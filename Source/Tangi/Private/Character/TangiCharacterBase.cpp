// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacterBase.h"

#include "AbilitySystemGlobals.h"
#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Net/UnrealNetwork.h"

ATangiCharacterBase::ATangiCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
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
}

void ATangiCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(FTangiGameplayTags::Status_IsDead, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &ATangiCharacterBase::DeathTagChanged
		);
		
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(FTangiGameplayTags::Status_IsHitReacting, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &ATangiCharacterBase::HitReactTagChanged
		);
	}
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
	checkf(DefaultVitalAttributes, TEXT("TangiCharacterBase required a DefaultVitalAttributes to be set. Please check the BP implementation."));
	checkf(DefaultSecondaryAttributes, TEXT("TangiCharacterBase required a DefaultSecondaryAttributes to be set. Please check the BP implementation."));

	// TODO: Load this from saved game??
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ATangiCharacterBase::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;
	
	UTangiAbilitySystemComponent *TangiAbilitySystemComponent = CastChecked<UTangiAbilitySystemComponent>(AbilitySystemComponent);
	
	// Add the default startup abilities for this character
	TangiAbilitySystemComponent->AddStartupAbilities(StartupAbilities);
}

// ---------------------------------------------------------------------------------------------------------------------
// Hit React
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Hit React
void ATangiCharacterBase::HitReactTagChanged(const FGameplayTag, const int32 NewCount)
{
	SetHitReacting(NewCount > 0);
}

void ATangiCharacterBase::SetHitReacting(const bool NewValue)
{
	if (HasAuthority())
	{
		if (bHitReacting != NewValue)
		{
			bHitReacting = NewValue;
			MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bHitReacting, this)
		}
	}
	else
	{
		ServerSetHitReacting(NewValue);
	}
}

void ATangiCharacterBase::ServerSetHitReacting_Implementation(const bool NewValue)
{
	SetHitReacting(NewValue);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
void ATangiCharacterBase::DeathTagChanged(const FGameplayTag, const int32 NewCount)
{
	SetDead(NewCount > 0);
}

void ATangiCharacterBase::SetDead(const bool NewValue)
{
	if (HasAuthority())
	{
		if (bDead != NewValue)
		{
			bDead = NewValue;
			MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bDead, this)
		}
	}
	else
	{
		ServerSetDead(NewValue);
	}
}

void ATangiCharacterBase::ServerSetDead_Implementation(const bool NewValue)
{
	SetDead(NewValue);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Swimming
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Swimming
void ATangiCharacterBase::SetSwimming(const bool NewValue)
{
	if (HasAuthority())
	{
		if (bSwimming != NewValue)
		{
			bSwimming = NewValue;
			MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bSwimming, this);
		}
	}
	else
	{
		ServerSetSwimming(NewValue);
	}
}

void ATangiCharacterBase::ServerSetSwimming_Implementation(const bool NewValue)
{
	SetSwimming(NewValue);
}

void ATangiCharacterBase::SetUnderwater(const bool NewValue)
{
	if (HasAuthority())
	{
		if (bUnderwater != NewValue)
		{
			bUnderwater = NewValue;
			MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bUnderwater, this);
		}
	}
	else
	{
		ServerSetUnderwater(NewValue);
	}
}

void ATangiCharacterBase::ServerSetUnderwater_Implementation(const bool NewValue)
{
	SetUnderwater(NewValue);
}

void ATangiCharacterBase::RefreshSwimming()
{
	const APhysicsVolume* CurrentVolume = GetPhysicsVolume();
	const bool bIsInWater = CurrentVolume->bWaterVolume;
	SetSwimming(bIsInWater && GetCharacterMovement()->IsSwimming());

	bool bNewUnderwater = false;
	if (bSwimming)
	{
		const FVector CapsuleTop = GetCapsuleComponent()->GetComponentLocation() + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		const float WaterSurfaceZ = CurrentVolume->GetActorLocation().Z + CurrentVolume->GetBounds().BoxExtent.Z;

		bNewUnderwater = CapsuleTop.Z <= WaterSurfaceZ;
	}
	
	SetUnderwater(bNewUnderwater);

	// If the character is underwater, activate the ability
	if (GetAbilitySystemComponent() && HasAuthority())
	{
		const FGameplayTagContainer TagContainer = FGameplayTagContainer{FTangiGameplayTags::GameplayAbility_HoldBreath};
		
		if (bUnderwater)
		{
			GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
		}
		else
		{
			GetAbilitySystemComponent()->CancelAbilities(&TagContainer);
		}
	}
}
#pragma endregion 