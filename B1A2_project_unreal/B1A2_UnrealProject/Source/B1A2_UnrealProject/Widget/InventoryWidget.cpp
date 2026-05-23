// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeSlots();	// 위젯이 생성되면 바로 슬롯 생성
}

void UInventoryWidget::AddItem(int id, ItemType type, float weight, int32 cost)
{
	// 빈 슬롯 찾기
	for (UInventorySlotWidget* slot : SlotArray)
	{
		if (slot && slot->isEmpty)
		{
			slot->SetSlotInfo(id, type, weight, cost);
			return;
		}
	}
}

void UInventoryWidget::InitializeSlots()
{
	if (SlotArray.Num() > 0) 
		return;

	if (!SlotWidgetClass || !SlotGrid) 
		return;

	SlotGrid->ClearChildren();
	for (int32 i = 0; i < 25; ++i)
	{
		UInventorySlotWidget* slot = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
		if (slot)
		{
			SlotGrid->AddChildToUniformGrid(slot, i / 5, i % 5);
			SlotArray.Add(slot);
		}
	}
}

void UInventoryWidget::SelectNextSlot()
{
	// 이전 선택 해제하기
	if (SlotArray.IsValidIndex(_currentSelectedIndex))
		SlotArray[_currentSelectedIndex]->SetSelected(false);

	// 인덱스 계산
	_currentSelectedIndex = (_currentSelectedIndex + 1) % SlotArray.Num();	// 0 ~ 25

	// 새 슬롯 선택하기
	UInventorySlotWidget* slot = SlotArray[_currentSelectedIndex];
	if (slot)
	{
		slot->SetSelected(true);
	}
}

void UInventoryWidget::SelectPrevSlot()
{
	// 이전 선택 해제하기
	if (SlotArray.IsValidIndex(_currentSelectedIndex))
		SlotArray[_currentSelectedIndex]->SetSelected(false);

	// 인덱스 계산
	_currentSelectedIndex = (_currentSelectedIndex - 1 + SlotArray.Num()) % SlotArray.Num();	// 0 ~ 25

	// 새 슬롯 선택하기
	UInventorySlotWidget* slot = SlotArray[_currentSelectedIndex];
	if (slot)
	{
		slot->SetSelected(true);
	}
}

void UInventoryWidget::ResetSelectSlot()
{
	// 기존 선택 슬롯 해제
	if (SlotArray.IsValidIndex(_currentSelectedIndex))
		SlotArray[_currentSelectedIndex]->SetSelected(false);

	_currentSelectedIndex = 0;

	if (SlotArray.IsValidIndex(_currentSelectedIndex))
	{
		SlotArray[_currentSelectedIndex]->SetSelected(true);
	}
}

FDroppedItemInfo UInventoryWidget::GetSelectedInventoryItem()
{
	FDroppedItemInfo info;

	if (SlotArray.IsValidIndex(_currentSelectedIndex) && !SlotArray[_currentSelectedIndex]->isEmpty)
	{
		info.itemID = SlotArray[_currentSelectedIndex]->GetItemID();
		info.type = SlotArray[_currentSelectedIndex]->GetItemType();
		info.weight = SlotArray[_currentSelectedIndex]->GetItemWeight();
		info.cost = SlotArray[_currentSelectedIndex]->GetItemCost();
		info.isValid = true;
	}

	return info;
}

void UInventoryWidget::RemoveItemByID(int32 itemID)
{
	for (UInventorySlotWidget* slot : SlotArray)
	{
		if (slot && !slot->isEmpty && slot->GetItemID() == itemID)
		{
			slot->ClearSlot();
			return;
		}
	}
}
