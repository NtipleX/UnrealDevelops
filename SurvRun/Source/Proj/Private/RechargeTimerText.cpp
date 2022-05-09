// Fill out your copyright notice in the Description page of Project Settings.


#include "RechargeTimerText.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARechargeTimerText::ARechargeTimerText()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.1f);
	InitialLifeSpan = 15.f;
}

void ARechargeTimerText::LookAt(AActor* target)
{
	FVector Forward = target->GetActorLocation() - GetActorLocation();
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
	SetActorRotation(Rot, ETeleportType::TeleportPhysics);
}

void ARechargeTimerText::Tick(float delta)
{
	Super::Tick(delta);
	GetTextRender()->SetText(FText::AsNumber(static_cast<int8>(CreationTime + InitialLifeSpan - GetWorld()->GetRealTimeSeconds())));
	LookAt(GetWorld()->GetFirstPlayerController()->GetPawn());
}