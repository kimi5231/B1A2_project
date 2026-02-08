// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// OpenCV
#include "PreOpenCVHeaders.h"
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include "PostOpenCVHeaders.h"

class UMain;

class B1A2_UNREALPROJECT_API EmotionExtractionRunnable : public FRunnable
{
public:
	EmotionExtractionRunnable(UMain* main);
	virtual ~EmotionExtractionRunnable();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

private:
	UMain* _main;
	FThreadSafeBool _running;

	// OpenCV 객체
	cv::VideoCapture _videoCapture;
	cv::dnn::Net _emotionNet;
	cv::CascadeClassifier _faceDetector;

	// 감정 라벨(FER2013)
	TArray<FString> Labels = { TEXT("Angry"), TEXT("Disgust"), TEXT("Fear"), TEXT("Happy"), TEXT("Sad"), TEXT("Surprise"), TEXT("Neutral") };
};
