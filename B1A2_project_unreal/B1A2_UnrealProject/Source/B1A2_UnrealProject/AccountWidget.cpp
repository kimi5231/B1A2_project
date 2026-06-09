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
		FTCHARToUTF8 Convert(*UserID);
		std::vector<char> IdVector(Convert.Get(), Convert.Get() + Convert.Length());
		gameInstance->SendLogin(IdVector);

		//UE_LOG(LogTemp, Display, TEXT("[Login] 패킷 전송 완료"));
	}
}

void UAccountWidget::OnCancelClicked()
{
	// Account 창 숨기기
	RemoveFromParent();
}