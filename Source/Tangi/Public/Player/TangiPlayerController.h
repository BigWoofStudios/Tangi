// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TangiAbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/InteractionComponent.h"
#include "TangiPlayerController.generated.h"

struct FInputActionValue;
class UTangiInputConfig;
class UDamageTextComponent;
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

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	UFUNCTION(BlueprintCallable, Category = "Veil|PlayerController")
	UTangiAbilitySystemComponent* GetTangiAbilitySystemComponent();

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bCriticalHit);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY() TObjectPtr<UInteractionComponent> InteractionComponent = nullptr;
	UPROPERTY() TObjectPtr<UTangiAbilitySystemComponent> TangiAbilitySystemComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

// ---------------------------------------------------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Input
protected:
	virtual void SetupInputComponent() override;
	
private:
	void AbilityInputTagPressed(const FGameplayTag InputTag);
	void AbilityInputTagReleased(const FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Settings")
	TObjectPtr<UInputMappingContext> TangiContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Settings")
	TObjectPtr<UTangiInputConfig> InputConfig = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Action")
	TObjectPtr<UInputAction> MoveAction;
	void MoveTriggered(const FInputActionValue& ActionValue);
	void MoveStopped(const FInputActionValue& ActionValue);
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Action")
	TObjectPtr<UInputAction> LookAction;
	void LookTriggered(const FInputActionValue& ActionValue);

	UPROPERTY(EditDefaultsOnly, Category="Input|Action")
	TObjectPtr<UInputAction> CrouchAction;
	void CrouchStarted(const FInputActionValue& ActionValue);

	UPROPERTY(EditDefaultsOnly, Category="Input|Action")
	TObjectPtr<UInputAction> JumpAction;
	void JumpStarted(const FInputActionValue& ActionValue);
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Action")
	TObjectPtr<UInputAction> InteractAction;
	void InteractStarted(const FInputActionValue& ActionValue);
	void InteractEnded(const FInputActionValue& ActionValue);
	
#pragma endregion
};
