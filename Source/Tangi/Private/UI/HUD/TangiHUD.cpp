// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/HUD/TangiHUD.h"

#include "UI/Widget/TangiUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/TangiWidgetController.h"

UOverlayWidgetController* ATangiHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void ATangiHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_VeilHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_VeilHUD"));

	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);

	OverlayWidget = CreateWidget<UTangiUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(GetOverlayWidgetController(WidgetControllerParams));
	GetOverlayWidgetController(WidgetControllerParams)->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}
