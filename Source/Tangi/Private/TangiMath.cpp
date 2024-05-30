// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiMath.h"

FVector UTangiMath::RadianToDirectionXY(const float InRadian)
{
	float Sin, Cos;
	FMath::SinCos(&Sin, &Cos, InRadian);

	return FVector(Cos, Sin, 0.0f);
}

FVector UTangiMath::PerpendicularCounterClockwiseXY(const FVector& InVector)
{
	return FVector(-InVector.Y, InVector.X, InVector.Z);
}

float UTangiMath::CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation)
{ 
	if (Velocity.IsNearlyZero()) return 0.f;

	const FMatrix RotMatrix = FRotationMatrix(BaseRotation);
	const FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
	const FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
	const FVector NormalizedVel = Velocity.GetSafeNormal2D();

	// Get a cos(alpha) of forward vector vs velocity
	const float ForwardCosAngle = static_cast<float>(FVector::DotProduct(ForwardVector, NormalizedVel));
	// Now get the alpha and convert to degree
	float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

	// Depending on where right vector is, flip it
	if (static_cast<float>(FVector::DotProduct(RightVector, NormalizedVel)) /*RightCosAngle*/ < 0.f)
	{
		ForwardDeltaDegree *= -1.f;
	}

	return ForwardDeltaDegree;
}
