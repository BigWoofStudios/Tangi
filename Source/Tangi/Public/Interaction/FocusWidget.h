// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FocusWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UFocusWidget : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TimeRemaining = 0.f;
};
