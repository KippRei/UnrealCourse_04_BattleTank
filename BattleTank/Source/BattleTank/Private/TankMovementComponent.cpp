// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitializeComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super() as we're replacing the functionality
	UE_LOG(LogTemp, Warning, TEXT("%s MoveVelocity: %s"), *GetOwner()->GetName(), *(MoveVelocity.ToString()));
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack){return;}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Prevent double speed due to using both control options (Forward arrow and L+R arrows)
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO Prevent double speed due to using both control options (Forward arrow and L+R arrows)
}