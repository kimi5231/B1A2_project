// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

#include "BaseItem.generated.h"

UENUM(BLueprintType)
enum class EItemType : uint8
{
	InInventory,	// 드는 동작 후 인벤토리로 들어감(메쉬 삭제)
	Tool	// 계속 손에 쥐고 있음
};

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

	void PickUp(USceneComponent* mesh, FName socketName);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;		// 플레이어와 충돌 처리

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;

public:
	UPROPERTY(EditAnywhere, Category = "Item Setting")
	EItemType ItemType;

private:
	int _itemID = {};
};