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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Transient)
	TObjectPtr<ATangiCharacterBase> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Transient)
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Transient)
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;

// ---------------------------------------------------------------------------------------------------------------------
// Velocity
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector Velocity = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector PreviousVelocity = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector Velocity2D = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Velocity", Transient)
	FVector PreviousVelocity2D = FVector::Zero();

private:
	UFUNCTION() void RefreshVelocity();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Acceleration
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Acceleration
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Acceleration", Transient)
	FVector Acceleration = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Acceleration", Transient)
	FVector PreviousAcceleration = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Acceleration", Transient)
	FVector Acceleration2D = FVector::Zero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Acceleration", Transient)
	FVector PreviousAcceleration2D = FVector::Zero();

private:
	UFUNCTION() void RefreshAcceleration();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Locomotion Angle
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Locomotion Angle
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Bit flag for Chooser plugin."))
	uint8 bPivoting: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Used for Orientation Warping."))
	float LocomotionAngleAcceleration = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Used for Orientation Warping."))
	float LocomotionAngleVelocity = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Used to compute Yaw Delta for additive leans."))
	float Yaw = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Used to compute Yaw Delta for additive leans."))
	float PreviousYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Locomotion Angle", Transient, meta=(Description="Used for additive leans."))
	float YawDelta = 0.f;
	
private:
	UFUNCTION() void RefreshLocomotionAngle();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Falling
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient, meta=(Description="Absolute time of when the character started falling. Used to compute total time spent falling."))
	float FallStart = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient, meta=(Description="The amount of absolute time the character has spent falling."))
	float FallDuration = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient, meta=(Description="Bit flag for Chooser plugin."))
	uint8 bFalling: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Falling", Transient, meta=(Description="Bit flag to compute if the player is actively falling."))
	uint8 bPreviousFalling: 1 = 0;
	
private:
	UFUNCTION() void RefreshFalling();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Stance (Postures on Land)
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Stance
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Stance", Transient)
	TEnumAsByte<ECharacterStance> Stance = StandingStance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Stance", Transient)
	TEnumAsByte<ECharacterStance> PreviousStance = StandingStance;
	
private:
	UFUNCTION() void RefreshStance();
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Swimming
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Swimming
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bSwimming: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Swimming", Transient)
	uint8 bUnderwater: 1 = 0;
	
private:
	UFUNCTION() void RefreshSwimming();
#pragma endregion
};

