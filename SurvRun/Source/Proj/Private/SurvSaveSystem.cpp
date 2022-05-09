// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvSaveSystem.h"

#include <functional>


USurvSaveSystem::USurvSaveSystem() : m_recNumber(5)
{}

bool USurvSaveSystem::saveToLeaderboard(float currentTimeAlive)
{
    if (m_aliveTimeRecords.Num() < m_recNumber)
    {
        m_aliveTimeRecords.Add(currentTimeAlive);
        m_aliveTimeRecords.Sort([](const float& a, const float& b) {return a > b; });
        return true;
    }

    for (int i = 0; i < m_recNumber; i++)
    {
        if (m_aliveTimeRecords[i] < currentTimeAlive)
        {
            m_aliveTimeRecords.Insert(currentTimeAlive, i);
            m_aliveTimeRecords.RemoveAt(m_recNumber);
            return true;
        }
    }
    return false;
}

void USurvSaveSystem::printAll()
{
    UE_LOG(LogTemp, Warning, TEXT("Printing"));
    for(auto item : m_aliveTimeRecords)
    {
        UE_LOG(LogTemp, Warning, TEXT("%f"), item);
    }
}