// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 개별 방 목록에 텍스트 세팅
	void SetupEntry(const FString& Title, const FText& State);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RoomTitle;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RoomState;
	
};
