// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Network/UnrealPackets.h"

#include "Engine/EngineTypes.h"     
#include "Engine/World.h"           
#include "CollisionQueryParams.h"   
#include "Engine/OverlapResult.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Main.h"
#include "InteractableInterface.h"
#include "BaseItem.h"
#include "BaseDoor.h"

#include "InventoryWidget.h" 
#include "ToolBarWidget.h" 
#include "Blueprint/UserWidget.h"

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
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		// Get Item
		EnhancedInputComponent->BindAction(GetItemAction, ETriggerEvent::Started, this, &AMyPlayer::Interact);

		// Use Tool
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Triggered, this, &AMyPlayer::UseToolAnimationAndSend);

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

void AMyPlayer::AddItemToInventory(ItemType type, int id, float weight)
{
	if (_inventoryWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] _inventoryWidgetInstance is NULL!"));
		return;
	}

	UInventoryWidget* inventory = Cast<UInventoryWidget>(_inventoryWidgetInstance);
	if (inventory)
	{
		inventory->AddItem(id, type, weight);
		UE_LOG(LogTemp, Display, TEXT("[Inventory] Add Item Success!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Inventory] Cast to UInventoryWidget Failed!"));
	}
}

int32 AMyPlayer::AddToolToToolBar(ItemType type, int id, float weight)
{
	if (_toolBarWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolBar] _toolBarWidgetInstance is NULL!"));
		return -1;
	}

	UToolBarWidget* toolBar = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (toolBar)
	{
		return toolBar->AddTool(id, type, weight);
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
			// 패킷 보내기
			if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
			{
				gameInstance->SendDropItem(gameInstance->GetMyID(), false, info.itemID);
				UE_LOG(LogTemp, Display, TEXT("[Item] Item Drop Packet Send! ItemID: %d"), info.itemID);
			}
		}
	}
	// Inventory가 닫혀있을 때, 선택된 장비 버리기
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
		return;

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
		GetWorldTimerManager().ClearTimer(ScanTimerHandle);
		return;
	}

	CurrentScanAlpha -= (0.01f / ScanEffectDuration);
	ScanMaterialInst->SetScalarParameterValue(TEXT("ScanIntensity"), CurrentScanAlpha);
}

void AMyPlayer::OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
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
	if (!OtherActor)
		return;

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
	if (IsBusy || !_focusedActor)	// 다른 몽타주 실행 중 or 상호작용 할 객체가 없으면 무시
		return;

	UMain* gameInstance = Cast<UMain>(GetGameInstance());
	if (!gameInstance)
		return;

	// Item or Tool인 경우
	if (ABaseItem* item = Cast<ABaseItem>(_focusedActor))
	{
		gameInstance->SendGetItem(item->GetItemID(), item->GetIsTool(), gameInstance->GetMyID());
	}
	// Door인 경우
	else if (ABaseDoor* door = Cast<ABaseDoor>(_focusedActor))
	{
		gameInstance->SendInteractDoor(gameInstance->GetMyID(), door->GetDoorID());
	}
}

void AMyPlayer::UseToolAnimationAndSend()
{
	if (IsBusy)
		return;

	UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (!widget)
		return;

	FDroppedItemInfo ToolInfo = widget->GetSelectedToolBarTool();
	if (ToolInfo.itemID == -1)
		return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ComboMontage)
	{
		IsBusy = true; // 입력 차단 시작

		// 몽타주 실행
		float duration = PlayAnimMontage(ComboMontage, 1.0f, FName("Slash"));

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

	// 서버에 C_UseTool 송신
	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{	
		FRotator rot = GetControlRotation();
		// - 180 ~ 180 값을 0 ~ 360으로 정규화
		float normPitch = FRotator::NormalizeAxis(rot.Pitch);
		if (normPitch < 0) normPitch += 360.0f;
		float normYaw = FRotator::NormalizeAxis(rot.Yaw);
		if (normYaw < 0) normYaw += 360.0f;
		float normRoll = FRotator::NormalizeAxis(rot.Roll);
		if (normRoll < 0) normRoll += 360.0f;
		Rotation rotation = { normPitch, normYaw, normRoll };

		gameInstance->SendUseTool(gameInstance->GetMyID(),ToolInfo.itemID, rotation);
		//UE_LOG(LogTemp, Log, TEXT("[Tool] Use Tool, Tool ID: %d, Type: %d"), ToolInfo.itemID, (int32)type);
	}
}

void AMyPlayer::OnToolMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 몽타주가 정상 종료되었거나, 다른 애니메이션에 의해 끊겼을 때 종료됨
	IsBusy = false;
	UE_LOG(LogTemp, Log, TEXT("[Tool] Montage Ended. IsBusy is now False. Interrupted: %s"), bInterrupted ? TEXT("True") : TEXT("False"));
}
