// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiAssetManager.h"

#include "AbilitySystemGlobals.h"

UTangiAssetManager& UTangiAssetManager::Get()
{
	check(GEngine);
	
	UTangiAssetManager* TangiAssetManager = Cast<UTangiAssetManager>(GEngine->AssetManager);

	return *TangiAssetManager;
}

void UTangiAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	// This is required to use TargetData!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
