// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SurvSaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_API USurvSaveSystem : public USaveGame
{
	GENERATED_BODY()
public:

	USurvSaveSystem();

	UFUNCTION()
	bool saveToLeaderboard(float currentTimeAlive);

	void printAll();

public:

	UPROPERTY(VisibleAnywhere)
	int8 m_recNumber;
	UPROPERTY(VisibleAnywhere)
	TArray<float> m_aliveTimeRecords;

	
};
