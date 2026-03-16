// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

#include "BaseItem.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ABaseItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowInteractionUI_Implementation() override;
	virtual void HideInteractionUI_Implementation() override;
	virtual void Interact_Implementation() override;

	void SetItemID(int itemID) { _itemID = itemID; }
	int GetItemID() { return _itemID; }

	void SetIsTool(bool isTool) { _isTool = isTool; }
	bool GetIsTool() { return _isTool; }

	void PickUp(USceneComponent* mesh, FName socketName);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;		// 플레이어와 충돌 처리

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;

private:
	int _itemID = {};
	bool _isTool = false;
};