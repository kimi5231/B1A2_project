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

	// Start 클릭 시 띄울 Account 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UAccountWidget> AccountWidgetClass;

public:
	// Account에서 Quit 버튼을 눌렀을 때, 비활성화된 Start, Quit 버튼 활성화
	void SetButtonEnable(bool enable);

	// Lobby 창을 띄울 떄 Account의 버튼 비활성화
	void SetAccountButtonEnable(bool enable);

	void RemoveAccountWidget();

private:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();

	UPROPERTY()
	class UAccountWidget* AccountWidgetInstance;
};
