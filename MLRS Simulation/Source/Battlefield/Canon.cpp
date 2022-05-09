// Fill out your copyright notice in the Description page of Project Settings.

#include "Canon.h"

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "ProjectileBasic.h"

// Sets default values
ACanon::ACanon() : isReadyShoot(false), batteryShells(40)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("canon mesh component"));
	canonPullPivot = CreateDefaultSubobject<USceneComponent>(TEXT("canon pull pivot"));
	static auto canonStaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	canonMesh->SetStaticMesh(canonStaticMesh.Object);
	canonMesh->SetRelativeLocation(FVector(0,0,0));

	canonParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("canon particle system"));
	canonParticle->SetAutoActivate(false);
	RootComponent = canonPullPivot;
	canonMesh->SetupAttachment(RootComponent);
	canonParticle->SetupAttachment(canonMesh);
	canonParticle->SetRelativeLocation(FVector(-50, 0, 0));
	canonPullPivot->SetRelativeRotation(FRotator(12.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void ACanon::BeginPlay()
{
	Super::BeginPlay();

	pullCanon(45);
	shootWhenReady();
}

// Called every frame
void ACanon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACanon::pullCanon(float degrees)
{
	FRotator finalRotation = canonPullPivot->GetRelativeRotation();
	finalRotation.Pitch = FMath::Min(70.f, FMath::Max(10.f, degrees));
	pullCanonInternal(canonPullPivot->GetRelativeRotation().Pitch, finalRotation.Pitch);
}

void ACanon::pullCanonInternal(float start, float end)
{
	float curDiff = fabs(start - end);
	float var = start;
	if(curDiff < 2.f)
	{
		start = end;
		m_timerDelegate.Unbind();
		isReadyShoot = true;
		return;
	}
	else if(start > end)
	{
		var -= 2;
	}
	else if(start < end)
	{
		var += 2;
	}
	start = var;
	FRotator curr = canonPullPivot->GetRelativeRotation();
	curr.Pitch = start;
	canonPullPivot->SetRelativeRotation(curr);
	m_timerDelegate.BindUFunction(this, "pullCanonInternal", start, end);
	GetWorldTimerManager().SetTimer(m_pullingTimer, m_timerDelegate, 0.02f, false);
}

void ACanon::shootWhenReady()
{
	if(!isReadyShoot)
	{
		GetWorldTimerManager().SetTimer(m_readyShootCheckTimer, this, &ACanon::shootWhenReady, 2.f, false);
	}
	else
	{
		canonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		canonMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		canonMesh->SetGenerateOverlapEvents(false);
		canonMesh->SetCollisionProfileName(FName(), false);
		canonParticle->Activate();
		FVector center = GetActorLocation();
		center.X = FMath::RandRange(center.X - 10, center.X + 10);
		center.Y = FMath::RandRange(center.Y - 30, center.Y + 30);
		center.Z = FMath::RandRange(center.Z - 20, center.Z + 20);
		FRotator stem = GetActorRotation();
		stem.Pitch = FMath::RandRange(stem.Pitch - 8, stem.Pitch + 8);
		stem.Yaw = FMath::RandRange(stem.Yaw - 5, stem.Yaw + 5);

		GetWorld()->SpawnActor<AProjectileBasic>(projectyleType, center, stem, FActorSpawnParameters());
		
		if (--batteryShells > 0)
		{
			GetWorldTimerManager().SetTimer(m_readyShootCheckTimer, this, &ACanon::shootWhenReady, 0.33, false);
		}
		else
		{
			pullCanon(15);
		}
	}
}