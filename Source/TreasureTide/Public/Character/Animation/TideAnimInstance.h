// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/TideCharacter.h"
#include "TideAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TREASURETIDE_API UTideAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ATideCharacter> Character;
};
