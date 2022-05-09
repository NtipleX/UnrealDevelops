// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PhysicsVolume.h"
#include "PainVolume.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_API APainVolume : public APhysicsVolume
{
	GENERATED_BODY()
public:
	APainVolume();
	virtual void ActorEnteredVolume(class AActor* Other) override;
	virtual void Tick(float delta) override;
	virtual void BeginPlay() override;

private:
	float m_damageInterval;
	float m_timePassed;
	float m_damageValue;
	class APawn* m_player;
};
