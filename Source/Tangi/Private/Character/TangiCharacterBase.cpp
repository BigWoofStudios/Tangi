// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacterBase.h"

#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"
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
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bIsDead, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bIsHitReacting, Parameters);
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
	
	UTangiAbilitySystemComponent *VeilAbilitySystemComponent = CastChecked<UTangiAbilitySystemComponent>(AbilitySystemComponent);
	
	// Add the default startup abilities for this character
	VeilAbilitySystemComponent->AddStartupAbilities(StartupAbilities);
}

// ---------------------------------------------------------------------------------------------------------------------
// Hit React
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Hit React
void ATangiCharacterBase::HitReactTagChanged(const FGameplayTag, const int32 NewCount)
{
	SetIsHitReacting(NewCount > 0);
}

void ATangiCharacterBase::SetIsHitReacting(const bool bNewIsHitReacting)
{
	if (HasAuthority())
	{
		bIsHitReacting = bNewIsHitReacting;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bIsHitReacting, this)
	}
	else
	{
		ServerSetIsHitReacting(bNewIsHitReacting);
	}
}

void ATangiCharacterBase::ServerSetIsHitReacting_Implementation(const bool bNewIsHitReacting)
{
	SetIsHitReacting(bNewIsHitReacting);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
void ATangiCharacterBase::DeathTagChanged(const FGameplayTag, const int32 NewCount)
{
	SetIsDead(NewCount > 0);
}

void ATangiCharacterBase::SetIsDead(const bool bNewIsDead)
{
	if (HasAuthority())
	{
		bIsDead = bNewIsDead;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bIsDead, this)
	}
	else
	{
		ServerSetIsDead(bNewIsDead);
	}
}

void ATangiCharacterBase::ServerSetIsDead_Implementation(const bool bNewIsDead)
{
	SetIsDead(bNewIsDead);
}
#pragma endregion 