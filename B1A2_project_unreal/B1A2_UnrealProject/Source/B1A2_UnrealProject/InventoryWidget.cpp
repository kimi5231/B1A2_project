// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SlotWidgetClass || !SlotGrid)
		return;

	SlotGrid->ClearChildren();
	SlotArray.Empty();

	for (int32 i = 0; i < 49; ++i)
	{
		UInventorySlotWidget* slot = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);

		if (slot)
		{
			int32 row = i / 7;
			int32 col = i % 7;

			SlotGrid->AddChildToUniformGrid(slot, row, col);
			SlotArray.Add(slot);
		}
	}
}
