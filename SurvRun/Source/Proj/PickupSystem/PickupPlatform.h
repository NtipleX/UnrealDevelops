// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupPlatform.generated.h"

class APickupSpawnSystem;

DECLARE_DELEGATE(FPickupGrabbed)

UCLASS()
class PROJ_API APickupPlatform : public AActor
{
	GENERATED_BODY()
	friend class APickupSpawnSystem;
	
public:	
	// Sets default values for this actor's properties
	APickupPlatform();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere)
	class USceneComponent* geometryComp;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABasicPickup> pickupType;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* effect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnPickupPicked();
	UFUNCTION(BlueprintCallable)
	void SpawnPickup();

private:
	FPickupGrabbed pickupGrabDelegate;
	bool m_isContainPickup;


};
