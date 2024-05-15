// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/TangiAbilitySystemGlobals.h"

#include "AbilitySystem/TangiGameplayEffectContext.h"

FGameplayEffectContext* UTangiAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FTangiGameplayEffectContext();
}
