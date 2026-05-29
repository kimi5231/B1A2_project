// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "Network/UnrealPackets.h"

#include "Engine/EngineTypes.h"     
#include "Engine/World.h"           
#include "CollisionQueryParams.h"   
#include "Engine/OverlapResult.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Main/Main.h"
#include "Interactable/InteractableInterface.h"
#include "Interactable/BaseItem.h"
#include "Interactable/BaseDoor.h"
#include "Interactable/BaseHatch.h"
#include "Interactable/BaseSellingMachine.h"

#include "Widget/InventoryWidget.h" 
#include "Widget/ToolBarWidget.h" 
#include "Widget/PlayerStatusWidget.h"
#include "Widget/ShopWidget.h"
#include "Widget/QuestWidget.h"

#include "Blueprint/UserWidget.h"
#include "Interactable/BaseBase.h"

AMyPlayer::AMyPlayer()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), FName("head"));
	FollowCamera->bUsePawnControlRotation = true;

	_isInterpolation = false;
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 아이템 캡슐과 충돌
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnItemOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnItemOverlapEnd);

	// 점프 속도
	GetCharacterMovement()->JumpZVelocity = 350.f;

	// Tool Bar 위젯 띄우기
	if (_toolBarWidgetClass)
	{
		_toolBarWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _toolBarWidgetClass);

		if (_toolBarWidgetInstance)
			_toolBarWidgetInstance->AddToViewport();
	}
	// Inventory 위젯 생성
	if (_inventoryWidgetClass)
	{
		_inventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _inventoryWidgetClass);
	}
	// Control Explain 위젯
	if (_controlExplainWidgetClass)
	{
		_controlExplainWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _controlExplainWidgetClass);

		if (_controlExplainWidgetInstance)
			_controlExplainWidgetInstance->AddToViewport();
	}
	// Hp, Stamina 위젯
	if (_statusWidgetClass)
	{
		_statusWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _statusWidgetClass);

		if (_statusWidgetInstance)
			_statusWidgetInstance->AddToViewport();
	}
	// Emotion Result 위젯
	if (_emotionResultWidgetClass)
	{
		_emotionResultWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _emotionResultWidgetClass);

		if (_emotionResultWidgetInstance)
			_emotionResultWidgetInstance->AddToViewport();
	}
	// Shop 위젯
	if (_shopWidgetClass)
	{
		_shopWidgetInstance = CreateWidget<UShopWidget>(GetWorld(), _shopWidgetClass);
	}
	// Quest 위젯
	if (_questWidgetClass)
	{
		_questWidgetInstance = CreateWidget<UQuestWidget>(GetWorld(), _questWidgetClass);

		if (_questWidgetInstance)
			_questWidgetInstance->AddToViewport();
	}

	// Scan Material 설정
	if (ScanMaterialOrigin && FollowCamera)
	{
		// 동적 인스턴스 생성
		ScanMaterialInst = UMaterialInstanceDynamic::Create(ScanMaterialOrigin, this);

		// 카메라의 포스트 프로세스 세팅에 추가
		FWeightedBlendable Blendable;
		Blendable.Weight = 1.0f; // 가중치는 1로 고정
		Blendable.Object = ScanMaterialInst;

		FollowCamera->PostProcessSettings.WeightedBlendables.Array.Add(Blendable);

		// 초기에는 효과가 안 보이도록 0으로 설정
		ScanMaterialInst->SetScalarParameterValue(TEXT("ScanIntensity"), 0.0f);
	}
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_movePacketSendTimer -= DeltaTime;
	_interactionTimer -= DeltaTime;

	// MovePacket Send
	if (_movePacketSendTimer <= 0.f)
	{
		_movePacketSendTimer = MOVE_PACKET_SEND_DELAY;

		if (UMain* GameInstance = Cast<UMain>(GetGameInstance()))
			GameInstance->SendLocalPosition();
	}

	// 아이템 상호작용
	if (_interactionTimer <= 0.f)
	{
		_interactionTimer = INTERACTION_DELAY;

		UpdateBestInteractableActor();
	}

	// 스테미나
	{
		float weightRatio = _currentWeight / _referenceWeight;
		float staminaModifier = 1.f + weightRatio;

		if (isRunning && GetVelocity().Size() > 0)
		{
			float drainAmount = 5.f * staminaModifier * DeltaTime;
			_currentStamina = FMath::Max(0.f, _currentStamina - drainAmount);

			// 스테미나가 다 떨어지면 강제로 달리기 중지함
			if (_currentStamina <= 0)
			{
				isRunning = false;
				UpdateMovementStats();
			}

		}
		else
		{
			// 달리기 중이 아니거나, 제자리에 서 있을 때 스테미나 회복
			if (_currentStamina < _maxStamina)
			{
				// 초당 2 회복
				float recoveryAmount = 2.0f * DeltaTime;
				_currentStamina = FMath::Min(_maxStamina, _currentStamina + recoveryAmount);
			}
		}
	}

	// Lantern
	if (_isLanternOn && _currentBattery > 0.f)
	{
		_sumTime += DeltaTime;
		if (_sumTime >= 1.f)
		{
			_sumTime = 0.f;
			_currentBattery -= 1.f;
			_currentBattery = FMath::Max(0.f, _currentBattery);
		}
	}
	
	// 스테미나, HP & Battery UI 업데이트
	UPlayerStatusWidget* ui = Cast<UPlayerStatusWidget>(_statusWidgetInstance);
	if (ui)
	{
		// 스테미나, Hp
		ui->SetStamina(_currentStamina / _maxStamina);
		ui->SetHealth(_currentHp / _maxHp);

		// Lantern Battery 업데이트 (로컬, 서버 상관 없을듯 Tick이라서??)
		ui->SetBattery(_currentBattery / 180.f);

		// 무게
		ui->SetWeight(_currentWeight);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayer::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);

		// Running
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Started, this, &AMyPlayer::StartRunning);
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Completed, this, &AMyPlayer::StopRunning);
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Canceled, this, &AMyPlayer::StopRunning);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		// Get Item, Door Open & Close
		EnhancedInputComponent->BindAction(GetItemAction, ETriggerEvent::Started, this, &AMyPlayer::Interact);

		// Use Tool
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Started, this, &AMyPlayer::TurnLanternSendOrUseToolAnimationAndSend);

		// Tool Bar
		EnhancedInputComponent->BindAction(ToolSlotUpAction, ETriggerEvent::Started, this, &AMyPlayer::ToolSelectUp);
		EnhancedInputComponent->BindAction(ToolSlotDownAction, ETriggerEvent::Started, this, &AMyPlayer::ToolSelectDown);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryTurnOnAndOffAction, ETriggerEvent::Started, this, &AMyPlayer::ToggleInventory);
		EnhancedInputComponent->BindAction(InventoryItemSelectForwardAction, ETriggerEvent::Started, this, &AMyPlayer::InventoryItemSelectForward);
		EnhancedInputComponent->BindAction(InventoryItemSelectBackwardAction, ETriggerEvent::Started, this, &AMyPlayer::InventoryItemSelectBackward);

		// Item or Tool Drop
		EnhancedInputComponent->BindAction(ItemOrToolDropAction, ETriggerEvent::Started, this, &AMyPlayer::ItemOrToolDrop);

		// Scan
		EnhancedInputComponent->BindAction(ScanAction, ETriggerEvent::Started, this, &AMyPlayer::Scan);

		// Cheat Key
		EnhancedInputComponent->BindAction(CheatKeyAction, ETriggerEvent::Started, this, &AMyPlayer::CheatKey);

		// Rock Scissor Paper
		EnhancedInputComponent->BindAction(SendRockAction, ETriggerEvent::Started, this, &AMyPlayer::SendRock);
		EnhancedInputComponent->BindAction(SendScissorAction, ETriggerEvent::Started, this, &AMyPlayer::SendScissor);
		EnhancedInputComponent->BindAction(SendPaperAction, ETriggerEvent::Started, this, &AMyPlayer::SendPaper);
		
		// Laber Cheat Key
		EnhancedInputComponent->BindAction(InteractLaverAction, ETriggerEvent::Started, this, &AMyPlayer::SendEndStageAndStartStage);

		// Sell Item
		EnhancedInputComponent->BindAction(SellAction, ETriggerEvent::Started, this, &AMyPlayer::InteractSellingMachine);

		// Quest Key
		EnhancedInputComponent->BindAction(QuestInputAction, ETriggerEvent::Started, this, &AMyPlayer::QuestInputToggle);
	}
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
	if (IsBusy) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyPlayer::Jump()
{
	float weightRatio = _currentWeight / _referenceWeight;
	float staminaModifier = 1.0f + weightRatio;
	float jumpCost = 3.0f * (1.0f + weightRatio);

	if (_currentStamina >= jumpCost)
	{
		// 무게에 따라서 속도 조정
		float adjustJumpVelocity = _baseJumpVelocity / staminaModifier;

		GetCharacterMovement()->JumpZVelocity = adjustJumpVelocity;

		Super::Jump();
		_currentStamina -= jumpCost;
	}
}

void AMyPlayer::Look(const FInputActionValue& Value)
{
	if (IsBusy) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMyPlayer::AddItemToInventory(ItemType type, int id, float weight, int cost)
{
	if (_inventoryWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] _inventoryWidgetInstance is NULL!"));
		return;
	}

	UInventoryWidget* inventory = Cast<UInventoryWidget>(_inventoryWidgetInstance);
	if (inventory)
	{
		inventory->AddItem(id, type, weight, cost);

		// 현재 무게 및 이동 스탯 갱신
		_currentWeight += weight;
		UpdateMovementStats();

		//UE_LOG(LogTemp, Display, TEXT("[Inventory] Add Item Success!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] Cast to UInventoryWidget Failed!"));
	}
}

int32 AMyPlayer::AddToolToToolBar(ItemType type, int id, float weight, int cost)
{
	if (_toolBarWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolBar] _toolBarWidgetInstance is NULL!"));
		return -1;
	}

	UToolBarWidget* toolBar = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (toolBar)
	{
		// 현재 무게 및 이동 스탯 갱신
		_currentWeight += weight;
		UpdateMovementStats();

		return toolBar->AddTool(id, type, weight, cost);
	}
	else
		return -1;
}

void AMyPlayer::ToggleInventory()
{
	if (!_inventoryWidgetInstance)
		return;
	
	// 위젯 켜져있으면 끔, 꺼져있으면 킴
	if (_inventoryWidgetInstance->IsInViewport())
	{
		_inventoryWidgetInstance->RemoveFromParent();
	}
	else
	{
		_inventoryWidgetInstance->AddToViewport();

		// 선택된 슬롯을 처음으로 초기화
		UInventoryWidget* widget = Cast<UInventoryWidget>(_inventoryWidgetInstance);
		if (widget)
			widget->ResetSelectSlot();
	}
}

void AMyPlayer::InventoryItemSelectForward()
{
	if (!_inventoryWidgetInstance)
		return;

	if (_inventoryWidgetInstance->IsInViewport())
	{
		UInventoryWidget* widget = Cast<UInventoryWidget>(_inventoryWidgetInstance);
		
		if (widget)
			widget->SelectNextSlot();
	}
}

void AMyPlayer::InventoryItemSelectBackward()
{
	if (!_inventoryWidgetInstance)
		return;

	if (_inventoryWidgetInstance->IsInViewport())
	{
		UInventoryWidget* widget = Cast<UInventoryWidget>(_inventoryWidgetInstance);

		if (widget)
			widget->SelectPrevSlot();
	}
}

void AMyPlayer::ToolSelectUp()
{
	if (_toolBarWidgetInstance)
	{
		UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);

		if (widget)
		{
			widget->ChangeSelection(true);	// 하이라이트 변경
			OnToolSelectionChanged();
		}

		UE_LOG(LogTemp, Display, TEXT("[Input] Mouse Wheel Up"));
	}
}

void AMyPlayer::ToolSelectDown()
{
	if (_toolBarWidgetInstance)
	{
		UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);

		if (widget)
		{
			widget->ChangeSelection(false);		// 하이라이트 변경
			OnToolSelectionChanged();
		}

		UE_LOG(LogTemp, Display, TEXT("[Input] Mouse Wheel Up"));
	}
}

void AMyPlayer::OnToolSelectionChanged()
{
	UpdateToolVisual();

	GetWorldTimerManager().ClearTimer(ToolChangeTimerHandle);
	GetWorldTimerManager().SetTimer(ToolChangeTimerHandle, this, &AMyPlayer::SendChangeToolPacket, 0.5f, false);
}

void AMyPlayer::ItemOrToolDrop()
{
	FDroppedItemInfo info;

	// Inventory가 열려있을 때, 선택된 아이템 버리기
	if (_inventoryWidgetInstance && _inventoryWidgetInstance->IsInViewport())
	{
		UInventoryWidget* widget = Cast<UInventoryWidget>(_inventoryWidgetInstance);
		info = widget->GetSelectedInventoryItem();

		if (info.isValid)
		{
			if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
			{
				ABaseSellingMachine* SellingMachine = _overlappedSellingMachine;

				// 판매기 근처이고, Open 상태일 때
				if (SellingMachine && SellingMachine->GetMachineState() == ObjectState::OPEN)
				{
					int32 ItemCost = info.cost;

					if (SellingMachine->CanAddCredit(ItemCost))
					{
						gameInstance->SendDropItemToSellingMachine(gameInstance->GetMyID(), info.itemID, SellingMachine->GetMachineID());
						SellingMachine->AddPendingCredit(ItemCost);
						UE_LOG(LogTemp, Display, TEXT("[SellingMachine] Item Drop Success! Cost: %d"), ItemCost);
					}
					else  // 판매 금액이 초과됐다면, 바닥에 드랍
					{
						gameInstance->SendDropItem(gameInstance->GetMyID(), false, info.itemID);
						UE_LOG(LogTemp, Display, TEXT("[SellingMachine] Credit Limit Exceeded! Normal Drop. MaxLimit %d, PendingCredit %d"), SellingMachine->GetMaxCredit(), SellingMachine->GetCurrentPendingCredit());
					}
				}
				else
				{
					// 일반적인 상황에서의 드랍
					gameInstance->SendDropItem(gameInstance->GetMyID(), false, info.itemID);
					UE_LOG(LogTemp, Display, TEXT("[Item] Item Drop"));
				}
			}

			// 무게 및 이동 스탯 갱신 (기존 로직 유지)
			_currentWeight -= info.weight;
			_currentWeight = FMath::Max(0.f, _currentWeight);	// 음수 방지
			UpdateMovementStats();
		}
	}
	// Inventory가 닫혀있을 때, 선택된 장비 버리기 (Tool은 항상 일반 DropItem 패킷 사용)
	else if (_toolBarWidgetInstance)
	{
		UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
		info = widget->GetSelectedToolBarTool();

		if (info.isValid)
		{
			// 패킷 보내기
			if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
			{
				gameInstance->SendDropItem(gameInstance->GetMyID(), true, info.itemID);
				UE_LOG(LogTemp, Display, TEXT("[Tool] Tool Drop Packet Send! ToolID: %d"), info.itemID);
			}

			// 들고 있는 Tool 지우기
			_currentAttachedToolActor->Destroy();
			_currentAttachedToolActor = nullptr;

			// 랜턴 들기 상태 해제
			IsCarryingLantern = false;

			// 무게 및 이동 스탯 갱신 (기존 로직 유지)
			_currentWeight -= info.weight;
			_currentWeight = FMath::Max(0.f, _currentWeight);	// 음수 방지
			UpdateMovementStats();
		}
	}
}

void AMyPlayer::Scan()
{
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance) return;

	FVector playerLoc = GetActorLocation();
	FVector forwardDir = GetFollowCamera()->GetForwardVector(); // 카메라가 바라보는 방향 기준
	forwardDir.Z = 0; // 평면적인 부채꼴을 위해 Z축 무시 (선택 사항)
	forwardDir.Normalize();

	float scanRadius = 500.0f;
	float scanHalfAngleDeg = 80.0f; // 160도의 절반
	float cosHalfAngle = FMath::Cos(FMath::DegreesToRadians(scanHalfAngleDeg));

	TArray<ABaseItem*> allScanables = gameInstance->GetAllScanableItems();
	for (ABaseItem* item : allScanables)
	{
		if (!item) continue;

		FVector itemLoc = item->GetActorLocation();
		FVector dirToItem = itemLoc - playerLoc;
		float distance = dirToItem.Size();

		// 거리 검사
		if (distance <= scanRadius)
		{
			dirToItem.Normalize();

			// 각도 검사
			float DotProduct = FVector::DotProduct(forwardDir, dirToItem);
			if (DotProduct >= cosHalfAngle)
			{
				item->OnScanned();
			}
		}
	}

	// 시각 효과 실행
	if (ScanMaterialInst)
	{
		CurrentScanAlpha = 1.0f; // 최대 밝기
		ScanMaterialInst->SetScalarParameterValue(TEXT("ScanIntensity"), CurrentScanAlpha);

		// 0.01초마다 UpdateScanEffect를 호출하여 부드럽게 감소
		GetWorldTimerManager().SetTimer(ScanTimerHandle, this, &AMyPlayer::UpdateScanEffect, 0.01f, true);
	}
}

void AMyPlayer::CheatKey()
{
	SetActorLocation(FVector(0.f, 0.f, 25.f));
}

void AMyPlayer::SendRock()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendChangeEmotion(gameInstance->GetMyID(), Emotion::Happy);	// Happy
	
		UE_LOG(LogTemp, Log, TEXT("[Emotion] Sent C_Emotion Happy"));
	}
}

void AMyPlayer::SendScissor()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendChangeEmotion(gameInstance->GetMyID(), Emotion::Neutral);	// Neutral

		UE_LOG(LogTemp, Log, TEXT("[Emotion] Sent C_Emotion Neutral"));
	}
}

void AMyPlayer::SendPaper()
{
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendChangeEmotion(gameInstance->GetMyID(), Emotion::Angry);	// Angry

		UE_LOG(LogTemp, Log, TEXT("[Emotion] Sent C_Emotion Angry"));
	}
}

void AMyPlayer::SendEndStageAndStartStage()
{
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance) return;

	// 레버를 처음 당길 때
	if (laverPullCount == 0)
	{
		laverPullCount = 1;
		gameInstance->SendEndStage(true);
		UE_LOG(LogTemp, Display, TEXT("[Stage] Send C_EndStage_Packet (Count: 0->1)"));
	}
	// 레버를 두 번째 당길 때
	else if (laverPullCount == 1)
	{
		laverPullCount = 0;
		gameInstance->SendStartStage(true);
		UE_LOG(LogTemp, Display, TEXT("[Stage] Send C_StartStage_Packet (Count: 1->0)"));
	}
}

void AMyPlayer::QuestInputToggle()
{
	if (_questWidgetInstance)
	{
		_questWidgetInstance->ToggleMouseMode();
	}
}

void AMyPlayer::StartRunning()
{
	isRunning = true;
	UpdateMovementStats();		// 무게에 따른 속도 계산
}

void AMyPlayer::StopRunning()
{
	isRunning = false;
	UpdateMovementStats();	// 원래 걷기 속도로 복귀
}

void AMyPlayer::UpdateMovementStats()
{
	// 이동 속도 공식 = 이동 속도 * ( 1 / ( 1 + ( 현재무게 / 기준무게) ) )
	float weightRatio = _currentWeight / _referenceWeight;
	float speedModifier = 1.0f / (1.0f + weightRatio);

	UCharacterMovementComponent* moveComp = GetCharacterMovement();
	if (moveComp)
	{
		// 현재 상태에 맞게 속도 적용
		moveComp->MaxWalkSpeed = _baseWalkSpeed * speedModifier;
		moveComp->MaxWalkSpeedCrouched = _baseCrouchSpeed * speedModifier;
		moveComp->JumpZVelocity = _baseJumpVelocity * speedModifier;

		// 만약 현재 달리기 중이라면 RunSpeed 적용
		if (isRunning)
		{
			moveComp->MaxWalkSpeed = _baseRunSpeed * speedModifier;
		}
	}
}

void AMyPlayer::RemoveItemInInventoryByID(int itemID)
{
	if (_inventoryWidgetInstance)
	{
		UInventoryWidget* widget = Cast<UInventoryWidget>(_inventoryWidgetInstance);
		widget->RemoveItemByID(itemID);
	}
}

void AMyPlayer::RemoveToolInToolBarByID(int itemID)
{
	if (_toolBarWidgetInstance)
	{
		UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
		widget->RemoveToolByID(itemID);
	}
}

void AMyPlayer::SendChangeToolPacket()
{
	UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (!widget)
		return;

	FDroppedItemInfo ToolInfo = widget->GetSelectedToolBarTool();
	int32 currentItemID = ToolInfo.itemID;
	
	if (_lastSentToolID == -1 && currentItemID == -1)	// 이전에 선택된 슬롯이 빈 슬롯 && 현재 선택된 슬롯이 빈 슬롯일 경우 Send하지 않음
		return;
	if (_lastSentToolID == currentItemID)		// 동일한 Tool을 선택한 경우 Send하지 않음
		return;

	int32 IDtoSend = currentItemID;
	if (_lastSentToolID != -1 && ToolInfo.itemID == -1)		// 이전에 선택된 슬롯에 Tool이 있음 && 현재 선택된 슬롯이 빈 슬롯일 경우 ID를 0으로 Send
		IDtoSend = 0;

	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		gameInstance->SendChangeTool(gameInstance->GetMyID(), IDtoSend);
		_lastSentToolID = currentItemID;

		UE_LOG(LogTemp, Log, TEXT("[Tool] Sent C_ChangeTool_Packet: ID %d"), currentItemID);
	}
}

void AMyPlayer::UpdateToolVisual()
{
	UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (!widget) 
		return;

	// 현재 선택된 슬롯의 정보
	FDroppedItemInfo info = widget->GetSelectedToolBarTool();

	// 기존 도구가 있으면 제거
	if (_currentAttachedToolActor)
	{
		_currentAttachedToolActor->Destroy();
		_currentAttachedToolActor = nullptr;
	}

	// 빈 슬롯이라면 바꾸지 않음
	if (info.itemID == -1)
	{
		IsCarryingLantern = false;	// 랜턴 안 들고 있음
		return;
	}

	// 랜턴으로 바꾼다면 들고 있음 확인
	IsCarryingLantern = (info.type == ItemType::LANTERN);

	TSubclassOf<ABaseItem> ToolClass = GetToolClass(info.type);
	if (ToolClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;

		// Tool 액터 생성
		_currentAttachedToolActor = GetWorld()->SpawnActor<ABaseItem>(ToolClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

		if (_currentAttachedToolActor)
		{
			FName targetSocket = _currentAttachedToolActor->TargetSocketName;

			_currentAttachedToolActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, targetSocket);
			_currentAttachedToolActor->SetActorEnableCollision(false);	// 충돌 끔
		}
	}
}

void AMyPlayer::UpdateScanEffect()
{
	if (CurrentScanAlpha <= 0.0f)
	{
		CurrentScanAlpha = 0.0f;
		ScanMaterialInst->SetScalarParameterValue(TEXT("ScanIntensity"), 0.0f);

		// 노출 보정
		FollowCamera->PostProcessSettings.AmbientOcclusionPower = false;

		GetWorldTimerManager().ClearTimer(ScanTimerHandle);
		return;
	}

	CurrentScanAlpha -= (0.01f / ScanEffectDuration);
	ScanMaterialInst->SetScalarParameterValue(TEXT("ScanIntensity"), CurrentScanAlpha);

	// 카메라 노출
	FollowCamera->PostProcessSettings.bOverride_AutoExposureBias = true;
	FollowCamera->PostProcessSettings.AutoExposureBias = CurrentScanAlpha * 2.f;
}

void AMyPlayer::OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (ABaseSellingMachine* SellingMachine = Cast<ABaseSellingMachine>(OtherActor))
	{
		_overlappedSellingMachine = SellingMachine;

		// 판매기 상태에 따른 위젯 변경 및 UI 표시
		_overlappedSellingMachine->UpdateWidgetState();
		IInteractableInterface::Execute_ShowInteractionUI(_overlappedSellingMachine);

		UE_LOG(LogTemp, Log, TEXT("[MyPlayer] Overlapped with SellingMachine. Saved to dedicated variable."));
		return;
	}

	// 아이템, 문 등 처리
	if (OtherActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		_nearInteractables.Add(OtherActor);
	
		// 아이템 인식 중에 아이템이 삭제되는 경우 - 삭제될 때 호출(구독)
		if (!OtherActor->OnDestroyed.IsAlreadyBound(this, &AMyPlayer::OnItemDestroyed))
		{
			OtherActor->OnDestroyed.AddDynamic(this, &AMyPlayer::OnItemDestroyed);
		}
	}
}

void AMyPlayer::OnItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	// 판매기 구역에서 벗어난 경우 처리
	if (ABaseSellingMachine* SellingMachine = Cast<ABaseSellingMachine>(OtherActor))
	{
		if (_overlappedSellingMachine == SellingMachine)
		{
			IInteractableInterface::Execute_HideInteractionUI(_overlappedSellingMachine);
			_overlappedSellingMachine = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[MyPlayer] Left SellingMachine Range. Cleared dedicated variable."));
		}
		return;
	}

	// 일반 인터페이스 상호작용 객체 처리
	if (_nearInteractables.Contains(OtherActor))
	{
		_nearInteractables.Remove(OtherActor);

		if (_focusedActor == OtherActor)
		{
			ClearFocusedActor();
		}
	}
}

void AMyPlayer::OnItemDestroyed(AActor* destroyedItem)
{
	ABaseItem* item = Cast<ABaseItem>(destroyedItem);
	if (item)
		return;

	_nearInteractables.Remove(item);

	if (_focusedActor == item)
		ClearFocusedActor();

	UE_LOG(LogTemp, Log, TEXT("[Item] Item Destroyed in Player Reference"));
}

void AMyPlayer::SetFocusedActor(AActor* newActor)
{
	if (_focusedActor == newActor)
		return;

	if (_focusedActor)
		IInteractableInterface::Execute_HideInteractionUI(_focusedActor);

	_focusedActor = newActor;

	if (_focusedActor)
		IInteractableInterface::Execute_ShowInteractionUI(_focusedActor);
}

void AMyPlayer::ClearFocusedActor()
{
	if (!_focusedActor)
		return;

	IInteractableInterface::Execute_HideInteractionUI(_focusedActor);
	_focusedActor = nullptr;
}

void AMyPlayer::UpdateBestInteractableActor()
{
	// 겹쳐 있는 아이템 or 문이 없으면 포커스 해제
	if (_nearInteractables.Num() == 0)
	{
		ClearFocusedActor();
		return;
	}

	AActor* closestActor = nullptr;
	float minDistance = TNumericLimits<float>::Max();
	FVector playerLocation = GetActorLocation();

	// 가장 가까운 Interactable 액터 찾기 (문 or 아이템)
	for (AActor* actor : _nearInteractables)
	{
		if (!IsValid(actor))
			continue;

		float dist = FVector::DistSquared(playerLocation, actor->GetActorLocation());
		if (dist < minDistance)
		{
			minDistance = dist;
			closestActor = actor;
		}
	}

	// 가장 가까운 아이템 or 문 포커스
	if (closestActor)
		SetFocusedActor(closestActor);
}

void AMyPlayer::Interact()
{	
	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance)
		return;

	// ShopWidget이 열렸을 경우 지우기
	if (_shopWidgetInstance->IsInViewport())
	{
		_shopWidgetInstance->RemoveFromParent();
		return;
	}	
	
	if (IsBusy || !_focusedActor)	// 다른 몽타주 실행 중 or 상호작용 할 객체가 없으면 무시
		return;

	// Item or Tool인 경우
	if (ABaseItem* item = Cast<ABaseItem>(_focusedActor))
	{
		gameInstance->SendGetItem(item->GetItemID(), item->GetIsTool(), gameInstance->GetMyID());
	}
	// Door인 경우
	else if (ABaseDoor* door = Cast<ABaseDoor>(_focusedActor))
	{
		// Lock일 때는 E 상호작용 X
		if (door->GetDoorState() == ObjectState::LOCK)	
			return;

		gameInstance->SendInteractDoor(gameInstance->GetMyID(), door->GetDoorID());
	}
	else if (ABaseHatch* hatch = Cast<ABaseHatch>(_focusedActor))
	{
		gameInstance->SendInteractDoor(gameInstance->GetMyID(), 0);	// Hatch의 ID는 0
		UE_LOG(LogTemp, Display, TEXT("[Hatch] Interact Packet Send!"));
	}
	// Base의 모니터인 경우
	else if (ABaseBase* base = Cast<ABaseBase>(_focusedActor))
	{
		if (!_shopWidgetInstance)
			return;

		if (!_shopWidgetInstance->IsInViewport())
			_shopWidgetInstance->AddToViewport();
	}
}

void AMyPlayer::TurnLanternSendOrUseToolAnimationAndSend()
{
	if (IsBusy)
		return;

	UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (!widget)
		return;

	FDroppedItemInfo ToolInfo = widget->GetSelectedToolBarTool();
	if (ToolInfo.itemID == -1)
		return;

	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance)
		return;

	// 잠긴 문 - 열쇠 사용
	if (ToolInfo.type == ItemType::Key)
	{
		// focusedActor가 문일 때
		if (ABaseDoor* door = Cast<ABaseDoor>(_focusedActor))
		{
			if (door->GetDoorState() == ObjectState::LOCK)
			{
				gameInstance->SendUseKey(gameInstance->GetMyID(), ToolInfo.itemID, door->GetDoorID());
				UE_LOG(LogTemp, Display, TEXT("[Door] Use Key for Locked Door"));

				return;
			}
		}

		// 문 상호작용 범위에 있고 좌클릭하면 작동 X
		return;
	}

	// Lantern 사용 패킷 Send (애니메이션 X)
	if (ToolInfo.type == ItemType::LANTERN)
	{
		gameInstance->SendUseLantern(gameInstance->GetMyID(), ToolInfo.itemID);

		return;
	}

	// 애니메이션 필요한 경우 판단(Key 사용, Lantern 사용 지금은 애니메이션 X)
	bool useAnimation = true;
	FName animName;
	float animSpeed = 1.f;

	switch (ToolInfo.type)
	{
	case ItemType::CUTLASS:
		animName = "Slash";
		break;
	case ItemType::Blaster:
		animName = "Shooting";
		break;
	default:
		useAnimation = false;
		break;
	}

	if (useAnimation)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && ComboMontage)
		{
			IsBusy = true; // 입력 차단 시작

			// 몽타주 실행
			float duration = PlayAnimMontage(ComboMontage, animSpeed, animName);

			if (duration > 0.f)
			{
				// 타이머 대신 종료 델리게이트 설정
				FOnMontageEnded EndDelegate;
				EndDelegate.BindUObject(this, &AMyPlayer::OnToolMontageEnded);
				AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboMontage);
			}
			else
			{
				IsBusy = false; // 재생 실패 시 즉시 해제
			}
		}
	}

	// 서버에 C_UseTool 송신
	FRotator rot = GetControlRotation();
	// - 180 ~ 180 값을 0 ~ 360으로 정규화
	float normPitch = FRotator::NormalizeAxis(rot.Pitch);
	if (normPitch < 0) normPitch += 360.0f;
	float normYaw = FRotator::NormalizeAxis(rot.Yaw);
	if (normYaw < 0) normYaw += 360.0f;
	float normRoll = FRotator::NormalizeAxis(rot.Roll);
	if (normRoll < 0) normRoll += 360.0f;
	Rotation rotation = { normPitch, normYaw, normRoll };

	gameInstance->SendUseTool(gameInstance->GetMyID(), ToolInfo.itemID, rotation);
	//UE_LOG(LogTemp, Log, TEXT("[Tool] Use Tool, Tool ID: %d, Type: %d"), ToolInfo.itemID, (int32)type);
}

void AMyPlayer::InteractSellingMachine()
{
	if (IsBusy || !_overlappedSellingMachine)
		return;

	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance) return;

	// 판매기가 Open 상태 && 아이템이 올려진 상태(크레딧이 있을 때)일 때 판매 패킷 송신
	if (_overlappedSellingMachine->GetMachineState() == ObjectState::OPEN && _overlappedSellingMachine->GetCurrentPendingCredit() > 0)
	{
		gameInstance->SendSellItem(gameInstance->GetMyID(), _overlappedSellingMachine->GetMachineID());

		// 판매가 시작되면 상호작용 UI 가시성 처리
		IInteractableInterface::Execute_Interact(_overlappedSellingMachine);

		UE_LOG(LogTemp, Display, TEXT("[SellingMachine] F Key Interact! Packets Sent."));
	}
}

void AMyPlayer::OnToolMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 몽타주가 정상 종료되었거나, 다른 애니메이션에 의해 끊겼을 때 종료됨
	IsBusy = false;
	UE_LOG(LogTemp, Log, TEXT("[Tool] Montage Ended. IsBusy is now False. Interrupted: %s"), bInterrupted ? TEXT("True") : TEXT("False"));
}
