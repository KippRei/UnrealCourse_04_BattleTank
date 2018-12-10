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

	auto PlayerTank = GetPlayerTank();
	auto AITank = GetAITank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI %s cannot find Player"), *AITank->GetName())
	}

	else
	{
		// TODO move towards player

		AITank->AimAt(PlayerTank->GetActorLocation());
	
		// TODO fire if ready
	}
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}