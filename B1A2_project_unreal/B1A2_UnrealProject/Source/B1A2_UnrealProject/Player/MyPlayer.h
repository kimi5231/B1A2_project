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
class ABaseSellingMachine;

class UShopWidget;
class UQuestWidget;

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

	// 달리기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* RunningAction;

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

	// 가위바위보 Cheat Key
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* SendRockAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* SendScissorAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* SendPaperAction;

	// 레버 당기기 Cheat Key
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractLaverAction;

	// 판매하기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* SellAction;

	// 퀘스트 마우스 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* QuestInputAction;

public:
	AMyPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Jump();
	void Look(const FInputActionValue& Value);
	
public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	void AddItemToInventory(ItemType type, int id, float weight, int cost);
	int32 AddToolToToolBar(ItemType type, int id, float weight, int cost);

protected:
	UPROPERTY()
	TSet<AActor*> _nearInteractables;

	UPROPERTY()
	AActor* _focusedActor;	// E 버튼을 띄울 아이템 or 문

	UPROPERTY()
	ABaseSellingMachine* _overlappedSellingMachine;

	// 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _inventoryWidgetClass;

	UPROPERTY()
	UUserWidget* _inventoryWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _emotionResultWidgetClass;

	UPROPERTY()
	UUserWidget* _emotionResultWidgetInstance;

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
	
	// 퀘스트 키 입력 시 마우스 입력 모드 전환(보상 받을 수 있도록)
	void QuestInputToggle();

protected:
	// Item/Tool 버리기 입력
	void ItemOrToolDrop();

	// Tool Change 패킷 보내기
	void SendChangeToolPacket();

	// Scan
	void Scan();

	// Cheat Key
	void CheatKey();

	// 가위 바위 보 (임시 테스트용!!)
	void SendRock();	// Happy
	void SendScissor();	// Neutral
	void SendPaper();	// Angry

	// 레버 당기기 Cheat Key (임시 테스트용!!)
	void SendEndStageAndStartStage();
	int laverPullCount = 0;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _statusWidgetClass;

	UPROPERTY()
	UUserWidget* _statusWidgetInstance;

	// Shop
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _shopWidgetClass;

	UPROPERTY()
	UShopWidget* _shopWidgetInstance;

	// Quest
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _questWidgetClass;

	UPROPERTY()
	UQuestWidget* _questWidgetInstance;

public:
	// 로컬 플레이어 모델 업데이트
	void UpdateToolVisual();

	UUserWidget* GetToolBarWidget() const { return _toolBarWidgetInstance; }
	UUserWidget* GetEmotionResultWidget() const { return _emotionResultWidgetInstance; }
	UShopWidget* GetShopWidget() const { return _shopWidgetInstance; }
	UQuestWidget* GetQuestWidget() const { return _questWidgetInstance; }

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

protected:
	// 달리기 시작 / 종료
	void StartRunning();
	void StopRunning();

	bool isRunning = false;
	void UpdateMovementStats();

	// 스테미나, 무게, 이속 등
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float _currentStamina = 100.0f;
	const float _maxStamina = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float _currentWeight = 0.0f;
	const float _maxWeight = 30.0f;
	const float _referenceWeight = 15.0f; // 기준무게 (Max / 2)

	// 기본 속도 정의
	const float _baseWalkSpeed = 500.f;
	const float _baseRunSpeed = 650.f;
	const float _baseJumpVelocity = 350.f;
	const float _baseCrouchSpeed = 400.f;

	// Hp
	UPROPERTY(BlueprintReadOnly, category = "Stats")
	float _currentHp = 100.f;
	const float _maxHp = 100.f;

public:
	float GetCurrentHp() { return _currentHp; }
	void SetCurrentHp(float hp) { _currentHp = hp; }

protected:
	// 랜턴의 현재 켜짐/꺼짐 상태
	UPROPERTY(BlueprintReadOnly, Category = "Lantern")
	bool _isLanternOn = false;

	// 현재 배터리 잔량
	UPROPERTY(BlueprintReadOnly, Category = "Lantern")
	float _currentBattery = 0.f;

	// 초당 배터리 소모 계산을 위한 누적 시간
	float _sumTime = 0.0f;

public:
	// 서버 패킷 수신 시 랜턴 상태와 배터리 설정
	void SetIsLanternOn(bool isOn) { _isLanternOn = isOn; }
	void SetCurrentBattery(float battery) { _currentBattery = battery; }

	// UI에서 값을 읽기 위한 Getter
	bool GetIsLanternOn() const { return _isLanternOn; }
	float GetCurrentBattery() const { return _currentBattery; }

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
	void TurnLanternSendOrUseToolAnimationAndSend();

	void InteractSellingMachine();

	// 몽타주 애니메이션 종료시 호출
	UFUNCTION()
	void OnToolMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 위치 정보 Send 타이머
	float _movePacketSendTimer = 0.2f;	// 현재 남은 시간
	const float MOVE_PACKET_SEND_DELAY = 0.2f;	// 전송 간격

	FVector _lastSentLocation = FVector::ZeroVector;
	FRotator _lastSentRotation = FRotator::ZeroRotator;

	// 상호작용 객체 확인 타이머
	float _interactionTimer = 0.1f;		// 현재 남은 시간
	const float INTERACTION_DELAY = 0.1f;	// 확인 간격
	
	// 직전에 서버에 보낸 Tool의 ID
	int32 _lastSentToolID = -1;	
	// 장비가 있는 슬롯 선택 -> 빈 슬롯 선택: 서버에 패킷 송신
	// 빈 슬롯 선택 -> 빈 슬롯 선택: 서버에 패킷 송신X
};
