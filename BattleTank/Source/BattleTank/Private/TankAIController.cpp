// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // radius is in cm

	AITank->AimAt(PlayerTank->GetActorLocation());
	
	// TODO fire if ready
	// AITank->Fire();

}