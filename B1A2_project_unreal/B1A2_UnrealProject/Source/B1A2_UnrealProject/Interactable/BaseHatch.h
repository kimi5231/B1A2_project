// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Network/Includes.h"

#include "BaseHatch.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ABaseHatch : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseHatch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowInteractionUI_Implementation() override;
	virtual void HideInteractionUI_Implementation() override;
	virtual void Interact_Implementation() override;

	// 서버 상태 업데이트용
	void UpdateHatchState(ObjectState newState);

    // 초기 설정
    void SetHatchState(ObjectState state) { _currentState = state; }
    ObjectState GetDoorState() { return _currentState; }

    void SetHatchID(int32 id) { _doorID = id;}
    int32 GetDoorID() { return _doorID; }

    void SetHatchRotation(ObjectState state);   // Open일 때는 문 열어놓기

protected:
    // 슬라이드 애니메이션 업데이트
    UFUNCTION()
    void UpdateHatchSlide(float value);

    // 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* DoorFrameMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* LeftDoorMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* RightDoorMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UWidgetComponent* EWidget;

    // 애니메이션 설정
    UPROPERTY(EditAnywhere, Category = "Hatch|Animation")
    UCurveFloat* HatchCurve;

    FTimeline HatchTimeline;

    UPROPERTY(EditAnywhere, Category = "Hatch|Animation")
    float MaxSlideDistance = 150.f; // 문이 옆으로 밀려날 거리

private:
    int _doorID;
    ObjectState _currentState = ObjectState::CLOSE;
};
