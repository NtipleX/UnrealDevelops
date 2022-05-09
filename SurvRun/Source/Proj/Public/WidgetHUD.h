// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_API UWidgetHUD : public UUserWidget
{
	GENERATED_BODY()
public:

	//UPROPERTY(EditAnywhere)
	//UButton* btn;

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
};
