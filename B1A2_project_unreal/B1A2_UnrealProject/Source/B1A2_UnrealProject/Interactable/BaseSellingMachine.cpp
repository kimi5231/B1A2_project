// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSellingMachine.h"

// Sets default values
ABaseSellingMachine::ABaseSellingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MachineBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineBodyMesh"));
	MachineBodyMesh->SetupAttachment(RootComponent);

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(MachineBodyMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	EWidget->SetupAttachment(RootComponent);
	EWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseSellingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	// 타임라인에 업데이트 함수 바인딩
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("UpdateLeverAnimation"));
	leverTimeline.AddInterpFloat(leverCurve, ProgressUpdate);

	// 초기 위젯 상태 설정
	UpdateWidgetState();
}

// Called every frame
void ABaseSellingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	leverTimeline.TickTimeline(DeltaTime);
}

void ABaseSellingMachine::ShowInteractionUI_Implementation()
{
	if (EWidget)
	{
		EWidget->SetVisibility(true);
	}
}

void ABaseSellingMachine::HideInteractionUI_Implementation()
{
	if (EWidget)
	{
		EWidget->SetVisibility(false);
	}
}

void ABaseSellingMachine::Interact_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[SellingMachine] FButton Interact Called and Hide Widget"));
}

void ABaseSellingMachine::UpdateMachineState(ObjectState newState)
{
	UE_LOG(LogTemp, Log, TEXT("[SellingMachine] UpdateMachineState Requested. MachineID: %d, OldState: %d -> NewState: %d"),
		GetMachineID(), (int32)_currentState, (int32)newState);

	if (_currentState == newState)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SellingMachine] State is already identical. Skipping update."));
		return;
	}

	ObjectState oldState = _currentState;
	_currentState = newState;

	// 상태 변화에 따른 레버 연출 실행
	OnStateChanged(oldState, _currentState);

	// 상태 변화에 맞춰 위젯 새로고침
	UpdateWidgetState();
}

void ABaseSellingMachine::SetLeverLength(ObjectState state)
{
	if (!LeverMesh)
		return;

	switch (state)
	{
	case ObjectState::CLOSE:
		LeverMesh->SetRelativeLocation(FVector(0.f, 0.f, LeverDistance));
		leverTimeline.SetPlaybackPosition(1.0, false);
		break;
	case ObjectState::OPEN:
		LeverMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		leverTimeline.SetPlaybackPosition(0.f, false);
		break;
	}
}

void ABaseSellingMachine::ResetPendingCredit()
{
	_currentPendingCredit = 0;
	UpdateWidgetState();
}

bool ABaseSellingMachine::CanAddCredit(int32 itemCost) const
{
	return (_currentPendingCredit + itemCost) <= _maxCredit;
}

void ABaseSellingMachine::AddPendingCredit(int32 itemCost)
{
	_currentPendingCredit += itemCost;
	
	UE_LOG(LogTemp, Display, TEXT("[SellingMachine] AddPendingCredit. MachineID: %d, Credit: %d (Max: %d)"),
		GetMachineID(), _currentPendingCredit, _maxCredit);

	UpdateWidgetState();
}

void ABaseSellingMachine::UpdateWidgetState()
{
	K2_UpdateWidget(_remainCredit, _currentPendingCredit);

	UE_LOG(LogTemp, Log, TEXT("[SellingMachine] UpdateWidgetState Unified. MachineID: %d, RemainCredit: %d, PendingCredit: %d"),
		GetMachineID(), _remainCredit, _currentPendingCredit);
}

void ABaseSellingMachine::PlaySellAnimation()
{
	// state는 변경하지 않고, 레버를 올리는 애니메이션 실행
	leverTimeline.Play();

	// 기존에 돌고 있던 타이머가 있다면 초기화
	GetWorld()->GetTimerManager().ClearTimer(_leverTimerHandle);

	// 3초 후에 레버를 다시 내리도록 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(_leverTimerHandle, this, &ABaseSellingMachine::ReverseLeverTimer, 3.0f, false);

	UpdateWidgetState();
}

void ABaseSellingMachine::OnStateChanged(ObjectState oldState, ObjectState newState)
{
	switch (newState)
	{
	case ObjectState::CLOSE:
		leverTimeline.Play();
		break;
	case ObjectState::OPEN:
		leverTimeline.Reverse();
		break;
	}
}

void ABaseSellingMachine::UpdateLeverAnimation(float value)
{
	FVector newLocation = FVector(0.f, 0.f, value * LeverDistance);
	LeverMesh->SetRelativeLocation(newLocation);
}

void ABaseSellingMachine::ReverseLeverTimer()
{
	// 현재 상태가 Open일 때만 레버를 내림
	if (_currentState == ObjectState::OPEN)
	{
		leverTimeline.Reverse();
		UpdateWidgetState();
	}
}

