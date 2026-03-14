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

void UToolBarWidget::ChangeSelection(bool forward)
{
}

