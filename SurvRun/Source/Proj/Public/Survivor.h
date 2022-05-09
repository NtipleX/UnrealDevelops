// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor.generated.h"

class ASurvivor;

#define SLOG(text) UE_LOG(LogTemp, Warning, text);
DECLARE_DELEGATE_OneParam(FSurvivorDeath, ASurvivor*);

UCLASS(Blueprintable)
class PROJ_API ASurvivor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurvivor();

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springCamComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere)
	class UWidgetHUD* userInterface;
	
public:

	void forward(float scale);
	UFUNCTION(BlueprintCallable)
	void healup(float hp);
	UFUNCTION(BlueprintCallable)
	void speedup();
	UFUNCTION(BlueprintCallable)
	float health();
	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float m_health;
	FTimerHandle m_boostTimer;
	FSurvivorDeath m_playerDeadDeleg;
};
