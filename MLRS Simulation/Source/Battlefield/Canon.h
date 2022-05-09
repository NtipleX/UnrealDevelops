// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Canon.generated.h"

#define SLOG(text) UE_LOG(LogTemp, Warning, TEXT(text));
#define FSLOG(text) UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
#define VLOG(vec) UE_LOG(LogTemp, Warning, TEXT("%s"), *vec.ToString());
#define FLOG(num) UE_LOG(LogTemp, Warning, TEXT("%f"), num);

UCLASS()
class BATTLEFIELD_API ACanon : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* canonMesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* canonParticle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectileBasic> projectyleType;

	UPROPERTY(EditAnywhere)
	USceneComponent* canonPullPivot;

	UPROPERTY(EditAnywhere)
	float batteryShells;

	// Sets default values for this actor's properties
	ACanon();

public:
	UFUNCTION(BlueprintCallable)
	void pullCanon(float degrees);

	UFUNCTION(BlueprintCallable)
	void shootWhenReady();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void pullCanonInternal(float start, float end);

private:
	bool isReadyShoot;
	FTimerHandle m_pullingTimer;
	FTimerHandle m_readyShootCheckTimer;
	FTimerDelegate m_timerDelegate;


};
