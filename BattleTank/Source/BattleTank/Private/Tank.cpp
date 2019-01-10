// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "../Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() // Blueprint BeginPlay will be called when Super is called
{
	Super::BeginPlay(); // Needed for Blueprint BeginPlay to run!!!!!
}


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is dead!"), *this->GetName());
		this->Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage = %f"), DamageToApply);
	return DamageToApply;
}