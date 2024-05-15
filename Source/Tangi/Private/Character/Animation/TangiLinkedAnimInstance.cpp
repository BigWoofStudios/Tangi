// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/Animation/TangiLinkedAnimInstance.h"

UTangiLinkedAnimInstance::UTangiLinkedAnimInstance()
{
	bUseMainInstanceMontageEvaluationData = true;
}

void UTangiLinkedAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	Parent = Cast<UTangiAnimInstance>(GetSkelMeshComponent()->GetAnimInstance());
	Character = Cast<ATangiCharacter>(GetOwningActor());
}

void UTangiLinkedAnimInstance::NativeBeginPlay()
{
	checkf(Parent.IsValid(),
		TEXT("%s should only be used as a linked anim instance within a %s animation blueprint!"),
		*ThisClass().GetName(), *UTangiAnimInstance::StaticClass()->GetName());
	
	Super::NativeBeginPlay();
}
