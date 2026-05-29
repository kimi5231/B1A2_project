// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"

#include "QuestWidget.generated.h"

class UTextBlock;
class UButton;

// 퀘스트 목록 데이터
struct FQuestData
{
    unsigned char questID = 0;
    unsigned char goalCount = 0;
    unsigned char currentCount = 0;
    ItemType questItem = ItemType::None;
    bool canClaimReward = false;
};
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;

public:
    // 서버 패킷 수신 시 호출
    void HandleUpdateQuest(bool isMain, int questID, int goalCount, ItemType itemType);
    void HandleUpdateQuestProgress(bool isMain,int CurrentCount);

    // Q 입력 인풋 모드 토글
    void ToggleMouseMode();

    // 보상 받기 클릭시 호출
    UFUNCTION() void OnMainRewardButtonClicked();
    UFUNCTION() void OnSubRewardButtonClicked();

private:
    void UpdateQuestUI();
    FText GetItemNameText(ItemType Type);

protected:
    // 메인 퀘스트
    UPROPERTY(meta = (BindWidget))
    UTextBlock* MainQuestText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MainQuestProgress;

    UPROPERTY(meta = (BindWidget))
    UButton* MainRewardButton;

    // 서브 퀘스트
    UPROPERTY(meta = (BindWidget))
    UTextBlock* SubQuestText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SubQuestProgress;

    UPROPERTY(meta = (BindWidget))
    UButton* SubRewardButton;

private:
    // 퀘스트 상태 저장
    FQuestData _mainQuestSlot;
    FQuestData _subQuestSlot;

    // 마우스 조작 모드 활성화 여부
    bool _isMouseModeActive = false;
};
