// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Widgets/SCompoundWidget.h"

class PROJ_API SLeaderboard : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLeaderboard) {}
	SLATE_ARGUMENT(TArray<float>, DataRecords)
	SLATE_ARGUMENT(int32, RecordsAmount)
	SLATE_ARGUMENT(TWeakObjectPtr<class APlayerController>, OwningController)
	SLATE_END_ARGS()

		//TArray<float> DataRecords;

	void Construct(const FArguments& Args);

	int32 m_recordsAmount;
	TArray<float> m_dataRecords;
	TWeakObjectPtr<APlayerController> m_owningController;

	virtual bool SupportsKeyboardFocus() const override { return true; };
	FReply OnQuitGame() const;

};
