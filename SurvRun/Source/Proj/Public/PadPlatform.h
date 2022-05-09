// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PadPlatform.generated.h"

UCLASS()
class PROJ_API APadPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APadPlatform();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* padMeshComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* padBoxComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
