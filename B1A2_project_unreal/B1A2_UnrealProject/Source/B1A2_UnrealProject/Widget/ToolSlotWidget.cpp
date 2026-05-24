// Fill out your copyright notice in the Description page of Project Settings.
#include "ToolSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UToolSlotWidget::SetSlotInfo(int32 id, ItemType type, float weight, int32 cost)
{
	UTexture2D* texture = nullptr;

	switch (type)
	{
	case ItemType::CUTLASS:
		texture = CutlassIcon; break;
	case ItemType::Blaster:
		texture = BlasterIcon; break;
	case ItemType::Key:
		texture = KeyIcon; break;
	case ItemType::LANTERN:
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

	// 무게 배경
	if (WeightTextBackground)
	{
		WeightTextBackground->SetVisibility(ESlateVisibility::Visible);
	}
	// 무게 텍스트
	if (WeightText)
	{
		WeightText->SetText(FText::AsNumber(weight));
		WeightText->SetVisibility(ESlateVisibility::Visible);
	}

	// 슬롯 채움
	isEmpty = false;

	// ID, Type, Weight
	SetToolID(id);
	SetToolType(type);
	SetToolWeight(weight);
	SetToolCost(cost);
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
	if (WeightTextBackground)
	{
		WeightTextBackground->SetVisibility(ESlateVisibility::Hidden);
	}
	if (WeightText)
	{
		WeightText->SetVisibility(ESlateVisibility::Hidden);
	}
}