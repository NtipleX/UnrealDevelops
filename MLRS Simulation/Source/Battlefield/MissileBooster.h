// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "MissileBooster.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEFIELD_API UMissileBooster : public UPrimitiveComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float burnTime;

	UMissileBooster();

public:
	UFUNCTION()
	void launch();

	UFUNCTION()
	void updateGeometry();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime,	enum ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostInitProperties() override;

private:
	bool m_isBurning;
	float m_maxReachedHighSpeed;
	float m_initialRoll;
	FTimerHandle m_burnTimer;
	FTimerHandle m_updateGeometryTimer;
	FVector m_force;
	class UStaticMeshComponent* m_rigidBody;
	bool flag;
};
