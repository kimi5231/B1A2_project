// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EmotionResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UEmotionResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetEmotion(int32 emotionIndex);

protected:
	// 텍스처 바꾸기 이벤트
	UFUNCTION(BlueprintImplementableEvent, Category = "Emotion", meta = (DisplayName = "On Emotion Updated"))
	void K2_OnEmotionUpdated(int32 emotionIndex);

public:
	// 텍스처 7장
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion", meta = (AllowPrivateAccess = "true"))
	TArray<class UTexture2D*> _emotionTextures;
};

