// Fill out your copyright notice in the Description page of Project Settings.


#include "Moving_Platform.h"

// Sets default values
AMoving_Platform::AMoving_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoving_Platform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMoving_Platform::Tick(float DeltaTime)
{

	// Move platform forwads
		// Get Current location
	FVector CurrentLocation = GetActorLocation();
		// Add vector to that location
		CurrentLocation += ( PlatformVelocity * DeltaTime);
		// Set the location
		SetActorLocation(CurrentLocation);

	// Send platform back if gone too far
		// Check how far we've moved
		float DistanceMoved = FVector ::Dist(StartLocation,CurrentLocation);
		// Reverse direction fof motion if gone too far

		if (MoveDistance < DistanceMoved)
		{
			float OverShoot = DistanceMoved - MoveDistance;
			FString Name = GetName();
			UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by: %f"),*Name, OverShoot);

			FVector MoveDirection = PlatformVelocity.GetSafeNormal();
			StartLocation += MoveDirection * MoveDistance;	
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity; 	
		}
}

