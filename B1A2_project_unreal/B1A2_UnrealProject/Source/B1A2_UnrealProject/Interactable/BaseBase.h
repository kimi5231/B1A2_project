// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

#include "BaseBase.generated.h"

class USkeletalMeshComponent;
class UAnimationAsset;
/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API ABaseBase : public AStaticMeshActor, public IInteractableInterface
{
	GENERATED_BODY()
public:
	ABaseBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowInteractionUI_Implementation() override;
	virtual void HideInteractionUI_Implementation() override;
	virtual void Interact_Implementation() override;

	void ShowInteractionUI_Dynamic(bool isInventoryOpen);

	void PlayLeverAnimation();

	// MyPlayer가 L키를 눌렀을 때 호출
	void RequestLeverPull();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;		// 플레이어와 충돌 처리

	// 인벤토리가 닫혔으면 상점 이용하기, 인벤토리가 열렸으면 제출하기
	// 상점 이용하기 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;
	
	// 제출하기 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* SubmitWidget;

	// 레버 관련
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* LeverCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* LeverWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* LeverMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimationAsset* LeverPullAnim;

private:
	UFUNCTION()
	void OnLeverOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLeverOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 플레이어가 레버 근처에 있는지?
	bool bIsPlayerNearLever = false;

	// 레버 당긴 횟수
	int32 LeverPullCount = 0;
};
