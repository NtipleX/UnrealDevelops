// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "PickupSpawnSystem.generated.h"

class APickupPlatform;

UCLASS(BlueprintType)
class PROJ_API APickupSpawnSystem : public AActor
{
	GENERATED_BODY()
	
public:

	APickupSpawnSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APickupPlatform*> platforms;

public:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void respawnSinglePickup();

private:
	FTimerHandle timer;
	int32 m_currentIdPlatform;

};
