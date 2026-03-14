// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSlotWidget.h"

void UToolSlotWidget::SetSelected(bool isSelected)
{
	if (!SelectionItemIcon)
		return;

	if (isSelected)
		SelectionItemIcon->SetVisibility(ESlateVisibility::Visible);
	else
		SelectionItemIcon->SetVisibility(ESlateVisibility::Hidden);
}