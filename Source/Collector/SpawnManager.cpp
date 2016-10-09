// Fill out your copyright notice in the Description page of Project Settings.

#include "Collector.h"
#include "SpawnManager.h"
#include "Pickup.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElapseTime = 0.f;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/Pickup_BP.Pickup_BP'"));
	WhatToSpawn = (UClass*)ItemBlueprint.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	//GetTimerManager().
}

// Called every frame
void ASpawnManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ElapseTime += DeltaTime;

	if (ElapseTime > 3.f)
	{
		SpawnPickup();

		ElapseTime = 0.f;
	}

}

void ASpawnManager::SpawnPickup()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		float fX = -(FMath::Rand() % 500) - 500.f;
		float fY = (FMath::Rand() % 500) + 100.f;
		float fZ = 500.f;

		FVector SpawnLocation(fX, fY, fZ);
		FRotator SpawnRotation(0.f, 0.f, 0.f);


		APickup* TempPickup = pWorld->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	}
}
