// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "RoomWidget.h"
#include "Main/Main.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Host) Button_Host->OnClicked.AddDynamic(this, &ULobbyWidget::OnHostClicked);
	if (Button_Join) Button_Join->OnClicked.AddDynamic(this, &ULobbyWidget::OnJoinClicked);
	if (Button_Leave) Button_Leave->OnClicked.AddDynamic(this, &ULobbyWidget::OnLeaveClicked);
}

void ULobbyWidget::OnHostClicked()
{
	// C_CreateRoom 송신
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendCreateRoom();
		UE_LOG(LogTemp, Log, TEXT("[Lobby] Send Create Room Packet!"));
	}
}

void ULobbyWidget::OnJoinClicked()
{
	// C_EnterRoom 송신
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		//gameInstance->SendEnterRoom();
		UE_LOG(LogTemp, Log, TEXT("[Lobby] Send Enter Room Packet!"));
	}
}

void ULobbyWidget::OnLeaveClicked()
{
	// C_Logout 송신
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendLogout();

		UE_LOG(LogTemp, Log, TEXT("[Lobby] Send LogOut Packet!"));
	}
}

void ULobbyWidget::UpdateRoomList(const std::vector<RoomDTO>& roomList)
{
	if (!ScrollBox_RoomList) return;

	// 이전 방 목록 청소
	ScrollBox_RoomList->ClearChildren();

	if (!RoomEntryWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("RoomEntryWidgetClass is not choose"));
		return;
	}

	// 방 목록 배열을 순회하며 동적으로 자식 위젯 생성하기
	for (const RoomDTO& RoomData : roomList)
	{
		FString titleStr = TEXT("No Title");
		if (!RoomData.roomTitle.empty())
		{
			std::string StdTitle(RoomData.roomTitle.begin(), RoomData.roomTitle.end());
			titleStr = FString(UTF8_TO_TCHAR(StdTitle.c_str()));
		}

		FText stateStr = FText::FromString(TEXT("Unknown"));
		switch (RoomData.roomState)
		{
		case RoomState::Reusable: stateStr = State_Reusable; break;
		case RoomState::Wait:     stateStr = State_Wait;     break;
		case RoomState::Play:     stateStr = State_Play;     break;
		case RoomState::Full:     stateStr = State_Full;     break;
		}

		UUserWidget* NewEntryWidget = CreateWidget<UUserWidget>(GetWorld(), RoomEntryWidgetClass);
		if (NewEntryWidget)
		{
			URoomWidget* RoomWidget = Cast<URoomWidget>(NewEntryWidget);
			if (RoomWidget)
			{
				RoomWidget->SetupEntry(titleStr, stateStr);
			}

			ScrollBox_RoomList->AddChild(NewEntryWidget);
		}
	}
}