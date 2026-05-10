// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusWidget.h"

void UPlayerStatusWidget::SetBattery(float Ratio)
{
    if (BatteryBar) 
    {
        BatteryBar->SetPercent(Ratio);

        // 20% 이하일 때 빨간색으로 변경
        FLinearColor color = (Ratio <= 0.2f) ? FLinearColor::Red : FLinearColor::Yellow;
        BatteryBar->SetFillColorAndOpacity(color);
    }
}
