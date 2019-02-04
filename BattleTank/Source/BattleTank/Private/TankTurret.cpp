// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::AzimuthRotate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Geven a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0, RawNewAzimuth, 0));

}

