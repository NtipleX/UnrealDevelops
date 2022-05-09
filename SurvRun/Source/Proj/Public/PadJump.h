// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PadPlatform.h"
#include "PadJump.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJ_API APadJump : public APadPlatform
{
	GENERATED_BODY()
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
