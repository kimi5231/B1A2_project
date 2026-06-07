// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidget.h"
#include "Components/TextBlock.h"

void URoomWidget::SetupEntry(const FString& Title, const FText& State)
{
	if (Text_RoomTitle) Text_RoomTitle->SetText(FText::FromString(Title));
	if (Text_RoomState) Text_RoomState->SetText(State);
}
