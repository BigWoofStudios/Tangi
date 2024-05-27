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
}

void ATangiCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bIsDead, Parameters);
}

void ATangiCharacterBase::DeathTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	SetIsDead(NewCount > 0);
}

void ATangiCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(FTangiGameplayTags::Status_IsDead, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &ATangiCharacterBase::DeathTagChanged
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
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
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