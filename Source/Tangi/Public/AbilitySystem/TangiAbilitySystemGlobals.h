// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "TangiAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UTangiAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	UTangiAbilitySystemGlobals();
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};