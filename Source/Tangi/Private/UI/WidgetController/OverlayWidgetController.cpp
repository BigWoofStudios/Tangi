// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/TangiAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetTangiAttributeSet()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetTangiAttributeSet()->GetMaxHealth());
	
	OnEnduranceChanged.Broadcast(GetTangiAttributeSet()->GetEndurance());
	OnMaxEnduranceChanged.Broadcast(GetTangiAttributeSet()->GetMaxEndurance());
	
	OnOxygenChanged.Broadcast(GetTangiAttributeSet()->GetOxygen());
	OnMaxOxygenChanged.Broadcast(GetTangiAttributeSet()->GetMaxOxygen());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetEnduranceAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnEnduranceChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetMaxEnduranceAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnMaxEnduranceChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetOxygenAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnOxygenChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetTangiAttributeSet()->GetMaxOxygenAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{ OnMaxOxygenChanged.Broadcast(Data.NewValue); });
}