// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TangiAnimInstance.h"

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
}
