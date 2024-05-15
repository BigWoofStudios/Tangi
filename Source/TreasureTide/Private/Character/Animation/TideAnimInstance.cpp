// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TideAnimInstance.h"

void UTideAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ATideCharacter>(GetOwningActor());
}

void UTideAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	checkf(Character, TEXT(""));
}

void UTideAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	
	if (!IsValid(Character))
	{
		return;
	}

	// TODO: Refresh data here on worker thread
}
