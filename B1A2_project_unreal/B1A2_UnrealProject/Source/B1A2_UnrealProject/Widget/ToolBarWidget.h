// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"

struct FDroppedItemInfo
{
	int32 itemID = -1;
	ItemType type = ItemType::EmptyCan;
	float weight = 0.0f;
	bool isValid = false;
};

#include "ToolBarWidget.generated.h"

class UVerticalBox;
class UToolSlotWidget;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UToolBarWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:
	int32 AddTool(int id, ItemType type, float weight);
	void ChangeSelection(bool forward);		// 휠 방향에 따라 변경
	void SetSelectedIndex(int32 index);	// 획득시 인덱스 강제 변경

	// 버리기 키를 입력했을 때, 현재 선택된 슬롯의 장비 정보 리턴
	FDroppedItemInfo GetSelectedToolBarTool();
	// 서버에서 버리기 명령이 오면 툴바에서 삭제
	void RemoveToolByID(int32 toolID);

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SlotBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ToolSlotClass;

	UPROPERTY()
	TArray<UToolSlotWidget*> ToolSlots;

	int32 _currentSelectedIndex = 0;
};
 