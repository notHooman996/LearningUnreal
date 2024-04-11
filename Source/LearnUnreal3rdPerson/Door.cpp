// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	RootComponent = CollisionComponent;

	DoorMesh->SetupAttachment(RootComponent);

	doorState = EDoorState::CLOSED; 
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (interacting) {
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / InteractTime * 100.0f, 0.0f, 100.0f); 

		FRotator currentRotation = DoorMesh->GetRelativeRotation();

		FRotator newZRotation;

		if (doorState == EDoorState::CLOSED) {
			// open door 
			FRotator targetRotation(0, 90, 0);
			newZRotation = FMath::Lerp(currentRotation, targetRotation, DeltaTime * 1.0f);
		}
		else if (doorState == EDoorState::OPEN) {
			// close door 
			FRotator targetRotation(0, 0, 0);
			newZRotation = FMath::Lerp(currentRotation, targetRotation, DeltaTime * 1.0f);
		}

		DoorMesh->SetRelativeRotation(newZRotation);

		if (percentage >= 100.0f) {
			interacting = false; 
			timeSinceTick = 0; 

			doorState = (doorState == EDoorState::CLOSED) ? EDoorState::OPEN : EDoorState::CLOSED; 
		}
	}
}

void ADoor::Use_Implementation()
{
	interacting = true; 
}

