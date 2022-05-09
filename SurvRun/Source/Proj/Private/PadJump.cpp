// Fill out your copyright notice in the Description page of Project Settings.


#include "PadJump.h"
#include "GameFramework/Character.h"

void APadJump::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character)
	{
		//character->face
		character->LaunchCharacter(FVector(0, 0, 1250), false, true);
	}

}