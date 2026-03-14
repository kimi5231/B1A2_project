// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	virtual void NativeConstruct() override;

public:
	//void UpdateInventoryUI(TArray<UTexture2D*> texture);

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* SlotGrid;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<UInventorySlotWidget*> SlotArray;

};
