// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Main/Main.h"

void UQuestWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (MainRewardButton)
	{
		MainRewardButton->OnClicked.RemoveDynamic(this, &UQuestWidget::OnMainRewardButtonClicked);
		MainRewardButton->OnClicked.AddDynamic(this, &UQuestWidget::OnMainRewardButtonClicked);
	}

	if (SubRewardButton)
	{
		SubRewardButton->OnClicked.RemoveDynamic(this, &UQuestWidget::OnSubRewardButtonClicked);
		SubRewardButton->OnClicked.AddDynamic(this, &UQuestWidget::OnSubRewardButtonClicked);
	}
}

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateQuestUI();
}

void UQuestWidget::HandleUpdateQuest(bool isMain, int questID, int goalCount, ItemType itemType)
{
	// Main 퀘스트
	if (isMain)
	{
		_mainQuestSlot.questID = questID;
		_mainQuestSlot.goalCount = goalCount;
		_mainQuestSlot.currentCount = 0;
		_mainQuestSlot.questItem = itemType;
		_mainQuestSlot.canClaimReward = false;
	}
	// Sub 퀘스트
	else
	{
		_subQuestSlot.questID = questID;
		_subQuestSlot.goalCount = goalCount;
		_subQuestSlot.currentCount = 0;
		_subQuestSlot.questItem = itemType;
		_subQuestSlot.canClaimReward = false;
	}

	UpdateQuestUI();
}

void UQuestWidget::HandleUpdateQuestProgress(bool isMain, int currentCount)
{
	if (isMain)
	{
		_mainQuestSlot.currentCount = currentCount;

		// 수집이 완료됐으면 보상 받도록 전환
		if (_mainQuestSlot.currentCount >= _mainQuestSlot.goalCount)
			_mainQuestSlot.canClaimReward = true;
	}
	else
	{
		_subQuestSlot.currentCount = currentCount;

		if (_subQuestSlot.currentCount >= _subQuestSlot.goalCount)
			_subQuestSlot.canClaimReward = true;
	}

	UpdateQuestUI();
}

void UQuestWidget::ToggleMouseMode()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	_isMouseModeActive = !_isMouseModeActive;

	if (_isMouseModeActive)
	{
		// 마우스 커서 보이게 설정
		PC->bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);

		PC->SetInputMode(InputMode);
	}
	else
	{
		// 일반 게임 모드
		PC->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

void UQuestWidget::OnMainRewardButtonClicked()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		//C_RequestQuestReward_Packet packet;
		//packet.size = sizeof(C_RequestQuestReward_Packet);
		//packet.packetID = PacketID::C_RequestQuestReward;
		//packet.isMain = true; // 메인 퀘스트 보상 요청

		//gameInstance->SendPacket(&packet);

		UE_LOG(LogTemp, Display, TEXT("[QuestWidget] Main Quest Reward Requested."));
	}
}

void UQuestWidget::OnSubRewardButtonClicked()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		//C_RequestQuestReward_Packet packet;
		//packet.size = sizeof(C_RequestQuestReward_Packet);
		//packet.packetID = PacketID::C_RequestQuestReward;
		//packet.isMain = false; // 서브 퀘스트 보상 요청

		//gameInstance->SendPacket(&packet);

		UE_LOG(LogTemp, Display, TEXT("[QuestWidget] Sub Quest Reward Requested."));
	}
}

void UQuestWidget::UpdateQuestUI()
{
	if (_mainQuestSlot.questItem != ItemType::None)
	{
		FText ItemName = GetItemNameText(_mainQuestSlot.questItem);
		MainQuestText->SetText(FText::Format(FText::FromString(TEXT("메인: {0} {1}ea 가져오기")), ItemName, FText::AsNumber(_mainQuestSlot.goalCount)));
		MainQuestProgress->SetText(FText::Format(FText::FromString(TEXT("({0} / {1})")), FText::AsNumber(_mainQuestSlot.currentCount), FText::AsNumber(_mainQuestSlot.goalCount)));

		// 보상 수령이 활성화되면 버튼을 노출, 아니면 숨기기
		if (MainRewardButton)
		{
			MainRewardButton->SetVisibility(_mainQuestSlot.canClaimReward ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}
	}

	if (_subQuestSlot.questItem != ItemType::None)
	{
		FText ItemName = GetItemNameText(_subQuestSlot.questItem);
		SubQuestText->SetText(FText::Format(FText::FromString(TEXT("일반: {0} {1}ea 가져오기")), ItemName, FText::AsNumber(_subQuestSlot.goalCount)));
		SubQuestProgress->SetText(FText::Format(FText::FromString(TEXT("({0} / {1})")), FText::AsNumber(_subQuestSlot.currentCount), FText::AsNumber(_subQuestSlot.goalCount)));

		if (SubRewardButton)
		{
			SubRewardButton->SetVisibility(_subQuestSlot.canClaimReward ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		}
	}
}

FText UQuestWidget::GetItemNameText(ItemType Type)
{
	switch (Type)
	{
	case ItemType::CardboardBox:  return FText::FromString(TEXT("cardboard box"));
	case ItemType::GoldBar:   return FText::FromString(TEXT("goldbar"));
	case ItemType::RubberDuck:    return FText::FromString(TEXT("rubber duck"));
	case ItemType::PlasticCrate:    return FText::FromString(TEXT("plastic crate"));
	case ItemType::Screw:    return FText::FromString(TEXT("screw"));
	case ItemType::PirateHat:    return FText::FromString(TEXT("pirate hat"));
	case ItemType::HardHat:    return FText::FromString(TEXT("hard hat"));
	case ItemType::EngineCore:    return FText::FromString(TEXT("engine core"));
	case ItemType::ScrapMetal:    return FText::FromString(TEXT("scrap metal"));
	case ItemType::EmptyCan:    return FText::FromString(TEXT("empty can"));
	default: return FText::FromString(TEXT("아이템"));
	}
}
