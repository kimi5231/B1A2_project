// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Host) Button_Host->OnClicked.AddDynamic(this, &ULobbyWidget::OnHostClicked);
	if (Button_Join) Button_Join->OnClicked.AddDynamic(this, &ULobbyWidget::OnJoinClicked);
	if (Button_Leave) Button_Leave->OnClicked.AddDynamic(this, &ULobbyWidget::OnLeaveClicked);
}

void ULobbyWidget::OnHostClicked()
{
	// C_CreateRoom 价脚
	UE_LOG(LogTemp, Log, TEXT("Host"));
}

void ULobbyWidget::OnJoinClicked()
{
	// C_EnterRoom 价脚
	UE_LOG(LogTemp, Log, TEXT("Join"));
}

void ULobbyWidget::OnLeaveClicked()
{
	// C_Logout 价脚
	UE_LOG(LogTemp, Log, TEXT("Leave"));
}

void ULobbyWidget::UpdateLobbyPlayers(const TArray<FString>& PlayerNames)
{
}

void ULobbyWidget::UpdateRoomInfo(const RoomDTO& RoomData)
{
	// 规 力格
	if (Text_RoomTitle)
	{
		FString titleStr = TEXT("No Title");

		if (!RoomData.roomTitle.empty())
		{
			std::string StdTitle(RoomData.roomTitle.begin(), RoomData.roomTitle.end());
			titleStr = FString(UTF8_TO_TCHAR(StdTitle.c_str()));
		}

		Text_RoomTitle->SetText(FText::FromString(titleStr));
	}

	// 规 惑怕
	if (Text_RoomState)
	{
		FText stateStr = FText::FromString(TEXT("Unknown"));

		switch (RoomData.roomState)
		{
		case RoomState::Reusable: stateStr = State_Reusable; break;
		case RoomState::Wait:     stateStr = State_Wait;     break;
		case RoomState::Lock:     stateStr = State_Lock;     break;
		case RoomState::Play:     stateStr = State_Play;     break;
		case RoomState::Full:     stateStr = State_Full;     break;
		}

		Text_RoomState->SetText(stateStr);
	}
}
