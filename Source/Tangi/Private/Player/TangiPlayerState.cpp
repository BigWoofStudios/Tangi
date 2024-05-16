// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TangiPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TangiAttributeSet.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"


ATangiPlayerState::ATangiPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTangiAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UTangiAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}
