// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"
#include "ToolBarWidget.h"

#include "InventoryWidget.generated.h"

class UInventorySlotWidget;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;	
	// NativeConstruct는 AddToViewport로 처음 그려질 때 호출됨 -> 인벤토리를 한 번도 안 그렸으면 초기화가 안 됐던 것!!

public:
	//void UpdateInventoryUI(TArray<UTexture2D*> texture);
	void AddItem(int id, ItemType type, float weight, int32 cost);
	void InitializeSlots();

	// 버튼 입력 시 슬롯 이동
	void SelectNextSlot();	// Input C
	void SelectPrevSlot();	// Input X
	
	// 위젯을 열 때 선택된 슬롯 처음 위치로 초기화
	void ResetSelectSlot();

	// 버리기 키를 입력했을 때, 현재 선택된 슬롯의 아이템 정보 리턴
	FDroppedItemInfo GetSelectedInventoryItem();
	// 서버에서 버리기 명령이 오면 인벤에서 삭제
	void RemoveItemByID(int32 itemID);

protected:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* SlotGrid;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<UInventorySlotWidget*> SlotArray;

private:
	int32 _currentSelectedIndex = 0;
};
