// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TangiAnimInstance.h"

void UTangiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ATangiCharacter>(GetOwningActor());
}

void UTangiAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	checkf(Character, TEXT(""));
}

void UTangiAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	
	if (!IsValid(Character))
	{
		return;
	}

	// TODO: Refresh data here on worker thread
}
