// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "PlayerResultWidget.h"
#include "GameResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* VBox_PlayerList;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UPlayerResultWidget> PlayerWidgetClass;

    void NativeUpdatePlayerList(const TArray<FString>& Names, const TArray<bool>& IsDeadStates);
};
