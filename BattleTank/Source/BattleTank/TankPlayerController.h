// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D, FVector&) const;

	bool GetLookVectorHitLocation(FVector&, FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	UPROPERTY(EditAnywhere)
		FVector TankBarrelLevel {0.f, 0.f, 100.f};
};
