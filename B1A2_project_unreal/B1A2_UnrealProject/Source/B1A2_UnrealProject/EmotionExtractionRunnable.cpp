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

    while (_running)
    {
        // 카메라 프레임 읽기
        _videoCapture >> frame;
        if (frame.empty())
        {
            FPlatformProcess::Sleep(0.1f);
            continue;
        }

        // 흑백 변환
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faces;

        // 얼굴 검출
        _faceDetector.detectMultiScale(gray, faces, 1.1, 5, 0, cv::Size(30, 30));

        if (faces.size() > 0)
        {
            // 가장 영역이 큰 얼굴 추출
            faceROI = gray(faces[0]);   

            // FER2013
            cv::Mat blob = cv::dnn::blobFromImage(faceROI, 1.0 / 255.0, cv::Size(48, 48), cv::Scalar(0), false);

            // 추론
            _emotionNet.setInput(blob);
            cv::Mat prob = _emotionNet.forward();

            // 해석
            prob = prob.reshape(1, 1);

            FString scoreLog = TEXT("[OpenCV] Emotion Scores: ");
            double MaxVal = 0;
            int MaxIdx = 0;

            for (int i = 0; i < prob.cols; i++)
            {
                // 모델 출력값 추출
                float score = prob.at<float>(0, i);

                if (Labels.IsValidIndex(i))
                {
                    scoreLog += FString::Printf(TEXT("[%s: %.2f] "), *Labels[i], score);
                }

                // 가장 높은 점수 찾음
                if (score > MaxVal)
                {
                    MaxVal = score;
                    MaxIdx = i;
                }
            }

            // 모든 감정 점수 출력
            UE_LOG(LogTemp, Log, TEXT("%s"), *scoreLog);
        }

        // 1초마다 추출하도록 대기
        FPlatformProcess::Sleep(1.0f);
    }

    return 0;
}

void EmotionExtractionRunnable::Stop()
{
    _running = false;
}
