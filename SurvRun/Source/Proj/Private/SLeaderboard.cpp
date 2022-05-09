// Fill out your copyright notice in the Description page of Project Settings.


#include "SLeaderboard.h"
#include "Misc/Timespan.h"

#define LOCTEXT_NAMESPACE "Leaderboard"

void SLeaderboard::Construct(const FArguments& Args)
{
	m_recordsAmount = Args._RecordsAmount;
	m_dataRecords = Args._DataRecords;
	m_owningController = Args._OwningController;

	TArray<FText> stringRecords;
	for(int i = 0; i < m_recordsAmount; i++)
	{
		if (i <= m_dataRecords.Num() - 1)
		{
			FTimespan time = FTimespan::FromSeconds(m_dataRecords[i]);
			stringRecords.Add(FText::FromString(time.ToString(TEXT("%m:%s.%f"))));
		}
		else
		{
			stringRecords.Add(FText::FromString("---"));
		}
	}

	const ISlateStyle& slateStyle = FCoreStyle::Get();

	FSlateFontInfo headerStyle = slateStyle.GetFontStyle("EmbossedText");
	headerStyle.Size = 48.f;

	FSlateFontInfo recordsStyle = slateStyle.GetFontStyle("EmbossedText");
	recordsStyle.Size = 24.f;


	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString("Game Over")))
				.Font(headerStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SSpacer)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(stringRecords[0])
				.Font(recordsStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(stringRecords[1])
				.Font(recordsStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(stringRecords[2])
			.Font(recordsStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(stringRecords[3])
			.Font(recordsStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(stringRecords[4])
			.Font(recordsStyle)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SSpacer)
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.OnClicked(this, &SLeaderboard::OnQuitGame)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString("Quit")))
					.Font(headerStyle)
				]
			]
		]
	];

	m_owningController->bShowMouseCursor = true;

}

FReply SLeaderboard::OnQuitGame() const
{
	m_owningController->ConsoleCommand("quit");
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE