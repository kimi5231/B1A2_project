// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "ToolSlotWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UToolSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSelected(bool isSelected);

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	// 선택됐을 때 보여주는 아이콘(진하게)
	UPROPERTY(meta = (BindWidget))
	UImage* SelectionItemIcon;
};
