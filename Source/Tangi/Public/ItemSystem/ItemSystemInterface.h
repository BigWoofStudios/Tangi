// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BagComponent.h"
#include "UObject/Interface.h"
#include "ItemSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UItemSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANGI_API IItemSystemInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual UBagComponent* GetBag() = 0;
};
