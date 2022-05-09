// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicPickup.generated.h"

UCLASS()
class PROJ_API ABasicPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	DECLARE_EVENT( ABasicPickup, PickupPickedEvent )
	PickupPickedEvent pickupPickedDeleg;

	// Sets default values for this actor's properties
	ABasicPickup();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* pickupMesh;
	UPROPERTY(EditAnywhere)
		class URotatingMovementComponent* rotationComp;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void applyPickupToPawn(class AActor* pawn);

private:
	UFUNCTION()
	void changeFloatDirection();

private:
	FVector m_floatValue;
	FTimerHandle m_floatTimer;
};
