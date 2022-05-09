// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "BasicPickup.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APickupPlatform::APickupPlatform() : m_isContainPickup(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Creation
	meshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("meshComp"));
	geometryComp = CreateDefaultSubobject<USceneComponent>(TEXT("geometryComp"));
	effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Active Particle"));

	/// Initialization
	static auto platformMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	static auto sparksEffect = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));
	meshComp->SetStaticMesh(platformMesh.Object);
	effect->SetTemplate(sparksEffect.Object);

	/// Attachment
	RootComponent = meshComp;
	geometryComp->SetupAttachment(meshComp);
	effect->SetupAttachment(meshComp);

	/// Transform
	meshComp->SetRelativeLocation(FVector(0, 0, 0));
	meshComp->SetWorldScale3D(FVector(1, 1, 0.3));
	geometryComp->SetRelativeLocation(FVector(0, 0, 250));
	effect->SetWorldScale3D(FVector(3,3,3));

	/// Configuration

}

void APickupPlatform::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	effect->bAutoActivate = false;
	effect->Deactivate();
}

// Called when the game starts or when spawned
void APickupPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupPlatform::SpawnPickup()
{
	if(!pickupType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Platform: Bad pickup type"));
		return;
	}
	m_isContainPickup = true;
	auto pickupInstance = GetWorld()->SpawnActor<ABasicPickup>(pickupType, geometryComp->GetComponentLocation(), FRotator());
	pickupInstance->pickupPickedDeleg.AddUFunction(this, "OnPickupPicked");
	effect->Activate();
}

void APickupPlatform::OnPickupPicked()
{
	m_isContainPickup = false;
	pickupGrabDelegate.ExecuteIfBound();
	effect->Deactivate();
}