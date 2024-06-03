// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacterBase.h"

#include "AbilitySystemGlobals.h"
#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"
#include "AbilitySystem/Effect/TangiGameplayEffect.h"
#include "AbilitySystem/ExecCalc/ExecCalc_FallDamage.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Net/UnrealNetwork.h"

ATangiCharacterBase::ATangiCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ACharacter::SetReplicateMovement(true);
	SetReplicates(true);

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");
	AddOwnedComponent(MotionWarping);

	CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>("CharacterTrajectory");
	AddOwnedComponent(CharacterTrajectory);
	
	TestWeapon = CreateDefaultSubobject<UStaticMeshComponent>("OneHandedWeapon");
	TestWeapon->CanCharacterStepUpOn = ECB_No;
	TestWeapon->SetCollisionResponseToAllChannels(ECR_Overlap);
	TestWeapon->SetGenerateOverlapEvents(true);
	TestWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "OneHandedWeapon");
}

void ATangiCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bDead, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bHitReacting, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bDrowning, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bSwimming, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bUnderwater, Parameters);
}

void ATangiCharacterBase::OnMovementModeChanged(const EMovementMode PrevMovementMode, const uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	// Note:
	// Falling movement mode is actually also jumping because it doesn't take into account the Z velocity, so
	// because of this a character is considered falling when accelerating upwards and therefore the movement mode gets
	// set to Falling. This will hopefully be configurable in the new Mover2.0 plugin (Character Motion Component) but
	// is it currently experimental and has bugs which make it unusable as of UE v5.4.1
	if (GetAbilitySystemComponent())
	{
		for (const TTuple<unsigned char, FGameplayTag> Pair : FTangiGameplayTags::MovementModeTagMap)
		{
			if (GetAbilitySystemComponent()->HasMatchingGameplayTag(Pair.Value))
			{
				GetAbilitySystemComponent()->RemoveLooseGameplayTag(Pair.Value);
				GetAbilitySystemComponent()->RemoveReplicatedLooseGameplayTag(Pair.Value);
			}
		}
		if (const FGameplayTag* FoundTag = FTangiGameplayTags::MovementModeTagMap.Find(GetCharacterMovement()->MovementMode))
		{
			GetAbilitySystemComponent()->AddLooseGameplayTag(*FoundTag);
			GetAbilitySystemComponent()->AddReplicatedLooseGameplayTag(*FoundTag);
		}
	}

	if (GetCharacterMovement()->MovementMode == MOVE_Swimming || GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		UnCrouch();
	}
}

void ATangiCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATangiCharacterBase::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Update certain state data on tick using fast push networking 
	RefreshSwimming();
}

void ATangiCharacterBase::InitAbilityActorInfo() { /* Used in inherited classes. */ }

void ATangiCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	checkf(IsValid(GetAbilitySystemComponent()), TEXT("AbilitySystemComponent isn't valid in Character Base."));
	checkf(GameplayEffectClass, TEXT("GameplayEffectClass passed to ApplyEffectToSelf isn't valid in CharacterBase."));
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	ContextHandle.AddSourceObject(this);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ATangiCharacterBase::InitializeDefaultAttributes()
{
	checkf(DefaultVitalAttributes, TEXT("TangiCharacterBase requires a DefaultVitalAttributes to be set. Please check the BP implementation."));
	checkf(DefaultSecondaryAttributes, TEXT("TangiCharacterBase requires a DefaultSecondaryAttributes to be set. Please check the BP implementation."));

	// TODO: Load this from saved game??
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
	ApplyEffectToSelf(RegenerateHealthEffect, 1.f);
	ApplyEffectToSelf(RegenerateEnduranceEffect, 1.f);
	ApplyEffectToSelf(RegenerateOxygenEffect, 1.f);
}

void ATangiCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	LandedDelegate.AddDynamic(this, &ATangiCharacterBase::ApplyFallDamage);
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RegisterGenericGameplayTagEvent().AddUObject(this, &ATangiCharacterBase::TagChanged);
	}
}

void ATangiCharacterBase::AddCharacterAbilities() const
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::AddCharacterAbilities must be called from the server."));
		return;
	}
	
	// Add the default startup abilities for this character
	CastChecked<UTangiAbilitySystemComponent>(AbilitySystemComponent)->AddStartupAbilities(StartupAbilities);
}

void ATangiCharacterBase::ApplyFallDamage(const FHitResult&)
{
	if (AbilitySystemComponent && GE_FallDamage && HasAuthority())
	{
		ApplyEffectToSelf(GE_FallDamage, GetCharacterMovement()->Velocity.Z);
	}
}

void ATangiCharacterBase::TagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	if (CallbackTag == FTangiGameplayTags::Status_Attribute_Health_IsDead)
	{
		SetDead(NewCount > 0);	
	}
	else if (CallbackTag == FTangiGameplayTags::Status_IsHitReacting)
	{
		SetHitReacting(NewCount > 0);
	}
	else if (CallbackTag == FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning)
	{
		SetDrowning(NewCount > 0);
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// Hit React
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Hit React
void ATangiCharacterBase::SetHitReacting(const bool NewValue)
{
	if (!HasAuthority())
	{
		ServerSetHitReacting(NewValue);
		return;
	}

	if (bHitReacting != NewValue)
	{
		bHitReacting = NewValue;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bHitReacting, this);
		UnCrouch();
	}
}

void ATangiCharacterBase::ServerSetHitReacting_Implementation(const bool NewValue) { SetHitReacting(NewValue); }
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
void ATangiCharacterBase::SetDead(const bool NewValue)
{
	if (!HasAuthority())
	{
		ServerSetDead(NewValue);
		return;
	}

	if (bDead != NewValue)
	{
		bDead = NewValue;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bDead, this);
		UnCrouch();
	}
}


void ATangiCharacterBase::ServerSetDead_Implementation(const bool NewValue) { SetDead(NewValue); }
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Swimming
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Swimming
void ATangiCharacterBase::SetDrowning(const bool NewValue)
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("SetDrowning must be called from the server!"));
		return;
	}
	
	if (bDrowning != NewValue)
	{
		bDrowning = NewValue;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bDrowning, this);
	}
}

void ATangiCharacterBase::SetSwimming(const bool NewValue)
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("SetSwimming must be called from the server!"));
		return;
	}
	
	if (bSwimming != NewValue)
	{
		bSwimming = NewValue;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bSwimming, this);
	}
}

void ATangiCharacterBase::SetUnderwater(const bool NewValue)
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("SetUnderwater must be called from the server!"));
		return;
	}
	
	if (bUnderwater != NewValue)
	{
		bUnderwater = NewValue;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bUnderwater, this);

		if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
		{
			if (bUnderwater)
			{
				if (!ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_IsUnderwater))
				{
					ASC->AddLooseGameplayTag(FTangiGameplayTags::Status_IsUnderwater);
					ASC->AddReplicatedLooseGameplayTag(FTangiGameplayTags::Status_IsUnderwater);
				}
			}
			else
			{
				if (ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_IsUnderwater))
				{
					ASC->RemoveLooseGameplayTag(FTangiGameplayTags::Status_IsUnderwater);
					ASC->RemoveReplicatedLooseGameplayTag(FTangiGameplayTags::Status_IsUnderwater);
				}
				if (ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning))
				{
					ASC->RemoveLooseGameplayTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
					ASC->RemoveReplicatedLooseGameplayTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
				}
			}
		}
	}
}

void ATangiCharacterBase::RefreshSwimming()
{
	if (!HasAuthority()) return;
	
	const APhysicsVolume* CurrentVolume = GetPhysicsVolume();
	const bool bNewSwimming = CurrentVolume->bWaterVolume && GetCharacterMovement()->IsSwimming();
	SetSwimming(bNewSwimming);

	bool bNewUnderwater = false;
	if (bNewSwimming)
	{
		const FVector CapsuleTop = GetCapsuleComponent()->GetComponentLocation() + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		const float WaterSurfaceZ = CurrentVolume->GetActorLocation().Z + CurrentVolume->GetBounds().BoxExtent.Z;

		bNewUnderwater = CapsuleTop.Z <= WaterSurfaceZ;
	}
	
	SetUnderwater(bNewUnderwater);
}
#pragma endregion