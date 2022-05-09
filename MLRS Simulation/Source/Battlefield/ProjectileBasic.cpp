// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBasic.h"

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MissileBooster.h"
#include "Canon.h"

// Sets default values
AProjectileBasic::AProjectileBasic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("canon mesh component"));
	static auto projectileStaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	projectileMesh->SetStaticMesh(projectileStaticMesh.Object);
	RootComponent = projectileMesh;
	projectileMesh->SetupAttachment(RootComponent);
	projectileMesh->SetRelativeLocation(FVector(0,0,0));
	projectileMesh->SetSimulatePhysics(true);
	projectileMesh->SetEnableGravity(true);

	projectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("projectile particle system"));
	projectileParticle->SetupAttachment(projectileMesh);
	
	booster = CreateDefaultSubobject<UMissileBooster>(TEXT("MLRS boost"));
	booster->SetupAttachment(projectileMesh);
	booster->AttachToComponent(projectileMesh, FAttachmentTransformRules::KeepRelativeTransform);
	booster->SetRelativeLocation(FVector(0, 0, 0));

	contactTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("contactTriggerBox"));
	contactTrigger->SetupAttachment(projectileMesh);
	contactTrigger->SetRelativeLocation(FVector(10, 0, 0));
	contactTrigger->SetGenerateOverlapEvents(true);
	contactTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AProjectileBasic::BeginPlay()
{
	Super::BeginPlay();
	contactTrigger->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBasic::explode);

	booster->launch();

}

// Called every frame
void AProjectileBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBasic::explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> ignoring;
	bool hit = UGameplayStatics::ApplyRadialDamage(GetWorld(),
	20, GetActorLocation(), 2500, UDamageType::StaticClass(), ignoring, this, nullptr, true, ECollisionChannel::ECC_Visibility);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 5000, 10, FColor(100, 100, 255), false, 5);
	this->Destroy();
}