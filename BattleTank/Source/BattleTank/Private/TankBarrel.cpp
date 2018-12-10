// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMath.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move barrel the right amount this frame
	// based on barrel movement speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto NewElevation = FMath::Clamp<float>(RawNewElevation, MinBarrelElevation, MaxBarrelElevation);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
