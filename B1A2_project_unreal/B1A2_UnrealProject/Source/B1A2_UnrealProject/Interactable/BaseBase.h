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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;		// 플레이어와 충돌 처리

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;
};
