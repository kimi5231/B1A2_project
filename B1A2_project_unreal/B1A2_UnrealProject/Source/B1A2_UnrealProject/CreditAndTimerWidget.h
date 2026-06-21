// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditAndTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UCreditAndTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 크레딧 정보 갱신 이벤트
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void K2_UpdateCredit(int32 GoalCredit, int32 CollectCredit, int32 CurrentCredit);

	// 시간 갱신 이벤트
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void K2_UpdateTimer(int32 CurrentTime);
};
