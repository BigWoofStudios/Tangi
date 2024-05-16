// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "TangiInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTangiInputActionToTag
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * Used to associate Abilities' InputAction to a GameplayTag. For example, if the InputAction is IA_Sprint, this can be
 * mapped to a GameplayTag of "InputTag.Sprint" so when actions are bound, this config can be iterated over to find the
 * appropriate InputAction and GameplayTag for the EnhancedInputComponent's BindAction method.
 */
UCLASS()
class TANGI_API UTangiInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTangiInputActionToTag> AbilityInputActionMappings;
};
