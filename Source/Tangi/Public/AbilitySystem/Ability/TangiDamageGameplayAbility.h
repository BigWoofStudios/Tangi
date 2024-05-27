// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TangiGameplayAbility.h"
#include "TangiDamageGameplayAbility.generated.h"


USTRUCT()
struct FDamageTypeMap
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(Categories="Damage"))
	FGameplayTag Tag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FScalableFloat Amount = 0.f;
};
/**
 * 
 */
UCLASS()
class TANGI_API UTangiDamageGameplayAbility : public UTangiGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TArray<FDamageTypeMap> DamageTypes;
};
