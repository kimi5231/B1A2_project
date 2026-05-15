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

    // 가위 바위 보 결과 출력 후 5초 뒤 Idle 표시하도록 예약
    void DisplayGameResult(FString result);
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
