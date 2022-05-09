// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBasic.generated.h"

UCLASS()
class BATTLEFIELD_API AProjectileBasic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBasic();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* projectileMesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* projectileParticle;

	UPROPERTY(EditAnywhere)
	class UMissileBooster* booster;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* contactTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
