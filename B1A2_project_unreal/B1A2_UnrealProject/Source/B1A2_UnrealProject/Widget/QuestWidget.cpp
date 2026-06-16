// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Main/Main.h"
#include "Network/DataManager.h"

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

	if (MainToggleButton)
	{
		MainToggleButton->OnClicked.RemoveDynamic(this, &UQuestWidget::OnMainQuestToggleClicked);
		MainToggleButton->OnClicked.AddDynamic(this, &UQuestWidget::OnMainQuestToggleClicked);
	}

	if (SubToggleButton)
	{
		SubToggleButton->OnClicked.RemoveDynamic(this, &UQuestWidget::OnSubQuestToggleClicked);
		SubToggleButton->OnClicked.AddDynamic(this, &UQuestWidget::OnSubQuestToggleClicked);
	}
}

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateQuestUI();
}

void UQuestWidget::OnMainQuestToggleClicked()
{
	_isMainQuestExpaneded = !_isMainQuestExpaneded;
	UpdateQuestUI();
}

void UQuestWidget::OnSubQuestToggleClicked()
{
	_isSubQuestExpanded = !_isSubQuestExpanded;
	UpdateQuestUI();
}

void UQuestWidget::HandleUpdateQuest(bool isMain, int questID, int goalCount, ItemType itemType, int deadLine)
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
		_subQuestSlot.deadLine = deadLine;
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
		gameInstance->SendRequestQuestReward(true);

		UE_LOG(LogTemp, Display, TEXT("[QuestWidget] Main Quest Reward Requested."));
	}
}

void UQuestWidget::OnSubRewardButtonClicked()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendRequestQuestReward(false);

		UE_LOG(LogTemp, Display, TEXT("[QuestWidget] Sub Quest Reward Requested."));
	}
}

void UQuestWidget::UpdateQuestUI()
{
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance || !gameInstance->GetDataManager()) return;

	DataManager* DataMgr = gameInstance->GetDataManager();

	// Main 퀘스트
	if (_mainQuestSlot.questItem != ItemType::None)
	{
		FText ItemName = GetItemNameText(_mainQuestSlot.questItem);
		MainQuestText->SetText(FText::Format(FText::FromString(TEXT("메인: {0} {1}개 제출하기")), ItemName, FText::AsNumber(_mainQuestSlot.goalCount)));
		MainQuestProgress->SetText(FText::Format(FText::FromString(TEXT("({0} / {1})")), FText::AsNumber(_mainQuestSlot.currentCount), FText::AsNumber(_mainQuestSlot.goalCount)));

		if (_isMainQuestExpaneded)
		{
			MainDetailsContainer->SetVisibility(ESlateVisibility::Visible);

			const QuestInfo& info = DataMgr->GetMainQuestInfo(_mainQuestSlot.questID);

			MainTitleText->SetText(FText::FromString(FString::Printf(TEXT("제목: %s"), *info.title)));
			MainClientText->SetText(FText::FromString(FString::Printf(TEXT("의뢰인: %s"), *info.client)));
			MainRequestText->SetText(FText::FromString(FString::Printf(TEXT("의뢰 내용:\n%s"), *info.request)));
			MainRewardText->SetText(FText::FromString(info.reward));

			// 보상 버튼 활성화 및 완료 대사 출력
			if (_mainQuestSlot.canClaimReward)
			{
				// 퀘스트 완료 시 설명 지우기
				MainTitleText->SetVisibility(ESlateVisibility::Collapsed);
				MainClientText->SetVisibility(ESlateVisibility::Collapsed);	
				MainRequestText->SetVisibility(ESlateVisibility::Collapsed);
				MainRewardText->SetVisibility(ESlateVisibility::Collapsed);

				// 퀘스트 완료 시 버튼과 대사를 모두 노출
				if (MainRewardButton) MainRewardButton->SetVisibility(ESlateVisibility::Visible);
				if (MainCompleteText) MainCompleteText->SetVisibility(ESlateVisibility::Visible);

				MainCompleteText->SetText(FText::FromString(info.complete));
			}
			else
			{
				// 완료되지 않았다면 둘 다 숨기기
				if (MainRewardButton) MainRewardButton->SetVisibility(ESlateVisibility::Collapsed);
				if (MainCompleteText) MainCompleteText->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
		else
		{
			MainDetailsContainer->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	// Sub 퀘스트
	if (_subQuestSlot.questItem != ItemType::None)
	{
		FText ItemName = GetItemNameText(_subQuestSlot.questItem);
		SubQuestText->SetText(FText::Format(FText::FromString(TEXT("서브: {0} {1}개 제출하기")), ItemName, FText::AsNumber(_subQuestSlot.goalCount)));
		SubQuestProgress->SetText(FText::Format(FText::FromString(TEXT("({0} / {1})")), FText::AsNumber(_subQuestSlot.currentCount), FText::AsNumber(_subQuestSlot.goalCount)));
		SubDeadline->SetText(FText::Format(FText::FromString(TEXT("기한: {0}일 남음")), FText::AsNumber(_subQuestSlot.deadLine)));

		if (_isSubQuestExpanded)
		{
			SubDetailsContainer->SetVisibility(ESlateVisibility::Visible);

			const QuestInfo& info = DataMgr->GetSubQuestInfo(_subQuestSlot.questID);

			SubTitleText->SetText(FText::FromString(FString::Printf(TEXT("제목: %s"), *info.title)));
			SubClientText->SetText(FText::FromString(FString::Printf(TEXT("의뢰인: %s"), *info.client)));
			SubRequestText->SetText(FText::FromString(FString::Printf(TEXT("의뢰 내용:\n%s"), *info.request)));
			SubRewardText->SetText(FText::FromString(info.reward));

			if (_subQuestSlot.canClaimReward)
			{
				// 퀘스트 완료 시 설명 지우기
				SubTitleText->SetVisibility(ESlateVisibility::Collapsed);
				SubClientText->SetVisibility(ESlateVisibility::Collapsed);
				SubRequestText->SetVisibility(ESlateVisibility::Collapsed);
				SubRewardText->SetVisibility(ESlateVisibility::Collapsed);

				// 퀘스트 완료 시 버튼과 대사를 모두 노출
				if (SubRewardButton) SubRewardButton->SetVisibility(ESlateVisibility::Visible);
				if (SubCompleteText) SubCompleteText->SetVisibility(ESlateVisibility::Visible);

				SubCompleteText->SetText(FText::FromString(info.complete));
			}
			else
			{
				if (SubRewardButton) SubRewardButton->SetVisibility(ESlateVisibility::Collapsed);
				if (SubCompleteText) SubCompleteText->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
		else
		{
			SubDetailsContainer->SetVisibility(ESlateVisibility::Collapsed);
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
