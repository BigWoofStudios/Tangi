// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TideMath.h"

FVector2D UTideMath::ClampMagnitude012D(const FVector2D& InVector)
{
	const double MagnitudeSquared = InVector.SizeSquared();

	if (MagnitudeSquared <= 1.0f) return InVector;

	const double Scale = FMath::InvSqrt(MagnitudeSquared);

	return FVector2d(InVector.X * Scale, InVector.Y * Scale);
}

FVector UTideMath::AngleToDirectionXY(const float InAngle)
{
	return RadianToDirectionXY(FMath::DegreesToRadians(InAngle));
}

FVector UTideMath::RadianToDirectionXY(const float InRadian)
{
	float Sin, Cos;
	FMath::SinCos(&Sin, &Cos, InRadian);

	return FVector(Cos, Sin, 0.0f);
}

FVector UTideMath::PerpendicularCounterClockwiseXY(const FVector& InVector)
{
	return FVector(-InVector.Y, InVector.X, InVector.Z);
}

double UTideMath::DirectionToAngleXY(const FVector& InDirection)
{
	return FMath::RadiansToDegrees(FMath::Atan2(InDirection.Y, InDirection.X));
}
