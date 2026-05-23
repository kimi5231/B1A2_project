// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEmotionGame.h"
#include "Materials/MaterialInstanceDynamic.h"

void ABaseEmotionGame::BeginPlay()
{
    Super::BeginPlay();

    // 메쉬 컴포넌트에서 머테리얼을 가져와 동적 인스턴스로 생성
    UMeshComponent* MeshComp = FindComponentByClass<UMeshComponent>();
    if (MeshComp)
    {
        MonitorDynamicMat = MeshComp->CreateDynamicMaterialInstance(0); // 모니터 머테리얼 슬롯은 0
    }
}

void ABaseEmotionGame::StartGrabCountdown()
{
    // 카운트다운 초기화
    _currentCountdownValue = 3;

    // 3 출력
    UpdateMonitorDisplay(TEXT("3"));

    // 1초마다 HandleCountdownStep 호출, 3번 반복
    GetWorld()->GetTimerManager().SetTimer(_countdownTimerHandle, this, &ABaseEmotionGame::HandleCountdownStep, 1.0f, true);
}

void ABaseEmotionGame::PlayGameResultSequence(FString monsterEmotion, FString gameResult)
{
    if (!GetWorld()) return;

    // 중복 타이머 초기화
    GetWorld()->GetTimerManager().ClearTimer(_resultDisplayTimerHandle);

    // 몬스터의 감정 출력
    UpdateMonitorDisplay(monsterEmotion);

    // 2초 타이머 생성
    FTimerDelegate resultDelegate;
    resultDelegate.BindWeakLambda(this, [this, gameResult]()
    {
        // 2초 후 결과 출력
        UpdateMonitorDisplay(gameResult);

        // 결과 출력 후, 다시 3초 뒤에 Idle로 돌아가도록 예약
        GetWorld()->GetTimerManager().SetTimer(_resultDisplayTimerHandle, this, &ABaseEmotionGame::ResetToIdle, 3.0f, false);
    });

    // 2초 단발성 타이머 가동
    GetWorld()->GetTimerManager().SetTimer(_resultDisplayTimerHandle, resultDelegate, 2.0f, false);
}

void ABaseEmotionGame::ResetToIdle()
{
    UpdateMonitorDisplay(TEXT("Idle"));
}

void ABaseEmotionGame::HandleCountdownStep()
{
    _currentCountdownValue--;

    if (_currentCountdownValue >= 1)
    {
        // 2, 1 출력
        UpdateMonitorDisplay(FString::FromInt(_currentCountdownValue));
    }
    else
    {
        // 카운트다운 종료 (타이머 해제)
        GetWorld()->GetTimerManager().ClearTimer(_countdownTimerHandle);

        // 0초가 되었을 때의 처리? -> 서버에서 결과 보내주니까 굳이 Idle로 변경 X
        // UpdateMonitorDisplay(TEXT("Idle")); 
    }
}

void ABaseEmotionGame::UpdateMonitorDisplay(FString State)
{
    if (!MonitorDynamicMat) return;

    UTexture2D* targetTex = nullptr;

    // 텍스처 변경
    if (State == "Idle") targetTex = Tex_Idle;
    else if (State == "Win") targetTex = Tex_Win;
    else if (State == "Lose") targetTex = Tex_Lose;
    else if (State == "Draw") targetTex = Tex_Draw;
    else if (State == "1") targetTex = Tex_1;
    else if (State == "2") targetTex = Tex_2;
    else if (State == "3") targetTex = Tex_3;
    else if (State == "Happy") targetTex = Tex_Happy;
    else if (State == "Sad") targetTex = Tex_Sad;
    else if (State == "Neutral") targetTex = Tex_Neutral;

    // 머테리얼 파라미터 업데이트
    if (targetTex)
    {
        MonitorDynamicMat->SetTextureParameterValue(FName("ScreenTex"), targetTex);
    }
}

