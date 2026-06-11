// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "RoomWidget.generated.h"

class UTextBlock;
class ULobbyWidget;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	// 개별 방 목록에 텍스트 세팅
	void SetupEntry(int roomID, const FString& Title, int playerCount, ULobbyWidget* parent);
	void SetSelected(bool selected);
	int GetRoomID() const { return _roomID; }

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RoomTitle;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_PlayerCount;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* CheckBox_Select;

private:
	int _roomID;

protected:

	// 부모 로비 참조 <- 한 개만 선택되도록 하기 위해
	UPROPERTY()
	ULobbyWidget* _parentLobby = nullptr;

	UFUNCTION()
	void OnSelectionChanged(bool isChecked);
};
