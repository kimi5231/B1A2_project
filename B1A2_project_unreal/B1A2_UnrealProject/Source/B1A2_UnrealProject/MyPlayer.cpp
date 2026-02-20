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
#include "DrawDebugHelpers.h"	// 라인 트레이스 디버깅용

#include "Main.h"
#include "InteractableInterface.h"

AMyPlayer::AMyPlayer()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnItemOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnItemOverlapEnd);
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

	if (_interactionTimer <= 0.f)
	{
		_interactionTimer = INTERACTION_DELAY;

		CheckItemTrace();
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
		//EnhancedInputComponent->BindAction(GetItemAction, ETriggerEvent::Started, this, &AMyPlayer::GetItemByEKey);
	}
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
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
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyPlayer::OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UInteractableInterface>())
	{
		_nearInteractables.Add(OtherActor);

		UE_LOG(LogTemp, Log,
			TEXT("[Item] Overlap Begin! Added Nearby Item: %s (Count: %d)"),
			*OtherActor->GetName(),
			_nearInteractables.Num());
	}
}

void AMyPlayer::OnItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		_nearInteractables.Remove(OtherActor);

		UE_LOG(LogTemp, Log, TEXT("[Item] OverlapEnd! Removed Nearby Item: %s (Count: %d)"), *OtherActor->GetName(), _nearInteractables.Num());

		// 나가면서 보고 있던 아이템이면 즉시 포커스 해제
		if (_focusedItem == OtherActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Item] OverlapEnd! Focused item left range, clearing focus"));
			ClearFocusedItem();
		}
	}
}

void AMyPlayer::CheckItemTrace()
{
	FHitResult hit;
	if (!LineTrace(hit)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("[Item] Trace, No hit"));
		return;
	}

	AActor* hitActor = hit.GetActor();
	UE_LOG(LogTemp, Warning, TEXT("[Item] Hit Actor: %s"), hitActor ? *hitActor->GetName() : TEXT("None"));

	if (hitActor && _nearInteractables.Contains(hitActor) && hitActor->Implements<UInteractableInterface>())
	{
		UE_LOG(LogTemp, Log, TEXT("[Trace] Valid Interactable Focus: %s"), *hitActor->GetName());
		SetFocusedItem(hitActor);
		return;
	}

	ClearFocusedItem();
}

void AMyPlayer::SetFocusedItem(AActor* newItem)
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

bool AMyPlayer::LineTrace(FHitResult& outHit) const
{
	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + (FollowCamera->GetForwardVector() * 300.f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, Params);

	DrawDebugLine(GetWorld(), start, end, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 2.f);

	// 히트 지점 표시
	if (bHit)
	{
		DrawDebugSphere(GetWorld(),	outHit.ImpactPoint, 8.f, 12, FColor::Blue, false, 0.1f);
	}

	return bHit;
}

//void AMyPlayer::GetItemByEKey()
//{
//	if (CurrentInteractableItem)
//	{
//		IInteractableInterface* interface = Cast<IInteractableInterface>(CurrentInteractableItem);
//
//		if (interface)
//		{
//			// Get Item 패킷 보내기
//			CurrentInteractableItem = nullptr;	// 참조 제거
//		}
//	}
//}
