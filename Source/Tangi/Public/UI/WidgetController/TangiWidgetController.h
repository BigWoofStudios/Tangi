// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TangiWidgetController.generated.h"

class ATangiPlayerController;
class ATangiPlayerState;
class UTangiAbilitySystemComponent;
class UTangiAttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {};
	FWidgetControllerParams(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
	: PlayerController(PlayerController), PlayerState(PlayerState), AbilitySystemComponent(AbilitySystemComponent), AttributeSet(AttributeSet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayTagChangedSignature, const FGameplayTag, GameplayTag, const int32, NewCount);


/**
 * The base widget controller class
 */
UCLASS()
class TANGI_API UTangiWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

protected:
	UFUNCTION(BlueprintCallable) ATangiPlayerController* GetTangiPlayerController();
	UFUNCTION(BlueprintCallable) ATangiPlayerState* GetTangiPlayerState();
	UFUNCTION(BlueprintCallable) UTangiAbilitySystemComponent* GetTangiAbilitySystemComponent();
	UFUNCTION(BlueprintCallable) UTangiAttributeSet* GetTangiAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController",
		meta=(Description="The base class for PlayerController reference, useful for things that don't require a custom implementation. Use GetTangiPlayerController for the casted version."))
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController",
		meta=(Description="The base class for PlayerState reference, useful for things that don't require a custom implementation. Use GetTangiPlayerState for the casted version."))
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController",
		meta=(Description="The base class for AbilitySystemComponent reference, useful for things that don't require a custom implementation. Use GetTangiAbilitySystemComponent for the casted version."))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController",
		meta=(Description="The base class for AttributeSet reference, useful for things that don't require a custom implementation. Use GetTangiAttributeSet for the casted version."))
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, Category = "WidgetController")
	TObjectPtr<ATangiPlayerController> TangiPlayerController;

	UPROPERTY(VisibleAnywhere, Category = "WidgetController")
	TObjectPtr<ATangiPlayerState> TangiPlayerState;

	UPROPERTY(VisibleAnywhere, Category = "WidgetController")
	TObjectPtr<UTangiAbilitySystemComponent> TangiAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "WidgetController")
	TObjectPtr<UTangiAttributeSet> TangiAttributeSet;
};
