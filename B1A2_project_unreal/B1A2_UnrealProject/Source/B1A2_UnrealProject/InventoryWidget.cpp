// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeSlots();	// À§Á¬ÀÌ »ý¼ºµÇ¸é ¹Ù·Î ½½·Ô »ý¼º
}

void UInventoryWidget::AddItem(int id, ItemType type, float weight)
{
	// ºó ½½·Ô Ã£±â
	for (UInventorySlotWidget* slot : SlotArray)
	{
		if (slot && slot->isEmpty)
		{
			slot->SetSlotInfo(id, type, weight);
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
	for (int32 i = 0; i < 49; ++i)
	{
		UInventorySlotWidget* slot = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
		if (slot)
		{
			SlotGrid->AddChildToUniformGrid(slot, i / 7, i % 7);
			SlotArray.Add(slot);
		}
	}
}
