// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainMenuWidget.h"
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

void UMainMenuWidget::SetButtonEnable(bool enable)
{
	if (StartButton) StartButton->SetIsEnabled(enable);
	if (QuitButton) QuitButton->SetIsEnabled(enable);

}

void UMainMenuWidget::SetAccountButtonEnable(bool enable)
{
	if (AccountWidgetInstance)
	{
		AccountWidgetInstance->SetButtonEnable(enable);
	}
}

void UMainMenuWidget::RemoveAccountWidget()
{
	if (AccountWidgetInstance)
	{
		AccountWidgetInstance->RemoveFromParent();
	}
}

void UMainMenuWidget::OnStartClicked()
{
	// Account 창을 띄우고, Start & Quit 버튼 비활성화
	if (StartButton)	StartButton->SetIsEnabled(false);
	if (QuitButton)		QuitButton->SetIsEnabled(false);

	if (AccountWidgetClass)
	{
		if (!AccountWidgetInstance)
		{
			AccountWidgetInstance = CreateWidget<UAccountWidget>(this, AccountWidgetClass);
		}

		if (AccountWidgetInstance && !AccountWidgetInstance->IsInViewport())
		{
			AccountWidgetInstance->SetMainMenuOwner(this);
			AccountWidgetInstance->SetButtonEnable(true);
			AccountWidgetInstance->AddToViewport();
		}
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	// 게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}