// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerResultWidget.h"

void UPlayerResultWidget::SetPlayerResult(const FString& Name, bool bIsDead)
{
    if (Text_PlayerName)
    {
        Text_PlayerName->SetText(FText::FromString(Name));
    }

    if (Text_Status)
    {
        if (bIsDead)
        {
            Text_Status->SetText(FText::FromString(TEXT("DEAD")));
            Text_Status->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
        }
        else
        {
            Text_Status->SetText(FText::FromString(TEXT("ALIVE")));
            Text_Status->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
        }
    }
}
