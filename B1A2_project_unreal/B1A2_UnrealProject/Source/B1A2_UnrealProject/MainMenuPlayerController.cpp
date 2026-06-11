// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Main/Main.h"
#include "LobbyWidget.h"
#include "MainMenuWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 마우스 커서 보이도록 설정
	SetShowMouseCursor(true);

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	// 메인 메뉴 위젯
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
		}
	}
}

void AMainMenuPlayerController::HandleLoginResult(LoginResult result)
{
	if (result == LoginResult::Sucess)
	{
		// 로비 위젯 생성 & 띄우기
		if (LobbyWidgetClass)
		{
			if (!LobbyWidgetInstance)
			{
				LobbyWidgetInstance = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
			}

			if (LobbyWidgetInstance && !LobbyWidgetInstance->IsInViewport())
			{
				LobbyWidgetInstance->AddToViewport();
			}
		}

		UMainMenuWidget* MainMenuUI = Cast<UMainMenuWidget>(MainMenuWidgetInstance);
		ULobbyWidget* LobbyUI = Cast<ULobbyWidget>(LobbyWidgetInstance);

		if (MainMenuUI)
		{
			// 메인 메뉴 버튼 비활성화
			MainMenuUI->SetAccountButtonEnable(false);

			// 레퍼런스 저장
			if (LobbyUI)
			{
				LobbyUI->SetMainMenuOwner(MainMenuUI);
			}
		}
	}
	else if (result == LoginResult::Failed)
	{
		// 다시 입력하세요 위젯을 1.5초 띄우고 지움
		if (FailureWidgetClass && !FailureWidgetInstance)
		{
			FailureWidgetInstance = CreateWidget<UUserWidget>(this, FailureWidgetClass);
			if (FailureWidgetInstance)
			{
				FailureWidgetInstance->AddToViewport();

				GetWorldTimerManager().SetTimer(failureTimerHandle, this, &AMainMenuPlayerController::HideFailureWidget, 1.5f, false);
			}
		}
	}
}

void AMainMenuPlayerController::HandleCurrentRoomList(const std::vector<RoomDTO>& roomList)
{
	if (LobbyWidgetInstance)
	{
		ULobbyWidget* LobbyUI = Cast<ULobbyWidget>(LobbyWidgetInstance);
		if (LobbyUI)
		{
			LobbyUI->UpdateRoomList(roomList);
		}
	}
}

void AMainMenuPlayerController::HideFailureWidget()
{
	if (FailureWidgetInstance)
	{
		FailureWidgetInstance->RemoveFromParent();
		FailureWidgetInstance = nullptr;
	}
}
