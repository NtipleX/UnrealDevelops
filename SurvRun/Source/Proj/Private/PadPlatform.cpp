// Fill out your copyright notice in the Description page of Project Settings.


#include "PadPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RechargeTimerText.h"

// Sets default values
APadPlatform::APadPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	padMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform mesh"));
	padBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform box"));

	static auto platformMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	padMeshComp->SetStaticMesh(platformMesh.Object);

	RootComponent = padMeshComp;
	padBoxComp->SetupAttachment(padMeshComp);
	padMeshComp->SetRelativeLocation(FVector(0, 0, 0));
	padBoxComp->SetRelativeLocation(FVector(0, 0, 0));

	padMeshComp->SetWorldScale3D(FVector(1, 1, 0.2));
	padBoxComp->SetWorldScale3D(FVector(1, 1, 0.4));

	padMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	padMeshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

}

// Called when the game starts or when spawned
void APadPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APadPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


