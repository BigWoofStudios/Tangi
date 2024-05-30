// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/TangiAbilitySystemLibrary.h"

#include "AbilitySystem/TangiGameplayEffectContext.h"
#include "Player/TangiPlayerState.h"
#include "UI/HUD/TangiHUD.h"


UOverlayWidgetController* UTangiAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController *PlayerController = WorldContextObject->GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return nullptr;
	
	ATangiHUD *TangiHUD = Cast<ATangiHUD>(PlayerController->GetHUD());
	if (!TangiHUD) return nullptr;
	
	ATangiPlayerState *PlayerState = PlayerController->GetPlayerState<ATangiPlayerState>();
	if (!PlayerState) return nullptr;
	
	UAbilitySystemComponent *AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	UAttributeSet *AttributeSet = PlayerState->GetAttributeSet();
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	
	return TangiHUD->GetOverlayWidgetController(WidgetControllerParams);
}

bool UTangiAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FTangiGameplayEffectContext *TangiGameplayEffectContext = static_cast<const FTangiGameplayEffectContext *>(EffectContextHandle.Get()))
	{
		return TangiGameplayEffectContext->IsCriticalHit();
	}
	
	return false;
}

void UTangiAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	const bool bInIsCriticalHit)
{
	if (FTangiGameplayEffectContext *TangiGameplayEffectContext = static_cast<FTangiGameplayEffectContext *>(EffectContextHandle.Get()))
	{
		TangiGameplayEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
