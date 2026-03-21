// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Network/Includes.h"

#include "InventorySlotWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSlotInfo(int32 id, ItemType type, float weight);
	void SetSelected(bool isSelected);

	// 슬롯에서 아이템 삭제
	void ClearSlot();

	// ID, Type, Weight
	void SetItemID(int32 id) { _itemID = id; }
	int32 GetItemID() { return _itemID; }
	void SetItemType(ItemType type) { _itemType = type; }
	ItemType GetItemType() { return _itemType; }
	void SetItemWeight(float weight) { _itemWeight = weight; }
	float GetItemWeight() { return _itemWeight; }

public:
	bool isEmpty = true;

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightText;

	// 아이콘
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* CardboardBoxIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* GoldBarIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* RubberDuckIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* PlasticCrateIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* ScrewIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* PirateHatIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* HardHatIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* EngineCoreIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* ScrapMetalIcon;
	UPROPERTY(EditDefaultsOnly, Category = "UI|Icons")
	UTexture2D* EmptyCanIcon;

	// 선택됐을 때 표시하는 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* SelectionHighlight;

private:
	int32 _itemID = 0;
	ItemType _itemType;
	float _itemWeight = 0.f;
};
