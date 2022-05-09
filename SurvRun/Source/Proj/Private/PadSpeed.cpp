// Fill out your copyright notice in the Description page of Project Settings.


#include "PadSpeed.h"
#include "RechargeTimerText.h"
#include "Survivor.h"

APadSpeed::APadSpeed() : m_isCharged(true)
{}

void APadSpeed::StartRechargingProcess()
{
	auto finishRecharge = [&]()
	{
		m_isCharged = true;
		pickupMesh->SetMaterial(0, m_defaultMaterial);
	};
	m_isCharged = false;
    

	FVector locationAbove = GetActorLocation();
	locationAbove.Z += GetActorScale3D().Z * 500;
	GetWorld()->SpawnActor<ARechargeTimerText>(m_TimerText, locationAbove, FRotator());
	pickupMesh->SetMaterial(0, m_rechargingMaterial);
	GetWorld()->GetTimerManager().SetTimer(m_rechargeTimer, finishRecharge, 0.1f, false, 15.f);
}

void APadSpeed::PostActorCreated() 
{
	pickupMesh->SetMaterial(0, m_defaultMaterial);
}


void APadSpeed::applyPickupToPawn(class AActor* OtherActor)
{
    if (m_isCharged)
	{
		auto survivor = dynamic_cast<ASurvivor*>(OtherActor);
		if (survivor)
		{
			survivor->speedup();
			StartRechargingProcess();
		}
    }
}