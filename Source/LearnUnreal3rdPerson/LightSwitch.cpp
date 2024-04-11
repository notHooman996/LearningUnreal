// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light"));

	RootComponent = CollisionComponent; 

	SwitchMesh->SetupAttachment(RootComponent);
	LightMesh->SetupAttachment(RootComponent);

	lightSwitchState = ELightSwitchState::ON; 
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (touching) {

		// TODO - get the light mesh

		if (lightSwitchState == ELightSwitchState::OFF) {
			// turn on light 
			LightMesh->SetVisibility(true);
		}
		else if (lightSwitchState == ELightSwitchState::ON) {
			// turn light off 
			LightMesh->SetVisibility(false);
		}

		touching = false; 
		lightSwitchState = (lightSwitchState == ELightSwitchState::OFF) ? ELightSwitchState::ON : ELightSwitchState::OFF; 
	}
}

void ALightSwitch::Use_Implementation()
{
	touching = true; 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("light switch")));
}

