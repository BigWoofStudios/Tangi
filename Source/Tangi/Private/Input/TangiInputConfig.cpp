// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Input/TangiInputConfig.h"

const UInputAction* UTangiInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FTangiInputActionToTag& Action: AbilityInputActionMappings)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));	
	}
	
	return nullptr;
}
