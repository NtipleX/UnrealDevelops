// Fill out your copyright notice in the Description page of Project Settings.


#include "PainVolume.h"
#include "Survivor.h"

APainVolume::APainVolume() : Super(), m_damageInterval(5.f), m_timePassed(0.f), m_damageValue(1.f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickInterval(1.f);
}

void APainVolume::ActorEnteredVolume(class AActor* Other)
{
	Super::ActorEnteredVolume(Other);
	auto pawn = Cast<ASurvivor>(Other);
	if (pawn)
		m_player = pawn;
}

void APainVolume::BeginPlay()
{
	Super::BeginPlay();
}

void APainVolume::Tick(float delta)
{
	Super::Tick(delta);

	m_timePassed += delta;
	if (m_timePassed >= m_damageInterval)
	{
		m_timePassed = 0.f;
		m_damageValue *= 1.1;
	}

	if (m_player)
		m_player->TakeDamage(m_damageValue, FDamageEvent(), m_player->GetController(), this);
}

