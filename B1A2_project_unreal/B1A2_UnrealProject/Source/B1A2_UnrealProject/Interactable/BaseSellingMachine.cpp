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

	// 플레이어 감지 설정
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
	ProgressUpdate.BindUFunction(this, FName("UpdateMachineRotation"));
	leverTimeline.AddInterpFloat(leverCurve, ProgressUpdate);

	// 상태에 따라 위젯 변경하도록 신호 보냄
	// 0: 판매 불가능, 1: 판매 가능
	int32 state;
	switch (_currentState)
	{
	case ObjectState::CLOSE:
		state = 0;
		break;
	case ObjectState::OPEN:
		state = 1;
		break;
	}
	K2_UpdateWidgetByState(state);
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
	// 판매하기 상태에서 버튼을 누르면 위젯 숨김
	// ...

	UE_LOG(LogTemp, Log, TEXT("[SellingMachine] EButton Interact Called"));
}

void ABaseSellingMachine::UpdateMachineState(ObjectState newState)
{
	if (_currentState == newState)
		return;

	ObjectState oldState = _currentState;
	_currentState = newState;

	// 상태 변화에 따른 레버 연출 실행
	OnStateChanged(oldState, _currentState);

	// 상태에 따라 위젯 변경하도록 신호 보냄
	int state;
	switch (_currentState)
	{
	case ObjectState::CLOSE:
		state = 0;
		break;
	case ObjectState::OPEN:
		state = 1;
		break;
	}
	K2_UpdateWidgetByState(state);
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
	FVector newLocation = FVector(0.f, value * LeverDistance, 0.f);
	LeverMesh->SetRelativeLocation(newLocation);
}

