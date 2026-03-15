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

public:
	bool isEmpty = true;

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightText;

	// æ∆¿Ãƒ‹
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
};
