// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TangiHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UTangiUserWidget;

/**
 *
 */
UCLASS()
class TANGI_API ATangiHUD : public AHUD
{
	GENERATED_BODY()
public:
	UOverlayWidgetController *GetOverlayWidgetController(const FWidgetControllerParams&);

	void InitOverlay(APlayerController*, APlayerState*, UAbilitySystemComponent*, UAttributeSet*);

private:
	UPROPERTY()
	TObjectPtr<UTangiUserWidget> OverlayWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTangiUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
