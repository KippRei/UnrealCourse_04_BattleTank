// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!ensure(PlayerTank && AITank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // radius is in cm

	auto PlayerLocation = PlayerTank->GetActorLocation();
	auto AIAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	AIAimingComponent->AimingAt(PlayerLocation);
	
	// TODO Fix firing
	AIAimingComponent->Fire();
}