// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Vector.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LastFireTime = FPlatformTime::Seconds();
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AmmoCount <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) // TODO Change FPlatform time to GetWorld()->GetTimeSeconds()
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}
void UTankAimingComponent::InitializeComponent(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimingAt(FVector& HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector& AimDirection)
{
	if (!ensure(Barrel || Turret)) { return; } 

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsARotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsARotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) > 180)
	{
		DeltaRotator.Yaw = -DeltaRotator.Yaw;
	}

	Turret->RotateTurret(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto CurrentBarrelPosition = Barrel->GetForwardVector().GetSafeNormal();
	return !CurrentBarrelPosition.FVector::Equals(AimDirection, .1);
}
void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }	
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	
		if (AmmoCount >= 1)
		{
			AmmoCount--;
		}
	}
	else
	{
		return;
	}
}
