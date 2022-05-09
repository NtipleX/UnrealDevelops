// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PickupSystem/BasicPickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class PROJ_API AHealthPickup : public ABasicPickup
{
	GENERATED_BODY()
	
public:
	AHealthPickup();

public:
	virtual void applyPickupToPawn(AActor* pawn) override;

private:
	float m_healing;

};
