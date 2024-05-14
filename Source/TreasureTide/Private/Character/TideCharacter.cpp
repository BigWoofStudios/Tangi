// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TideCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ATideCharacter::ATideCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	if (IsValid(GetMesh()))
	{
		// Drop character mesh down flush with floor/ in position with capsule component
		// and rotate to face the forward direction, as indicated by the arrow in ACharacter
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.f, 0.f, -92.f),
			FRotator(0.f, -90.f, 0.f));
	}
}
