// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccountWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UAccountWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* EditableText_ID;

	UPROPERTY(meta = (BindWidget))
	class UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

private:
	UFUNCTION()
	void OnLoginClicked();

	UFUNCTION()
	void OnCancelClicked();
};
