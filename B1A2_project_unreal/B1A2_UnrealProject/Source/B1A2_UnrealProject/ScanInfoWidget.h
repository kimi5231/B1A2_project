// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScanInfoWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UScanInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetScanInfo(bool isTool, const FString& itemName, int32 cost);

protected:
	// 종류
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Type;

	// 이름
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;

	// 가격
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Text_Cost;

	// 에디터에서 한글로 변경해야 함!
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ToolText = FText::FromString(TEXT("Tool"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemText = FText::FromString(TEXT("Item"));
};
