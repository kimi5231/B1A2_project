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

		CheckForInteractables();
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
		EnhancedInputComponent->BindAction(GetItemAction, ETriggerEvent::Started, this, &AMyPlayer::GetItemByEKey);
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

void AMyPlayer::CheckForInteractables()
{
	float interactionRadius = 100.0f;
	FVector playerLocation = GetActorLocation();
	FVector forward = GetActorForwardVector();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->OverlapMultiByChannel(
		overlapResults,
		playerLocation,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(interactionRadius),
		queryParams
	);

	AActor* closestActor = nullptr;
	float minDistance = interactionRadius;

	// 검출된 총 액터 수 출력
	if (bHit && overlapResults.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[Item] Overlap Count: %d"), overlapResults.Num());
	}

	for (auto& Result : overlapResults)
	{
		AActor* hitActor = Result.GetActor();
		if (hitActor && hitActor->Implements<UInteractableInterface>())
		{
			FVector directionToItem = (hitActor->GetActorLocation() - playerLocation).GetSafeNormal();
			float dotProduct = FVector::DotProduct(forward, directionToItem);

			// 인터페이스를 가진 액터를 찾았을 때의 내적 값과 이름 출력
			UE_LOG(LogTemp, Warning, TEXT("[Item] Found Interactable: %s, DotProduct: %f"), *hitActor->GetName(), dotProduct);

			if (dotProduct > 0.0f)
			{
				float distance = GetDistanceTo(hitActor);
				if (distance < minDistance)
				{
					minDistance = distance;
					closestActor = hitActor;
				}
			}
		}
	}

	if (CurrentInteractableItem != closestActor)
	{
		if (CurrentInteractableItem)
		{
			Cast<IInteractableInterface>(CurrentInteractableItem)->HideInteractionUI();
		}

		CurrentInteractableItem = closestActor;

		if (CurrentInteractableItem)
		{
			// 최종 타겟이 확정
			UE_LOG(LogTemp, Error, TEXT("[Item] Final Target Selected: %s"), *CurrentInteractableItem->GetName());
			Cast<IInteractableInterface>(CurrentInteractableItem)->ShowInteractionUI();
		}
		else
		{
			// 범위 내에 아무것도 없을 때
			UE_LOG(LogTemp, Log, TEXT("[Item] No Target in Range"));
		}
	}
}

void AMyPlayer::GetItemByEKey()
{
	if (CurrentInteractableItem)
	{
		IInteractableInterface* interface = Cast<IInteractableInterface>(CurrentInteractableItem);

		if (interface)
		{
			// Get Item 패킷 보내기
			CurrentInteractableItem = nullptr;	// 참조 제거
		}
	}
}
