// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBarWidget.h"
#include "ToolSlotWidget.h"
//#include "Components/UniformGridPanel.h"
//#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UToolBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SlotBox || !ToolSlotClass)
		return;

	for (int32 i = 0; i < 4; ++i)
	{
		UToolSlotWidget* slot = CreateWidget<UToolSlotWidget>(this, ToolSlotClass);

		if (slot)
		{
			UVerticalBoxSlot* spacingSlot = SlotBox->AddChildToVerticalBox(slot);

			if (spacingSlot)
			{
				spacingSlot->SetPadding(FMargin(0.0f, 20.0f, 0.0f, 20.0f));
				spacingSlot->SetHorizontalAlignment(HAlign_Center);
			}
			ToolSlots.Add(slot);
		}
	}

	ToolSlots[0]->SetSelected(true);	// 첫 번째 슬롯 기본 선택
}

int32 UToolBarWidget::AddTool(int id, ItemType type, float weight, int cost)
{
	for (int32 i = 0; i < ToolSlots.Num(); ++i)
	{
		if (ToolSlots[i] && ToolSlots[i]->isEmpty)
		{
			ToolSlots[i]->SetSlotInfo(id, type, weight, cost);
			return i;
		}
	}
	
	return -1;	// 빈 슬롯이 없을 경우 
}

void UToolBarWidget::ChangeSelection(bool forward)
{
	if (ToolSlots.Num() == 0)
		return;

	// 기존 하이라이트 끔
	if (ToolSlots.IsValidIndex(_currentSelectedIndex))
		ToolSlots[_currentSelectedIndex]->SetSelected(false);

	// 인덱스 계산
	if (forward)
		_currentSelectedIndex = (_currentSelectedIndex + 1) % ToolSlots.Num();
	else
		_currentSelectedIndex = (_currentSelectedIndex - 1 + ToolSlots.Num()) % ToolSlots.Num();

	// 선택된 슬롯 하이라이트 켬
	if (ToolSlots.IsValidIndex(_currentSelectedIndex))
	{
		ToolSlots[_currentSelectedIndex]->SetSelected(true);

		UE_LOG(LogTemp, Display, TEXT("[ToolBar] Highlight!"));
	}
}

void UToolBarWidget::SetSelectedIndex(int32 index)
{
	if (!ToolSlots.IsValidIndex(index)) return;

	// 기존 하이라이트 끄기
	if (ToolSlots.IsValidIndex(_currentSelectedIndex))
		ToolSlots[_currentSelectedIndex]->SetSelected(false);

	// 새 인덱스로 변경 및 하이라이트 켜기
	_currentSelectedIndex = index;
	ToolSlots[_currentSelectedIndex]->SetSelected(true);
}

FDroppedItemInfo UToolBarWidget::GetSelectedToolBarTool()
{
	FDroppedItemInfo info;

	if (ToolSlots.IsValidIndex(_currentSelectedIndex) && !ToolSlots[_currentSelectedIndex]->isEmpty)
	{
		info.itemID = ToolSlots[_currentSelectedIndex]->GetToolID();
		info.type = ToolSlots[_currentSelectedIndex]->GetToolType();
		info.weight = ToolSlots[_currentSelectedIndex]->GetToolWeight();
		info.cost = ToolSlots[_currentSelectedIndex]->GetToolCost();
		info.isValid = true;
	}

	return info;
}

void UToolBarWidget::RemoveToolByID(int32 toolID)
{
	for (UToolSlotWidget* slot : ToolSlots)
	{
		if (slot && !slot->isEmpty && slot->GetToolID() == toolID)
		{
			slot->ClearSlot();
			return;
		}
	}
}

