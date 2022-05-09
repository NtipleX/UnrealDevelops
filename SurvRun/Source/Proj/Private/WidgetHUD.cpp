// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

bool UWidgetHUD::Initialize()
{
    Super::Initialize();
    UE_LOG(LogTemp, Warning, TEXT("WIDGET INITIALIZE"));
    return true;
}

void UWidgetHUD::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Warning, TEXT("WIDGET NATIVECONSTRUCT"));

}