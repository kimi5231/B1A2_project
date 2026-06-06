// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Network/Includes.h"

#include "MainMenuPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> LobbyWidgetClass;

	// 다시 입력하세요
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> FailureWidgetClass;
public:
	void HandleLoginResult(LoginResult result);
	void HandleCurrentRoomList(const RoomDTO& roomData);

private:
	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

	UPROPERTY()
	UUserWidget* LobbyWidgetInstance;

	UPROPERTY()
	UUserWidget* FailureWidgetInstance;

	// 경고창 타이머
	FTimerHandle failureTimerHandle;

	// 경고창 끄기
	void HideFailureWidget();
};
