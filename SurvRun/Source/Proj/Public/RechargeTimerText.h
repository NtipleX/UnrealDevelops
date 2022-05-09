// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "RechargeTimerText.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_API ARechargeTimerText : public ATextRenderActor
{
	GENERATED_BODY()
	
public:
	ARechargeTimerText();
	void LookAt(AActor* target);


protected:
	virtual void Tick(float delta) override;

};
