// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Network/Includes.h"

#include "BaseDoor.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ABaseDoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoor();

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
	void UpdateDoorState(ObjectState newState);

	// 초기 설정
	void SetDoorState(ObjectState state) { _currentState = state; }
	ObjectState GetDoorState() { return _currentState; }

	void SetDoorID(int32 ID) { _doorID = ID; }
	int32 GetDoorID() { return _doorID; }

protected:
	// 문 열림 - 닫힘 애니메이션 
	void OnStateChanged(ObjectState oldState, ObjectState newState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WindowMesh; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* EWidget;

private:
	int _doorID;
	ObjectState _currentState = ObjectState::CLOSE;
};
