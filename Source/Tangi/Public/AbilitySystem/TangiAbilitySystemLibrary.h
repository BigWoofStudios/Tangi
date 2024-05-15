// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TangiGameplayEffectContext.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "TangiAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UTangiAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Auroras Veil Ability System Library | Widget Controller")
	static UOverlayWidgetController *GetOverlayWidgetController(const UObject *WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Auroras Veil Ability System Library | Gameplay Effect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Auroras Veil Ability System Library | Gameplay Effect")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit);
};
