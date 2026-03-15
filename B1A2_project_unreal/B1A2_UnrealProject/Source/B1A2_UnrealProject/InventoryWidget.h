// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"

#include "InventoryWidget.generated.h"

class UInventorySlotWidget;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;	
	// NativeConstruct는 AddToViewport로 처음 그려질 때 호출됨 -> 인벤토리를 한 번도 안 그렸으면 초기화가 안 됐던 것!!

public:
	//void UpdateInventoryUI(TArray<UTexture2D*> texture);
	void AddItem(int id, ItemType type, float weight);
	void InitializeSlots();

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* SlotGrid;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<UInventorySlotWidget*> SlotArray;
};
