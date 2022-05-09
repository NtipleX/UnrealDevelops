// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileBooster.h"
#include "Components/StaticMeshComponent.h"
#include "Canon.h"

UMissileBooster::UMissileBooster() : burnTime(2.f), m_isBurning(false), m_rigidBody(nullptr)
{
	flag = false;
	PrimaryComponentTick.bCanEverTick = true;
	SetMassOverrideInKg(FName("Main"), 15, true);
	//SetComponentTickInterval(1.f);
}

void UMissileBooster::launch()
{
	FVector direction = m_rigidBody->GetForwardVector();
	FRotator rotation = m_rigidBody->GetComponentRotation();
	m_initialRoll = rotation.Roll;
	m_force = FVector(direction.Y * 120000 * (100 - abs(rotation.Roll)) / 10,
					  direction.X * -120000 * (100 - abs(rotation.Roll)) / 10,
					  rotation.Roll * 13000);
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]()
	{
		m_isBurning = false;
		m_maxReachedHighSpeed = m_rigidBody->GetOwner()->GetVelocity().Z;
		GetWorld()->GetTimerManager().SetTimer(m_updateGeometryTimer, this, &UMissileBooster::updateGeometry, 0.5f, true, 0.1f);
	});
	GetWorld()->GetTimerManager().SetTimer(m_burnTimer, TimerCallback, burnTime, false);
	m_isBurning = true;
	if(m_rigidBody)
		m_rigidBody->AddImpulse(m_force/2.5);
}

void UMissileBooster::TickComponent(float DeltaTime,
	enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	if (m_isBurning && m_rigidBody)
	{
		m_rigidBody->AddForce(m_force);
	}
}

void UMissileBooster::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMissileBooster::updateGeometry()
{
	FVector vel = m_rigidBody->GetOwner()->GetVelocity();
	FRotator flyRotation = m_rigidBody->GetComponentRotation();
	float rollFall = m_initialRoll * FMath::Min(1, FMath::Max(vel.Z / m_maxReachedHighSpeed, -1));
	flyRotation.Roll = rollFall;
	m_rigidBody->SetRelativeRotation(flyRotation);
}

void UMissileBooster::BeginPlay()
{
	Super::BeginPlay();
	m_rigidBody = dynamic_cast<UStaticMeshComponent*>(GetAttachParent());
	SetSimulatePhysics(true);
	launch();
}