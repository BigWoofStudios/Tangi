// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiMath.h"

FVector2D UTangiMath::ClampMagnitude012D(const FVector2D& InVector)
{
	const double MagnitudeSquared = InVector.SizeSquared();

	if (MagnitudeSquared <= 1.0f) return InVector;

	const double Scale = FMath::InvSqrt(MagnitudeSquared);

	return FVector2d(InVector.X * Scale, InVector.Y * Scale);
}

FVector UTangiMath::AngleToDirectionXY(const float InAngle)
{
	return RadianToDirectionXY(FMath::DegreesToRadians(InAngle));
}

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

double UTangiMath::DirectionToAngleXY(const FVector& InDirection)
{
	return FMath::RadiansToDegrees(FMath::Atan2(InDirection.Y, InDirection.X));
}
