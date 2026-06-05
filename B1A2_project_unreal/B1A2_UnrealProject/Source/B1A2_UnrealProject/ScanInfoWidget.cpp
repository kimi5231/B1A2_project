// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanInfoWidget.h"
#include "Components/TextBlock.h"

void UScanInfoWidget::SetScanInfo(bool isTool, const FString& itemName, int32 cost)
{
	if (Text_Name)
		Text_Name->SetText(FText::FromString(itemName));

	// 도구 (이름, 종류만, 가격 숨김)
	if (isTool)
	{
		if (Text_Type)
		{
			FText basePrefix = Text_Type->GetText();

			FText formattedText = FText::Format(FText::FromString(TEXT("{0}{1}")), basePrefix, ToolText);
			Text_Type->SetText(formattedText);
		}

		if (Text_Cost)
		{
			Text_Cost->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	// 아이템 (이름, 종류, 가격 표시)
	else
	{
		if (Text_Type)
		{
			FText basePrefix = Text_Type->GetText();

			FText formattedText = FText::Format(FText::FromString(TEXT("{0}{1}")), basePrefix, ItemText);
			Text_Type->SetText(formattedText);
		}

		if (Text_Cost)
		{
			Text_Cost->SetVisibility(ESlateVisibility::Visible);

			FString costStr = FString::Printf(TEXT("%d $"), cost);
			Text_Cost->SetText(FText::FromString(costStr));
		}
	}
}
