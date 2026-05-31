// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UAccountWidget;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	// Start Å¬¸¯ ½Ã ¶ç¿ï Account À§Á¬ Å¬·¡½º
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UAccountWidget> AccountWidgetClass;

private:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();

	UPROPERTY()
	class UAccountWidget* AccountWidgetInstance;
};
