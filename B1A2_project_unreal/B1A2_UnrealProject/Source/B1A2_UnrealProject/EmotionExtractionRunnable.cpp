// Fill out your copyright notice in the Description page of Project Settings.


#include "EmotionExtractionRunnable.h"
#include "Main.h"
#include "Misc/Paths.h"

EmotionExtractionRunnable::EmotionExtractionRunnable(UMain* main)
    : _main(main)
{
    _running = true;
}

EmotionExtractionRunnable::~EmotionExtractionRunnable()
{
	Stop();
}

bool EmotionExtractionRunnable::Init()
{
	// 경로 설정
	FString folderPath = FPaths::ProjectContentDir() + TEXT("OpenCV/Data/");
	FString modelPath = folderPath + TEXT("emotion_model.onnx");
	FString xmlPath = folderPath + TEXT("haarcascade_frontalface_default.xml");

    try
    {
        // 모델 로드
        _emotionNet = cv::dnn::readNetFromONNX(TCHAR_TO_UTF8(*modelPath));
        if (_emotionNet.empty()) return false;

        // 얼굴 검출기 로드
        if (!_faceDetector.load(TCHAR_TO_UTF8(*xmlPath)))
        {
            UE_LOG(LogTemp, Error, TEXT("[OpenCV] XML file load failed... %s"), *xmlPath);
            return false;
        }

        // 카메라 오픈
        _videoCapture.open(0);

        if (_videoCapture.isOpened())
        {
            UE_LOG(LogTemp, Error, TEXT("[OpenCV] emotion model, face detector, camera open success!!!"), *xmlPath);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[OpenCV] camera open failed!"));
            return false;
        }
    }
    catch (const cv::Exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("[OpenCV] exception... %s"), UTF8_TO_TCHAR(e.what()));
        return false;
    }
}

uint32 EmotionExtractionRunnable::Run()
{
    cv::Mat frame, gray, faceROI;
    
    // FER2013 공식 레이블 순서
    TArray<FString> FER2013_Labels = { TEXT("Angry"), TEXT("Disgust"), TEXT("Fear"), TEXT("Happy"), TEXT("Sad"), TEXT("Surprise"), TEXT("Neutral") };

    while (_running)
    {
        _videoCapture >> frame;
        if (frame.empty()) {
            FPlatformProcess::Sleep(0.1f);
            continue;
        }

        // 전처리
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        _faceDetector.detectMultiScale(gray, faces, 1.1, 5, 0, cv::Size(30, 30));

        if (faces.size() > 0)
        {
            // 가장 큰 얼굴 선택
            faceROI = gray(faces[0]);

            // 모델 입력 규격 맞추기 (48x48, 1/255 정규화)
            cv::Mat blob = cv::dnn::blobFromImage(faceROI, 1.0 / 255.0, cv::Size(48, 48), cv::Scalar(0), false, false);

            _emotionNet.setInput(blob);
            cv::Mat output = _emotionNet.forward();

            // LogSoftmax를 확률로 변환
            cv::Mat prob;
            cv::exp(output, prob);

            double MaxVal = 0;
            cv::Point MaxLoc;
            cv::minMaxLoc(prob, nullptr, &MaxVal, nullptr, &MaxLoc);
            int MaxIdx = MaxLoc.x;

            // 로그 출력
            FString scoreLog = TEXT("[OpenCV] Emotion Probabilities: ");
            for (int i = 0; i < prob.cols; i++)
            {
                float s = prob.at<float>(0, i);
                if (FER2013_Labels.IsValidIndex(i))
                {
                    scoreLog += FString::Printf(TEXT("[%s: %.2f] "), *FER2013_Labels[i], s);
                }
            }

            UE_LOG(LogTemp, Log, TEXT("%s"), *scoreLog);
            UE_LOG(LogTemp, Warning, TEXT(">> Result: %s (%.1f%%)"), *FER2013_Labels[MaxIdx], MaxVal * 100.0f);
        }

        FPlatformProcess::Sleep(1.0f);
    }
    return 0;
}

void EmotionExtractionRunnable::Stop()
{
    _running = false;
}

void EmotionExtractionRunnable::Exit()
{
    if (_videoCapture.isOpened())
    {
        _videoCapture.release();
        UE_LOG(LogTemp, Log, TEXT("[OpenCV] Camera Released"));
    }
}
