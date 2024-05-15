// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TangiAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UTangiAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UTangiAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;
};
