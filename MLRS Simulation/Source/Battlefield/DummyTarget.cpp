// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyTarget.h"
#include "Canon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADummyTarget::ADummyTarget(): m_health(100)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(true);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0,0,0));
	meshComp->bApplyImpulseOnDamage = true;
	


}

// Called when the game starts or when spawned
void ADummyTarget::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ADummyTarget::takingDamage);
	if (!OnTakeAnyDamage.IsBound())
	{
		SLOG("Not bound!");
	}
	
}

// Called every frame
void ADummyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ADummyTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//
//}

float ADummyTarget::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator,
	AActor* DamageCauser
)
{
	SLOG("ADummyTarget::TakeDamage");
	m_health -= DamageAmount;
	FLOG(m_health);
	if (m_health < 0)
		Destroy();
	return DamageAmount;
}

void ADummyTarget::takingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	SLOG("ADummyTarget::takingDamage");
	m_health -= Damage;
	FLOG(m_health);
	if (m_health < 0)
		Destroy();
}