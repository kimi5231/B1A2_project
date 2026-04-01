// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OtherPlayer.h"
#include "Animation/AnimMontage.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"

#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMain;
class ABaseItem;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMyPlayer : public AOtherPlayer
{
	GENERATED_BODY()
	
protected:
	/** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|IMC", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MouseLookAction;

	// Get Item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* GetItemAction;

	// Use Tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* UseToolAction;

	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryTurnOnAndOffAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryItemSelectForwardAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryItemSelectBackwardAction;

	// Tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ToolSlotUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ToolSlotDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemOrToolDropAction;

	// Scan
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ScanAction;

	// Cheat Key(Go To MainRoom)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* CheatKeyAction;

public:
	AMyPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	void AddItemToInventory(ItemType type, int id, float weight);
	int32 AddToolToToolBar(ItemType type, int id, float weight);

protected:
	UPROPERTY()
	TSet<AActor*> _nearInteractables;

	UPROPERTY()
	AActor* _focusedActor;	// E 버튼을 띄울 아이템 or 문

	// 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _inventoryWidgetClass;

	UPROPERTY()
	UUserWidget* _inventoryWidgetInstance;

	// Inventory 입력
	void ToggleInventory();
	void InventoryItemSelectForward();
	void InventoryItemSelectBackward();

	// Tool Bar 입력
	void ToolSelectUp();
	void ToolSelectDown();
public:
	// Tool 획득시 변경
	void OnToolSelectionChanged();

protected:
	// Item/Tool 버리기 입력
	void ItemOrToolDrop();

	// Tool Change 패킷 보내기
	void SendChangeToolPacket();

	// Scan
	void Scan();

	// Cheat Key
	void CheatKey();

public:
	// Inventory에서 Item 삭제
	void RemoveItemInInventoryByID(int itemID);
	// ToolBar에서 Tool 삭제
	void RemoveToolInToolBarByID(int itemID);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _toolBarWidgetClass;

	UPROPERTY()
	UUserWidget* _toolBarWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _controlExplainWidgetClass;

	UPROPERTY()
	UUserWidget* _controlExplainWidgetInstance;

public:
	// 로컬 플레이어 모델 업데이트
	void UpdateToolVisual();

	UUserWidget* GetToolBarWidget() const { return _toolBarWidgetInstance; }

protected:
	// Scan
	UPROPERTY(EditAnywhere, Category = "Scan")
	UMaterialInterface* ScanMaterialOrigin;

	UPROPERTY()
	UMaterialInstanceDynamic* ScanMaterialInst;

	// 타이머
	FTimerHandle ScanTimerHandle;
	float ScanEffectDuration = 1.0f; // 1초 동안 지속
	float CurrentScanAlpha = 0.0f;

	// 스캔 효과를 서서히 줄여 줌
	void UpdateScanEffect();

private:
	// 아이템 상호작용
	UFUNCTION()
	void OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnItemDestroyed(AActor* destroyedItem);
	void SetFocusedActor(AActor* newActor);
	void ClearFocusedActor();
	void UpdateBestInteractableActor();

	void Interact();
	void UseToolAnimationAndSend();
	// 몽타주 애니메이션 종료시 호출
	UFUNCTION()
	void OnToolMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 위치 정보 Send 타이머
	float _movePacketSendTimer = 0.2f;	// 현재 남은 시간
	const float MOVE_PACKET_SEND_DELAY = 0.2f;	// 전송 간격

	// 상호작용 객체 확인 타이머
	float _interactionTimer = 0.1f;		// 현재 남은 시간
	const float INTERACTION_DELAY = 0.1f;	// 확인 간격
	
	// 직전에 서버에 보낸 Tool의 ID
	int32 _lastSentToolID = -1;	
	// 장비가 있는 슬롯 선택 -> 빈 슬롯 선택: 서버에 패킷 송신
	// 빈 슬롯 선택 -> 빈 슬롯 선택: 서버에 패킷 송신X
};
