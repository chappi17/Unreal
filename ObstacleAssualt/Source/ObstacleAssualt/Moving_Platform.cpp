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

	FString Name =GetName(); 

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"),*Name);

}

// Called every frame
void AMoving_Platform::Tick(float DeltaTime)
{

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);


}

void AMoving_Platform:: MovePlatform(float DeltaTime)
{


	// Send platform back if gone too far
		// Check how far we've moved
		// Reverse direction fof motion if gone too far

		if (ShouldPlatformReturn())
		{
			FVector MoveDirection = PlatformVelocity.GetSafeNormal();
			StartLocation += MoveDirection * MoveDistance;	
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity; 	
		}
		else
		{
			// Move platform forwads
			// Get Current location
		FVector CurrentLocation = GetActorLocation();
			// Add vector to that location
		CurrentLocation += ( PlatformVelocity * DeltaTime);
			// Set the location
		SetActorLocation(CurrentLocation);
		}
}

void AMoving_Platform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMoving_Platform::ShouldPlatformReturn()
{
	
	return MoveDistance < GetDistanceMoved(); 
}

float AMoving_Platform::GetDistanceMoved() const
{
    return FVector ::Dist(StartLocation,GetActorLocation());
}
