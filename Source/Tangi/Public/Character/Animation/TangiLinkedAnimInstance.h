// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TangiAnimInstance.h"
#include "TangiLinkedAnimInstance.generated.h"

class ATangiCharacter;

/**
 * 
 */
UCLASS()
class TANGI_API UTangiLinkedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UTangiLinkedAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TWeakObjectPtr<UTangiAnimInstance> Parent;
};
