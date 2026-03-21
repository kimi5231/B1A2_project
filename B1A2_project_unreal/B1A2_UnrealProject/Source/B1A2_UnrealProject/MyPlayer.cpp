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

#include "Main.h"
#include "InteractableInterface.h"
#include "BaseItem.h"

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

		UpdateBestInteractableItem();
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
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Triggered, this, &AMyPlayer::UseTool);

		// Tool Bar
		EnhancedInputComponent->BindAction(ToolSlotUpAction, ETriggerEvent::Started, this, &AMyPlayer::ToolSelectUp);
		EnhancedInputComponent->BindAction(ToolSlotDownAction, ETriggerEvent::Started, this, &AMyPlayer::ToolSelectDown);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryTurnOnAndOffAction, ETriggerEvent::Started, this, &AMyPlayer::ToggleInventory);
		EnhancedInputComponent->BindAction(InventoryItemSelectForwardAction, ETriggerEvent::Started, this, &AMyPlayer::InventoryItemSelectForward);
		EnhancedInputComponent->BindAction(InventoryItemSelectBackwardAction, ETriggerEvent::Started, this, &AMyPlayer::InventoryItemSelectBackward);

		// Item or Tool Drop
		EnhancedInputComponent->BindAction(ItemOrToolDropAction, ETriggerEvent::Started, this, &AMyPlayer::ItemOrToolDrop);
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

void AMyPlayer::AddToolToToolBar(ItemType type, int id)
{
	if (_toolBarWidgetInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolBar] _toolBarWidgetInstance is NULL!"));
		return;
	}

	UToolBarWidget* toolBar = Cast<UToolBarWidget>(_toolBarWidgetInstance);
	if (toolBar)
	{
		toolBar->AddTool(id, type);
	}
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
			widget->ChangeSelection(true);

		UE_LOG(LogTemp, Display, TEXT("[Input] Mouse Wheel Up"));
	}
}

void AMyPlayer::ToolSelectDown()
{
	if (_toolBarWidgetInstance)
	{
		UToolBarWidget* widget = Cast<UToolBarWidget>(_toolBarWidgetInstance);

		if (widget)
			widget->ChangeSelection(false);

		UE_LOG(LogTemp, Display, TEXT("[Input] Mouse Wheel Up"));
	}
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
				gameInstance->SendDropItem(gameInstance->GetMyID(), ObjectType::Item, info.itemID);
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
				gameInstance->SendDropItem(gameInstance->GetMyID(), ObjectType::Tool, info.itemID);				
				UE_LOG(LogTemp, Display, TEXT("[Tool] Tool Drop Packet Send! ToolID: %d"), info.itemID);
			}
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

void AMyPlayer::OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseItem* item = Cast<ABaseItem>(OtherActor);
	if (!item)
		return;

	_nearInteractableItem.Add(item);

	//UE_LOG(LogTemp, Log, TEXT("[Item] Overlap Begin! Added Nearby Item: %s (Count: %d)"), *OtherActor->GetName(), _nearInteractableItem.Num());

	// 아이템 인식 중에 아이템이 삭제되는 경우 - 삭제될 때 호출(구독)
	if (item && !item->OnDestroyed.IsAlreadyBound(this, &AMyPlayer::OnItemDestroyed))
	{
		item->OnDestroyed.AddDynamic(this, &AMyPlayer::OnItemDestroyed);
	}
}

void AMyPlayer::OnItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseItem* item = Cast<ABaseItem>(OtherActor);
	if (!item)
		return;

	_nearInteractableItem.Remove(item);
	//UE_LOG(LogTemp, Log, TEXT("[Item] OverlapEnd! Removed Nearby Item: %s (Count: %d)"), *OtherActor->GetName(), _nearInteractableItem.Num());

	// 충돌 끝나면, 보고 있던 아이템 포커스 해제하기
	if (_focusedItem == item)
	{
		//UE_LOG(LogTemp, Warning, TEXT("[Item] OverlapEnd! Focused item left range, clearing focus"));
		ClearFocusedItem();
	}
}

void AMyPlayer::OnItemDestroyed(AActor* destroyedItem)
{
	ABaseItem* item = Cast<ABaseItem>(destroyedItem);
	if (item)
		return;

	_nearInteractableItem.Remove(item);

	if (_focusedItem == item)
		ClearFocusedItem();

	UE_LOG(LogTemp, Log, TEXT("[Item] Item Destroyed in Player Reference"));
}

void AMyPlayer::SetFocusedItem(ABaseItem* newItem)
{
	if (_focusedItem == newItem)
		return;

	if (_focusedItem)
		IInteractableInterface::Execute_HideInteractionUI(_focusedItem);

	_focusedItem = newItem;

	if (_focusedItem)
		IInteractableInterface::Execute_ShowInteractionUI(_focusedItem);
}

void AMyPlayer::ClearFocusedItem()
{
	if (!_focusedItem)
		return;

	IInteractableInterface::Execute_HideInteractionUI(_focusedItem);
	_focusedItem = nullptr;
}

void AMyPlayer::UpdateBestInteractableItem()
{
	// 겹쳐 있는 아이템이 없으면 포커스 해제
	if (_nearInteractableItem.Num() == 0)
	{
		ClearFocusedItem();
		return;
	}

	ABaseItem* closestItem = nullptr;
	float minDistance = TNumericLimits<float>::Max();
	FVector playerLocation = GetActorLocation();

	// 가장 가까운 아이템 찾기
	for (ABaseItem* item : _nearInteractableItem)
	{
		if (!item)
			continue;

		float dist = FVector::DistSquared(playerLocation, item->GetActorLocation());
		if (dist < minDistance)
		{
			minDistance = dist;
			closestItem = item;
		}
	}

	// 가장 가까운 아이템 포커스
	if (closestItem)
		SetFocusedItem(closestItem);
}

void AMyPlayer::Interact()
{
	if (IsBusy)	// 다른 몽타주 실행 중이면 무시
		return;

	if (!_focusedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("[Item] E Key Pressed, but no focused Item"));
		return;
	}

	if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
	{
		UE_LOG(LogTemp, Display, TEXT("[Item/Tool] E Key Pressed, Sending GetItem Request - ID: %d, IsTool: %s, PlayerID: %d"),
			_focusedItem->GetItemID(), _focusedItem->GetIsTool() ? TEXT("True") : TEXT("False"), gameInstance->GetMyID());

		gameInstance->SendGetItem(_focusedItem->GetItemID(), _focusedItem->GetIsTool(), gameInstance->GetMyID());
	}
}

void AMyPlayer::UseTool()
{
	if (IsBusy)
		return;

	IsBusy = true;

	// 아직 Tool 생성이 안 돼서 테스트용으로 애니메이션 넣음
	float duration = PlayAnimMontage(ComboMontage, 1.0f, FName("Slash"));
	if (duration > 0.f)
	{
		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, [this]() {IsBusy = false; }, duration, false);
	}
	else
	{
		IsBusy = false;
	}

	//if (IsBusy || _currentTool == EToolType::None)
	//	return;
	//
	//switch (_currentTool)
	//{
	//case EToolType::None:	// Test
	//case EToolType::Sword:
	//	float duration = PlayAnimMontage(ComboMontage, 1.0f, FName("Slash"));
	//	if (duration > 0.f)
	//	{
	//		FTimerHandle timerHandle;
	//		GetWorldTimerManager().SetTimer(timerHandle, [this]() {IsBusy = false; }, duration, false);
	//	}
	//	break;
	//}
}
