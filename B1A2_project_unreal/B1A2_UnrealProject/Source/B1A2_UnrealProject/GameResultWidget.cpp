// Fill out your copyright notice in the Description page of Project Settings.


#include "GameResultWidget.h"

void UGameResultWidget::NativeUpdatePlayerList(const TArray<FString>& Names, const TArray<bool>& IsDeadStates)
{
    if (!VBox_PlayerList || !PlayerWidgetClass) return;

    VBox_PlayerList->ClearChildren();

    for (int32 i = 0; i < Names.Num(); ++i)
    {
        if (!IsDeadStates.IsValidIndex(i)) break;

        UPlayerResultWidget* ItemWidget = CreateWidget<UPlayerResultWidget>(this, PlayerWidgetClass);
        if (ItemWidget)
        {
            // 데이터 세팅
            ItemWidget->SetPlayerResult(Names[i], IsDeadStates[i]);

            // 정렬
            VBox_PlayerList->AddChildToVerticalBox(ItemWidget);
        }
    }
}
