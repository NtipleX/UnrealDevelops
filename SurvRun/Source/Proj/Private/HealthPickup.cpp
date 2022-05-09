// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Survivor.h"

AHealthPickup::AHealthPickup() : Super()
{}

void AHealthPickup::applyPickupToPawn(AActor* pawn)
{
    auto survivor = Cast<ASurvivor>(pawn);
    if(survivor)
    {
        Super::applyPickupToPawn(pawn);
        this->SetActorHiddenInGame(true);
        this->Destroy();
        survivor->healup(10.f);
    }
}