// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Network/Includes.h"

#include "BaseSellingMachine.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ABaseSellingMachine : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseSellingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowInteractionUI_Implementation() override;
	virtual void HideInteractionUI_Implementation() override;
	virtual void Interact_Implementation() override;

	// 서버에서 받은 상태 업뎃(상태 변경 + 애니메이션)
	void UpdateMachineState(ObjectState newState);

	// 설정
	void SetMachineState(ObjectState state) { _currentState = state; UpdateWidgetState(); }
	ObjectState GetMachineState() { return _currentState; }

	void SetMachineID(int32 ID) { _machineID = ID; }
	int32 GetMachineID() { return _machineID; }

	// Close State로 생성되면 -> 판매기 닫아놓기
	void SetLeverLength(ObjectState state);

	// Credit
	int32 GetCurrentPendingCredit() const { return _currentPendingCredit; }
	void ResetPendingCredit();
	bool CanAddCredit(int32 itemCost) const;
	void AddPendingCredit(int32 itemCost);

	// 제한 크레딧
	void SetMaxCredit(int32 maxCredit) { _maxCredit = maxCredit; }
	int32 GetMaxCredit() const { return _maxCredit; }

	// 위젯 상태 업데이트 통합 관리
	void UpdateWidgetState();

	// S_SellItemResult_Packet을 수신하면, 판매 애니메이션 수행(레버 올렸다가 3초 뒤 내림)
	void PlaySellAnimation();

protected:
	// 애니메이션
	void OnStateChanged(ObjectState oldState, ObjectState newState);

	UFUNCTION()
	void UpdateLeverAnimation(float value);

	// 3초 뒤 레버 복귀용 타이머 콜백 함수
	void ReverseLeverTimer();

	// Components
	UPROPERTY(EditAnywhere, Category = "Machine|Animation")
	UCurveFloat* leverCurve;

	FTimeline leverTimeline;

	UPROPERTY(EditAnywhere, Category = "Machine|Animation")
	float LeverDistance = 60.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MachineBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;

private:
	int _machineID;
	ObjectState _currentState = ObjectState::CLOSE;

	int32 _maxCredit{};		// 판매기 제한 크레딧
	int32 _currentPendingCredit{};	// 현재 올려진 아이템들의 총 가격

	// 판매 애니메이션 전용 타이머 핸들
	FTimerHandle _leverTimerHandle;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Machine|UI")
	void K2_UpdateWidgetByState(int32 StateIndex);
};
