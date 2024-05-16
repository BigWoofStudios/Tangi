// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "TangiPlayerController.generated.h"

class UTangiInputConfig;
class UDamageTextComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TANGI_API ATangiPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATangiPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Veil|PlayerController")
	UTangiAbilitySystemComponent* GetTangiAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UTangiAbilitySystemComponent> TangiAbilitySystemComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
// ---------------------------------------------------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Input
protected:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> TangiContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UTangiInputConfig> InputConfig = nullptr;
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	void MoveTriggered(const FInputActionValue& ActionValue);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	void LookTriggered(const FInputActionValue& ActionValue);
#pragma endregion
};
