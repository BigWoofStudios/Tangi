// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/TangiCharacterBase.h"
#include "TangiAnimInstance.generated.h"


UENUM(BlueprintType)
enum ECharacterStance : uint8
{
	CrouchingStance,
	StandingStance,
};
/**
 * 
 */
UCLASS()
class TANGI_API UTangiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ATangiCharacterBase> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;

// ---------------------------------------------------------------------------------------------------------------------
// Velocity
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector VelocityXY = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector PreviousVelocityXY = FVector::Zero();

	UFUNCTION()
	void RefreshVelocity();
#pragma endregion
	
// ---------------------------------------------------------------------------------------------------------------------
// Falling
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient)
	float FallStart = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient)
	float FallDuration = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient)
	uint8 bFalling: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient)
	uint8 bPreviousFalling: 1 = 0;

	UFUNCTION()
	void RefreshFalling();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Stance (Postures on Land)
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Stance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Stance", Transient)
	TEnumAsByte<ECharacterStance> Stance = StandingStance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Stance", Transient)
	TEnumAsByte<ECharacterStance> PreviousStance = StandingStance;

	UFUNCTION()
	void RefreshStance();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Movement Mode (Different Environments)
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Movement Mode
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bSwimming: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bPreviousSwimming: 1 = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bUnderwater: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bPreviousUnderwater: 1 = 0;
	
	UFUNCTION()
	void RefreshSwimming();
#pragma endregion
};

