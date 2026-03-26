// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Network/Includes.h"

#include "ToolSlotWidget.generated.h"

class UImage;
class UBorder;
class UTextBlock;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UToolSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSlotInfo(int32 id, ItemType type, float weight);
	void SetSelected(bool isSelected);

	// 슬롯에서 장비 삭제
	void ClearSlot();

	// ID, Type, Weight
	void SetToolID(int32 id) { _toolID = id; }
	int32 GetToolID() { return _toolID; }
	void SetToolType(ItemType type) { _toolType = type; }
	ItemType GetToolType() { return _toolType; }
	void SetToolWeight(float weight) { _toolWeight = weight; }
	float GetToolWeight() { return _toolWeight; }

public:
	bool isEmpty = true;

	UPROPERTY(meta = (BindWidget))
	UImage* ToolIcon;

	UPROPERTY(meta = (BindWidget))
	UBorder* WeightTextBackground;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightText;

	// 아이콘
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* CutlassIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* BlasterIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* KeyIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* LanternIcon;

	// 선택됐을 때 표시하는 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* SelectionHighlight;

private:
	int32 _toolID = 0;
	ItemType _toolType;
	float _toolWeight = 0.f;
};
