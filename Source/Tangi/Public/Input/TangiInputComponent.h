// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TangiInputConfig.h"
#include "EnhancedInputComponent.h"
#include "TangiInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UTangiInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UTangiInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UTangiInputComponent::BindAbilityActions(const UTangiInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (const FTangiInputActionToTag& ActionToTag : InputConfig->AbilityInputActionMappings)
	{
		if (ActionToTag.InputAction && ActionToTag.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(ActionToTag.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, ActionToTag.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(ActionToTag.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, ActionToTag.InputTag);
			}
		}
	}
}
