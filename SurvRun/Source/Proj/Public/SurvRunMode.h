// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvRunMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJ_API ASurvRunMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASurvRunMode();


	UPROPERTY(EditAnywhere)
	FString GameSaveName;

	UFUNCTION()
	void playerDeath(ASurvivor* player);

	UFUNCTION(BlueprintImplementableEvent)
	void GameOverEvent(float time);
};
