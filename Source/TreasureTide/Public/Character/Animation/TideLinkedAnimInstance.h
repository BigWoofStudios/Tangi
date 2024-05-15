// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TideAnimInstance.h"
#include "TideLinkedAnimInstance.generated.h"

class ATideCharacter;

/**
 * 
 */
UCLASS()
class TREASURETIDE_API UTideLinkedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UTideLinkedAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TWeakObjectPtr<UTideAnimInstance> Parent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ATideCharacter> Character;
};
