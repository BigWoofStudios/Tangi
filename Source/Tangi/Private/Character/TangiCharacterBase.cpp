// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacterBase.h"

#include "AbilitySystem/TangiAbilitySystemComponent.h"

ATangiCharacterBase::ATangiCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	ACharacter::SetReplicateMovement(true);
	SetReplicates(true);
}

void ATangiCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATangiCharacterBase::InitAbilityActorInfo()
{
	// Used in inherited classes.
}

void ATangiCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
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
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}

void ATangiCharacterBase::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;
	
	UTangiAbilitySystemComponent *VeilAbilitySystemComponent = CastChecked<UTangiAbilitySystemComponent>(AbilitySystemComponent);
	
	// Add the default startup abilities for this character
	VeilAbilitySystemComponent->AddStartupAbilities(StartupAbilities);
}

