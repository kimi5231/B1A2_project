// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "PlayerResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UPlayerResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_PlayerName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Status;

    void SetPlayerResult(const FString& Name, bool bIsDead);
};
