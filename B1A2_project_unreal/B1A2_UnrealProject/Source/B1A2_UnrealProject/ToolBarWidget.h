// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolBarWidget.generated.h"

class UVerticalBox;
class UToolSlotWidget;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UToolBarWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:
	void ChangeSelection(bool forward);		// 휠 방향에 따라 변경

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SlotBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ToolSlotClass;

	UPROPERTY()
	TArray<UToolSlotWidget*> ToolSlots;

	int32 _currentSelectedIndex = 0;
	
};
