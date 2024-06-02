// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/TangiAbilitySystemGlobals.h"

#include "AbilitySystem/TangiGameplayEffectContext.h"

UTangiAbilitySystemGlobals::UTangiAbilitySystemGlobals()
{
	ReplicateActivationOwnedTags = true;
}

FGameplayEffectContext* UTangiAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FTangiGameplayEffectContext();
}
