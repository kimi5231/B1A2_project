// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "AccountWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Main/Main.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::OnStartClicked()
{
	// 서버 연결
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (gameInstance)
	{
		gameInstance->ConnectServer();
	}

	if (AccountWidgetClass)
	{
		if (!AccountWidgetInstance)
		{
			AccountWidgetInstance = CreateWidget<UAccountWidget>(this, AccountWidgetClass);
		}

		if (AccountWidgetInstance && !AccountWidgetInstance->IsInViewport())
		{
			AccountWidgetInstance->AddToViewport();
		}
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	// 게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}