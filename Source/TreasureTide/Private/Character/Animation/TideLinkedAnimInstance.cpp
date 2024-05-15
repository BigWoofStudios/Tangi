// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TideLinkedAnimInstance.h"

UTideLinkedAnimInstance::UTideLinkedAnimInstance()
{
	bUseMainInstanceMontageEvaluationData = true;
}

void UTideLinkedAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	Parent = Cast<UTideAnimInstance>(GetSkelMeshComponent()->GetAnimInstance());
	Character = Cast<ATideCharacter>(GetOwningActor());
}

void UTideLinkedAnimInstance::NativeBeginPlay()
{
	checkf(Parent.IsValid(),
		TEXT("%s should only be used as a linked anim instance within a %s animation blueprint!"),
		*ThisClass().GetName(), *UTideAnimInstance::StaticClass()->GetName());
	
	Super::NativeBeginPlay();
}
