// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvRunMode.h"
#include "Survivor.h"
#include "SLeaderboard.h"
#include "SurvSaveSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"


ASurvRunMode::ASurvRunMode() : GameSaveName("Save1")
{}

void ASurvRunMode::playerDeath(ASurvivor* player)
{
	SetPause(GetWorld()->GetFirstPlayerController());
	float timeAlive = GetWorld()->GetTimeSeconds() - player->CreationTime;

	USaveGame* rawGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(GameSaveName, 0))
	{
		rawGameObject = UGameplayStatics::LoadGameFromSlot(GameSaveName, 0);
	}
	else
	{
		rawGameObject = UGameplayStatics::CreateSaveGameObject(USurvSaveSystem::StaticClass());
	}

	USurvSaveSystem* gameObject = Cast<USurvSaveSystem>(rawGameObject);
	if (gameObject)
	{
		if (gameObject->saveToLeaderboard(timeAlive))
			SLOG(TEXT("New record!"));
		if (!UGameplayStatics::SaveGameToSlot(gameObject, GameSaveName, 0))
			SLOG(TEXT("Game save failed!"));
		gameObject->printAll();
	}
	GameOverEvent(timeAlive);
	/////////////////////////////////////
	
	auto widget =
		SNew(SLeaderboard)
		.DataRecords(gameObject->m_aliveTimeRecords)
		.RecordsAmount(gameObject->m_recNumber)
		.OwningController(GetWorld()->GetFirstPlayerController())
		;

	GEngine->GameViewport->AddViewportWidgetContent(widget);

}