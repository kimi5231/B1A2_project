// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

#include "BaseBase.generated.h"

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

};
