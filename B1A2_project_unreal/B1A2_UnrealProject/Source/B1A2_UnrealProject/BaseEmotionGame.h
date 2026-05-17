// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "BaseEmotionGame.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API ABaseEmotionGame : public ABaseMonster
{
	GENERATED_BODY()
	
public:
    // 상황에 맞춰 호출할 함수
    void UpdateMonitorDisplay(FString State);
    
    // UMain에서 Grab 상태 패킷을 받으면 호출 시작 - 3, 2, 1 출력하기 위해
    void StartGrabCountdown();
    
    // 감정 텍스처 선출력 후 2초 뒤 결과 출력 -> 3초 뒤 Idle 복귀 시퀀스 함수
    void PlayGameResultSequence(FString monsterEmotion, FString gameResult);
    
    // Idle로 리셋 
    void ResetToIdle();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Idle;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Win;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Lose;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Draw;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_1;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_2;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_3;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Happy;
    
    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Sad;

    UPROPERTY(EditAnywhere, Category = "Monitor")
    UTexture2D* Tex_Neutral;

private:
    UPROPERTY()
    class UMaterialInstanceDynamic* MonitorDynamicMat;

protected:
    FTimerHandle _countdownTimerHandle;
    int32 _currentCountdownValue = 3;

    FTimerHandle _resultDisplayTimerHandle;

    // 타이머 매초 실행
    void HandleCountdownStep(); 
};
