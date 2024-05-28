// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TangiAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"

void UTangiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ATangiCharacterBase>(GetOwningActor());
}

void UTangiAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);

	if (!IsValid(Character)) return;
	
	CharacterTrajectory = Character->CharacterTrajectory;

	RefreshStance();
	RefreshSwimming();
	RefreshVelocity();
	RefreshFalling();
}

// ---------------------------------------------------------------------------------------------------------------------
// Velocity
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Velocity
void UTangiAnimInstance::RefreshVelocity()
{
	PreviousVelocityXY = VelocityXY;
	VelocityXY = FVector(Character->GetCharacterMovement()->Velocity.X, Character->GetCharacterMovement()->Velocity.Y, 0.f);
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Falling
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Falling
void UTangiAnimInstance::RefreshFalling()
{
	bPreviousFalling = bFalling;
	bFalling = Character->GetCharacterMovement()->IsFalling() && Character->GetCharacterMovement()->Velocity.Z < UE_SMALL_NUMBER;
	
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
	bPreviousSwimming = bSwimming;
	bPreviousUnderwater = bUnderwater;

	const APhysicsVolume* CurrentVolume = Character->GetPhysicsVolume();
	const bool bIsInWater = CurrentVolume->bWaterVolume;
	bSwimming = bIsInWater && Character->GetCharacterMovement()->IsSwimming();
	if (bSwimming)
	{
		const FVector CapsuleTop = Character->GetCapsuleComponent()->GetComponentLocation() + FVector(0.0f, 0.0f, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		const float WaterSurfaceZ = CurrentVolume->GetActorLocation().Z + CurrentVolume->GetBounds().BoxExtent.Z;

		bUnderwater = CapsuleTop.Z <= WaterSurfaceZ;
	}
	else
	{
		bUnderwater = 0;
	}
}
#pragma endregion 