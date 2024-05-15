// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/WidgetController/TangiWidgetController.h"

#include "AbilitySystem/TangiAbilitySystemComponent.h"
#include "AbilitySystem/TangiAttributeSet.h"
#include "Player/TangiPlayerController.h"
#include "Player/TangiPlayerState.h"

void UTangiWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UTangiWidgetController::BroadcastInitialValues()
{
	// Used in classes that derive from this base class.
}

void UTangiWidgetController::BindCallbacksToDependencies()
{
	// Used in classes that derive from this base class.
}

ATangiPlayerController* UTangiWidgetController::GetTangiPlayerController()
{
	if (TangiPlayerController == nullptr)
	{
		TangiPlayerController = Cast<ATangiPlayerController>(PlayerController);
	}
	return TangiPlayerController;
}

ATangiPlayerState* UTangiWidgetController::GetTangiPlayerState()
{
	if (TangiPlayerState == nullptr)
	{
		TangiPlayerState = Cast<ATangiPlayerState>(PlayerState);
	}
	return TangiPlayerState;
}

UTangiAbilitySystemComponent* UTangiWidgetController::GetTangiAbilitySystemComponent()
{
	if (TangiAbilitySystemComponent == nullptr)
	{
		TangiAbilitySystemComponent = Cast<UTangiAbilitySystemComponent>(AbilitySystemComponent);
	}
	return TangiAbilitySystemComponent;
}

UTangiAttributeSet* UTangiWidgetController::GetTangiAttributeSet()
{
	if (TangiAttributeSet == nullptr)
	{
		TangiAttributeSet = Cast<UTangiAttributeSet>(AttributeSet);
	}
	return TangiAttributeSet;
}
