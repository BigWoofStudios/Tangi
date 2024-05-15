// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TangiMath.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API UTangiMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Veil|Math|Vector", DisplayName = "Clamp Magnitude 01 2D", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector2D ClampMagnitude012D(const FVector2D& InVector);
	
	UFUNCTION(BlueprintPure, Category = "Veil|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector AngleToDirectionXY(const float InAngle);

	UFUNCTION(BlueprintPure, Category = "Veil|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector RadianToDirectionXY(const float InRadian);
	
	UFUNCTION(BlueprintPure, Category = "Veil|Math|Vector", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector PerpendicularCounterClockwiseXY(const FVector& InVector);

	UFUNCTION(BlueprintPure, Category = "Veil|Math|Vector", Meta = (AutoCreateRefTerm = "Direction", ReturnDisplayName = "Angle"))
	static double DirectionToAngleXY(const FVector& InDirection);
};
