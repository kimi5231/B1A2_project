// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSlotWidget.h"

void UToolSlotWidget::SetSlotInfo(int32 id, ItemType type)
{
	UTexture2D* texture = nullptr;

	switch (type)
	{
	case ItemType::Cutlass:
		texture = CutlassIcon; break;
	case ItemType::Blaster:
		texture = BlasterIcon; break;
	case ItemType::Key:
		texture = KeyIcon; break;
	case ItemType::Lantern:
		texture = LanternIcon; break;
	}

	if (!texture)
		UE_LOG(LogTemp, Error, TEXT("[ToolBar] Texture is NULL for ItemType: %d"), (int32)type);

	// 아이콘
	if (ToolIcon && texture)
	{
		ToolIcon->SetBrushFromTexture(texture);
		ToolIcon->SetRenderOpacity(1.0f);
		ToolIcon->SetVisibility(ESlateVisibility::Visible);
	}

	// 슬롯 채움
	isEmpty = false;

	// ID, Type
	SetToolID(id);
	SetToolType(type);
}

void UToolSlotWidget::SetSelected(bool isSelected)
{
	if (!SelectionHighlight)
		return;

	if (isSelected)
		SelectionHighlight->SetVisibility(ESlateVisibility::Visible);
	else
		SelectionHighlight->SetVisibility(ESlateVisibility::Hidden);
}

void UToolSlotWidget::ClearSlot()
{
	isEmpty = true;
	_toolID = -1;

	if (ToolIcon)
	{
		ToolIcon->SetVisibility(ESlateVisibility::Hidden);
		ToolIcon->SetBrushFromTexture(nullptr);
	}
}