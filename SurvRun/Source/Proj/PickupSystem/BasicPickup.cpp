// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPickup.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasicPickup::ABasicPickup() : m_floatValue(FVector(0, 0, -1.f))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creation
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	rotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));

	//Initialization
	pickupMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")).Object);

	//Attachment
	RootComponent = pickupMesh;
	boxComp->SetupAttachment(pickupMesh);

	//Transform
	pickupMesh->SetRelativeLocation(FVector(0, 0, 0));
	pickupMesh->SetWorldScale3D(FVector(0.3, 0.35, 0.2));

	//Configuration
	rotationComp->RotationRate = FRotator(0.f, 350.f, 0.f);
	boxComp->SetGenerateOverlapEvents(true);
	SetActorTickInterval(0.1f);

}

// Called when the game starts or when spawned
void ABasicPickup::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->SetRelativeLocation(FVector(0.f,0.f,0.f));
	GetWorldTimerManager().SetTimer(m_floatTimer, this, &ABasicPickup::changeFloatDirection, 0.6f, true, 0.6f);
	
}

// Called every frame
void ABasicPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(m_floatValue);

}

void ABasicPickup::applyPickupToPawn(AActor* pawn)
{
	pickupPickedDeleg.Broadcast();
}


void ABasicPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	applyPickupToPawn(OtherActor);
}

void ABasicPickup::changeFloatDirection()
{
	m_floatValue*=(-1);
}