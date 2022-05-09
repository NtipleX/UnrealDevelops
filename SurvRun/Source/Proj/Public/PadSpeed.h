// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PickupSystem/BasicPickup.h"
#include "PadSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_API APadSpeed : public ABasicPickup
{
	GENERATED_BODY()
public:
	APadSpeed();

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* m_defaultMaterial;

	UPROPERTY(EditAnywhere)
		  UMaterialInterface* m_rechargingMaterial;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARechargeTimerText> m_TimerText;
	
	virtual void PostActorCreated() override;
	virtual void applyPickupToPawn(AActor* pawn) override;

private:
	void StartRechargingProcess();

	bool m_isCharged;
	FTimerHandle m_rechargeTimer;
};
