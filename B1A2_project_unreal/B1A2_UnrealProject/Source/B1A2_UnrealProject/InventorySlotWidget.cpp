// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::SetSlotInfo(int32 id, ItemType type, float weight)
{
	UTexture2D* texture = nullptr;

	switch (type)
	{
	case ItemType::CardboardBox:
		texture = CardboardBoxIcon; break;
	case ItemType::GoldBar:
		texture = GoldBarIcon; break;
	case ItemType::RubberDuck:
		texture = RubberDuckIcon; break;
	case ItemType::PlasticCrate:
		texture = PlasticCrateIcon; break;
	case ItemType::Screw:
		texture = ScrewIcon; break;
	case ItemType::PirateHat:
		texture = PirateHatIcon; break;
	case ItemType::HardHat:
		texture = HardHatIcon; break;
	case ItemType::EngineCore:
		texture = EngineCoreIcon; break;
	case ItemType::ScrapMetal:
		texture = ScrapMetalIcon; break;
	case ItemType::EmptyCan:
		texture = EmptyCanIcon; break;
	}
	
	if (!texture)
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] Texture is NULL for ItemType: %d"), (int32)type);
	}

	// 아이콘
	if (ItemIcon && texture)
	{
		ItemIcon->SetBrushFromTexture(texture);
		ItemIcon->SetRenderOpacity(1.0f);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("[Inventory] Success! Slot updated with ID: %d"), id);
	}

	// 무게
	if (WeightText)
	{
		WeightText->SetText(FText::AsNumber(weight));
		WeightText->SetVisibility(ESlateVisibility::Visible);
	}

	// 슬롯 채움
	isEmpty = false;

	// ID, Type, Weight
	SetItemID(id);
	SetItemType(type);
	SetItemWeight(weight);
}

void UInventorySlotWidget::SetSelected(bool isSelected)
{
	if (!SelectionHighlight)
		return;

	if (isSelected)
		SelectionHighlight->SetVisibility(ESlateVisibility::Visible);
	else
		SelectionHighlight->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::ClearSlot()
{
	isEmpty = true;
	_itemID = -1;

	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		ItemIcon->SetBrushFromTexture(nullptr);
	}
	if (WeightText)
	{
		WeightText->SetVisibility(ESlateVisibility::Hidden);
	}
}
