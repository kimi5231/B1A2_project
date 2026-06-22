// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Main/Main.h"
#include "Widget/MainMenuWidget.h"

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
	// 선택된 방이 있는지
	if (SelectedRoomWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Lobby] Join Button Clicked, But is not selected room"));
		return;
	}

	// 방의 ID 추출
	int targetRoomID = SelectedRoomWidget->GetRoomID();

	// 패킷 송신
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendEnterRoom(targetRoomID);
		UE_LOG(LogTemp, Log, TEXT("[Lobby] Join Button Clicked! Send Enter Room, RoomID: %d"), targetRoomID);
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

	if (MainMenuOwner)
	{
		// Account 창 지움
		MainMenuOwner->RemoveAccountWidget();
		// MainMenu의 버튼 활성화
		MainMenuOwner->SetButtonEnable(true);
	}

	// Lobby 창 숨기기
	RemoveFromParent();
}

void ULobbyWidget::UpdateRoomList(const std::vector<RoomDTO>& roomList)
{
	if (!ScrollBox_RoomList) return;

	// 이전 방 목록 청소
	SelectedRoomWidget = nullptr;
	ScrollBox_RoomList->ClearChildren();

	if (!RoomEntryWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("RoomEntryWidgetClass is not choose"));
		return;
	}

	if (roomList.empty())
	{
		UE_LOG(LogTemp, Display, TEXT("[UI] Room list is empty. Screen cleared."));
		return;
	}

	// 방 목록 배열을 순회하며 동적으로 자식 위젯 생성하기
	for (const RoomDTO& RoomData : roomList)
	{
		// Title
		FString titleStr = TEXT("No Title");
		if (!RoomData.roomTitle.empty())
		{
			std::string StdTitle(RoomData.roomTitle.begin(), RoomData.roomTitle.end());
			titleStr = FString(UTF8_TO_TCHAR(StdTitle.c_str()));
		}

		UUserWidget* NewEntryWidget = CreateWidget<UUserWidget>(GetWorld(), RoomEntryWidgetClass);
		if (NewEntryWidget)
		{
			URoomWidget* RoomWidget = Cast<URoomWidget>(NewEntryWidget);
			if (RoomWidget)
			{
				RoomWidget->SetupEntry(RoomData.roomID, titleStr, RoomData.playerCount, this);
				ScrollBox_RoomList->AddChild(NewEntryWidget);

			}
		}
	}
}

void ULobbyWidget::SetSelectedRoom(URoomWidget* newSelected)
{
	// 이전에 선택된 위젯이 있다면 체크 해제
	if (SelectedRoomWidget && SelectedRoomWidget != newSelected)
	{
		SelectedRoomWidget->SetSelected(false);
	}

	// 새로운 위젯 등록
	SelectedRoomWidget = newSelected;
}
