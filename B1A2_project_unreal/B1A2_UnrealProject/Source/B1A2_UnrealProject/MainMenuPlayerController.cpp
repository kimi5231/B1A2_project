// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Main/Main.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 서버 연결
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (gameInstance)
	{
		gameInstance->ConnectServer();
	}

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
