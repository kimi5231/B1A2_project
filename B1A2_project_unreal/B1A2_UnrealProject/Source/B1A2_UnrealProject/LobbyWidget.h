// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"

#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 버튼
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Leave;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ScrollBox_RoomList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Room")
	TSubclassOf<UUserWidget> RoomEntryWidgetClass;

	// 인코딩 오류 방지용 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|RoomState")
	FText State_Reusable = FText::FromString(TEXT("Available"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|RoomState")
	FText State_Wait = FText::FromString(TEXT("Waiting"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|RoomState")
	FText State_Lock = FText::FromString(TEXT("Locked"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|RoomState")
	FText State_Play = FText::FromString(TEXT("Playing"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|RoomState")
	FText State_Full = FText::FromString(TEXT("Full"));

	// 버튼 입력
	UFUNCTION() void OnHostClicked();
	UFUNCTION() void OnJoinClicked();
	UFUNCTION() void OnLeaveClicked();

public:
	// 목록 갱신
	void UpdateRoomList(const std::vector<RoomDTO>& roomList);
};
