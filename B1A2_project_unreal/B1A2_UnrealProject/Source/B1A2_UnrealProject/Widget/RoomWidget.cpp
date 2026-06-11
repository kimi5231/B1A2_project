// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "LobbyWidget.h"

void URoomWidget::SetupEntry(int roomID, const FString& Title, int playerCount, ULobbyWidget* parent)
{
	_roomID = roomID;
	_parentLobby = parent;

	if (Text_RoomTitle) Text_RoomTitle->SetText(FText::FromString(Title));
	if (Text_PlayerCount)
	{
		FText playerCountText = FText::Format(FText::FromString("{0}/4"), FText::AsNumber(playerCount));
		Text_PlayerCount->SetText(playerCountText);
	}
	if (CheckBox_Select) CheckBox_Select->SetIsChecked(false);
}

void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox_Select)
		CheckBox_Select->OnCheckStateChanged.AddDynamic(this, &URoomWidget::OnSelectionChanged);
}

void URoomWidget::OnSelectionChanged(bool isChecked)
{
	if (!_parentLobby) return;

	if (isChecked)
	{
		_parentLobby->SetSelectedRoom(this);
	}
}

void URoomWidget::SetSelected(bool selected)
{
	if (!CheckBox_Select) return;

	CheckBox_Select->SetIsChecked(selected);
}
