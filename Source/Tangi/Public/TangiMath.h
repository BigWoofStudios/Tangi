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
	UFUNCTION(BlueprintPure, Category = "Tangi|Math|Vector", Meta = (ReturnDisplayName = "Direction"))
	static FVector RadianToDirectionXY(const float InRadian);
	
	UFUNCTION(BlueprintPure, Category = "Tangi|Math|Vector", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector PerpendicularCounterClockwiseXY(const FVector& InVector);

	/**
	 * A copy from UKismetAnimationLibrary function to prevent the need to add the module. If it turns out that this
	 * project uses more functions from this library, it will make more sense to remove this function and add the module.
	 * 
	 * Returns degree of the angle between Velocity and Rotation forward vector
	 * The range of return will be from [-180, 180]. Useful for feeding directional blendspaces.
	 * @param	Velocity		The velocity to use as direction relative to BaseRotation
	 * @param	BaseRotation	The base rotation, e.g. of a pawn
	 */
	UFUNCTION(BlueprintPure, Category="Tangi|Math|Animation|Utilities")
	static float CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation);
};
