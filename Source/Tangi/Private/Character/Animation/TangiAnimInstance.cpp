// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TangiAnimInstance.h"

#include "TangiMath.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"

void UTangiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (ATangiCharacterBase* TangiCharacterBase = Cast<ATangiCharacterBase>(GetOwningActor()))
	{
		Character = TangiCharacterBase;
		CharacterTrajectory = Character->CharacterTrajectory;
		CharacterMovementComponent = Character->GetCharacterMovement();
	}
}

void UTangiAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);

	if (!IsValid(Character)) return;
	
	RefreshStance();
	RefreshSwimming();
	RefreshFalling();
	
	RefreshVelocity();
	RefreshAcceleration();
	RefreshLocomotionAngle();
}

// ---------------------------------------------------------------------------------------------------------------------
// Velocity
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Velocity
void UTangiAnimInstance::RefreshVelocity()
{
	PreviousVelocity2D = Velocity2D;
	PreviousVelocity = Velocity;
	
	Velocity = CharacterMovementComponent->Velocity;
	Velocity2D = Velocity * FVector(1.f, 1.f, 0.f);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Acceleration
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Acceleration
void UTangiAnimInstance::RefreshAcceleration()
{
	PreviousAcceleration2D = Acceleration2D;
	PreviousAcceleration = Acceleration;
	
	Acceleration = CharacterMovementComponent->GetCurrentAcceleration();
	Acceleration2D = Acceleration * FVector(1.f, 1.f, 0.f);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Locomotion Angle
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Locomotion Angle
void UTangiAnimInstance::RefreshLocomotionAngle()
{
	const FRotator CharacterRotation = Character->GetActorRotation();
	LocomotionAngleVelocity = UTangiMath::CalculateDirection(Velocity2D, CharacterRotation);
	LocomotionAngleAcceleration = UTangiMath::CalculateDirection(Acceleration2D, CharacterRotation);
	
	PreviousYaw = Yaw;
	Yaw = CharacterRotation.Yaw;
	YawDelta = FMath::IsNearlyZero(PreviousYaw) ? 0.f : Yaw / PreviousYaw;
	
	bPivoting = FVector::DotProduct(Velocity2D.GetSafeNormal(), Acceleration2D.GetSafeNormal()) < UE_SMALL_NUMBER;
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Falling
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
void UTangiAnimInstance::RefreshFalling()
{
	bPreviousFalling = bFalling;
	bFalling = CharacterMovementComponent->IsFalling() && CharacterMovementComponent->Velocity.Z < UE_SMALL_NUMBER;
	
	if (bFalling && !bPreviousFalling) // Character just started falling
	{
		FallStart = GetWorld()->GetTimeSeconds();
		FallDuration = 0.f;
	}
	else if (bFalling && bPreviousFalling) // Character is continuing to fall
	{
		FallDuration = GetWorld()->GetTimeSeconds() - FallStart;
	}
	else // Character is not falling
	{
		FallStart = 0.f;
		FallDuration = 0.f;
	}
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Stance (Postures on Land)
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Stance
void UTangiAnimInstance::RefreshStance()
{
	PreviousStance = Stance;

	if (Character->bIsCrouched)
	{
		Stance = CrouchingStance;
	}
	else
	{
		Stance = StandingStance;
	}
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Swimming
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Swimming
void UTangiAnimInstance::RefreshSwimming()
{
	bSwimming = Character->bSwimming;
	bUnderwater = Character->bUnderwater;
}
#pragma endregion 