// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawnSystem.h"
#include "PickupPlatform.h"
#include "BasicPickup.h"
#include "Math/UnrealMathUtility.h"

APickupSpawnSystem::APickupSpawnSystem() : platforms(), m_currentIdPlatform(-1)
{}

void APickupSpawnSystem::respawnSinglePickup()
{
	int32 idPlatform = FMath::RandRange(0, platforms.Num()-1);
	if(!platforms[idPlatform]->m_isContainPickup && idPlatform != m_currentIdPlatform)
	{
		m_currentIdPlatform = idPlatform;
		platforms[idPlatform]->SpawnPickup();
	}
	else
	{
		respawnSinglePickup();
	}
}

void APickupSpawnSystem::BeginPlay()
{
	Super::BeginPlay();

	for(auto& item : platforms)
	{
		item->pickupGrabDelegate.BindUFunction(this, "respawnSinglePickup");
	}

	respawnSinglePickup();
}
