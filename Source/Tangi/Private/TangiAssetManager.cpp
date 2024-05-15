// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiAssetManager.h"

UTangiAssetManager& UTangiAssetManager::Get()
{
	check(GEngine);
	
	UTangiAssetManager* VeilAssetManager = Cast<UTangiAssetManager>(GEngine->AssetManager);

	return *VeilAssetManager;
}

void UTangiAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	// This is required to use TargetData!
	// UAbilitySystemGlobals::Get().InitGlobalData();
}
