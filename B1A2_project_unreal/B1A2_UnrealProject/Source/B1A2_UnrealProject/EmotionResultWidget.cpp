// Fill out your copyright notice in the Description page of Project Settings.


#include "EmotionResultWidget.h"

void UEmotionResultWidget::SetEmotion(int32 emotionIndex)
{
	if (_emotionTextures.IsValidIndex(emotionIndex))
		K2_OnEmotionUpdated(emotionIndex);
}
