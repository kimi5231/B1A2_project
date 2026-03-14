// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::SetItemImage(UTexture2D* texture)
{
	if (ItemIcon && texture)
	{
		ItemIcon->SetBrushFromTexture(texture);
		ItemIcon->SetRenderOpacity(1.0f);
	}
}
