// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Main/Main.h"

void UAccountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &UAccountWidget::OnLoginClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UAccountWidget::OnCancelClicked);
	}
}

void UAccountWidget::OnLoginClicked()
{
	if (!EditableText_ID) return;

	FString UserID = EditableText_ID->GetText().ToString();

	if (UserID.IsEmpty())
	{
		// 아이디가 비어있을 때의 예외 처리
		// 경고창 띄우기??
		return;
	}

	// 로그인 패킷 전송
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (gameInstance)
	{
		
	}
}

void UAccountWidget::OnCancelClicked()
{
	// Account 창 숨기기
	RemoveFromParent();
}