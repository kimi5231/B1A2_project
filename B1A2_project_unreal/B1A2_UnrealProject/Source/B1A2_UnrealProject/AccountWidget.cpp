// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Main/Main.h"
#include "MainMenuWidget.h"

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

void UAccountWidget::SetButtonEnable(bool enable)
{
	if (LoginButton) LoginButton->SetIsEnabled(enable);
	if (CancelButton) CancelButton->SetIsEnabled(enable);
}

void UAccountWidget::OnLoginClicked()
{
	if (!EditableText_ID) return;

	FString userID = EditableText_ID->GetText().ToString();

	// 아이디가 비었다면 리턴
	if (userID.IsEmpty())
	{
		return;
	}

	// 로그인 패킷 전송
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (gameInstance)
	{
		FTCHARToUTF8 Convert(*userID);
		std::vector<char> IdVector(Convert.Get(), Convert.Get() + Convert.Length());
		gameInstance->SendLogin(IdVector);

		//UE_LOG(LogTemp, Display, TEXT("[Login] 패킷 전송 완료"));
	}
}

void UAccountWidget::OnCancelClicked()
{
	// MainMenu 위젯의 Start, Quit 버튼 활성화
	if (MainMenuOwner)
	{
		MainMenuOwner->SetButtonEnable(true); 
	}

	// Account 창 숨기기
	RemoveFromParent();
}