// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseItem.h"
#include "Main.h"

// Sets default values
AOtherPlayer::AOtherPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

}

// Called when the game starts or when spawned
void AOtherPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOtherPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_isInterpolation)	// MyPlayer에서는 보간 X
		return;

	// 보간 전 위치 저장
	FVector oldLocation = GetActorLocation();
	
	// 위치 보간
	FVector newLocation = FMath::VInterpTo(oldLocation, _destPos, DeltaTime, InterpolationSpeed);
	// 회전 보간
	FRotator newRotation = FMath::RInterpTo(GetActorRotation(), _destRot, DeltaTime, InterpolationSpeed);

	SetActorLocationAndRotation(newLocation, newRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// 이동 벡터 계산
	FVector deltaMove = (newLocation - oldLocation);

	// 수평(XY) 속도와 수직(Z) 속도 분리! - 점프할 때 달리기 애니메이션 나오면 안 됨
	FVector horizonDelta = FVector(deltaMove.X, deltaMove.Y, 0.f);
	float horizonInstantSpeed = horizonDelta.Size() / DeltaTime;
	float verticalInstantSpeed = deltaMove.Z / DeltaTime;

	// 애니메이션용 변수 적용
	float targetSpeed = (FVector::DistSquared(newLocation, _destPos) < 1.f) ? 0.f : horizonInstantSpeed;
	_currentAnimSpeed = FMath::FInterpTo(_currentAnimSpeed, targetSpeed, DeltaTime, AnimSmoothingSpeed);
	CalculatedSpeed = _currentAnimSpeed;

	if (horizonInstantSpeed > 5.f)
	{
		FVector LocalMove = GetActorTransform().InverseTransformVectorNoScale(horizonDelta);
		float TargetAngle = FRotationMatrix::MakeFromX(LocalMove).Rotator().Yaw;
		_currentAnimAngle = FMath::FInterpTo(_currentAnimAngle, TargetAngle, DeltaTime, AnimSmoothingSpeed);
		CalculatedAngle = _currentAnimAngle;
	}

	// Z축으로 10.f 이상 움직이면 공중으로 판단함
	IsAirborne = FMath::Abs(verticalInstantSpeed) > 10.f;
}

void AOtherPlayer::SetPlayerLocation(FVector location, FRotator rotation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Other Player Received Pos: %s"),*location.ToString());

	_destPos = location;
	_destRot = rotation;
}

void AOtherPlayer::SetPlayerState(ObjectState state)
{
	_state = state;
	
	switch (state)
	{
	case IDLE:
		_eState = EMoveState::MOVE_STATE_IDLE;
		break;
	case RUN:
		_eState = EMoveState::MOVE_STATE_RUN;
		break;
	case JUMP:
		_eState = EMoveState::MOVE_STATE_JUMP;
		break;
	default:
		break;
	}
}

void AOtherPlayer::PlayPickUpAnimation(ABaseItem* item)
{
	if (!item || !ComboMontage) return;

	IsBusy = true;
	_currentPickingUpItem = item;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		// 재생
		float Duration = PlayAnimMontage(ComboMontage, 1.0f, FName("TakeItem"));

		if (Duration > 0.f)
		{
			IsBusy = true;
			_currentPickingUpItem = item;

			// 아이템 파괴 Notify 연결
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AOtherPlayer::PickUpNotifyReached);

			// 종료 델리게이트 설정 (애니메이션 재생 후 이동 가능하도록 설정)
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &AOtherPlayer::PickUpMontageEnded);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboMontage);
		}
	}

	// 인벤토리에 넣기!!!
	// ...
}

void AOtherPlayer::PickUpNotifyReached(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == FName("DestroyItem"))
	{
		if (_currentPickingUpItem)
		{
			_currentPickingUpItem->Destroy();
			_currentPickingUpItem = nullptr;
		}

		// 델리게이트 해제
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AOtherPlayer::PickUpNotifyReached);
		}
	}
}

void AOtherPlayer::PickUpMontageEnded(UAnimMontage* montage, bool bIntererrupted)
{
	IsBusy = false;
	UE_LOG(LogTemp, Log, TEXT("Montage Finished! Player is now free."));
}
