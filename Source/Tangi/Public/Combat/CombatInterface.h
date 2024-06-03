// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANGI_API ICombatInterface
{
	GENERATED_BODY()
public:
	virtual UStaticMeshComponent* GetActiveWeaponMesh() = 0;

	// Hit React
	UFUNCTION(BlueprintCallable) virtual bool GetIsHitReacting() = 0;
	UFUNCTION(BlueprintCallable) virtual UAnimMontage* GetHitReactMontage() = 0;
	UFUNCTION(BlueprintCallable) virtual TArray<USoundBase*> GetHitReactSounds() = 0;

	// Death
	UFUNCTION(BlueprintCallable) virtual bool GetIsDead() = 0;
	UFUNCTION(BlueprintCallable) virtual UAnimMontage* GetDeathMontage() = 0;
	UFUNCTION(BlueprintCallable) virtual TArray<USoundBase*> GetDeathSounds() = 0;

	// Attack
	UFUNCTION(BlueprintCallable) virtual UAnimMontage* GetMeleeAttackMontage() = 0;
};
