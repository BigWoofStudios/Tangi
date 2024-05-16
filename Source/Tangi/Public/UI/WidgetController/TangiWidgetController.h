// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

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

/**
 * 
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
	UFUNCTION(BlueprintPure) ATangiPlayerController* GetTangiPlayerController();
	UFUNCTION(BlueprintPure) ATangiPlayerState* GetTangiPlayerState();
	UFUNCTION(BlueprintPure) UTangiAbilitySystemComponent* GetTangiAbilitySystemComponent();
	UFUNCTION(BlueprintPure) UTangiAttributeSet* GetTangiAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
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
