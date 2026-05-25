// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHatch.h"

// Sets default values
ABaseHatch::ABaseHatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->SetupAttachment(RootComponent);

	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorMesh"));
	LeftDoorMesh->SetupAttachment(DoorFrameMesh);

	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RightDoorMesh->SetupAttachment(DoorFrameMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	// 플레이어 감지 설정
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // 충돌 판정(물리 충돌 X)
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);   // 다른 Collision Channel 만났을 때 무시
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);   // Pawn만 감지하도록

	EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	EWidget->SetupAttachment(RootComponent);
	EWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseHatch::BeginPlay()
{
	Super::BeginPlay();
	
	if (HatchCurve)
	{
		FOnTimelineFloat ProgressUpdate;
		ProgressUpdate.BindUFunction(this, FName("UpdateHatchSlide"));
		HatchTimeline.AddInterpFloat(HatchCurve, ProgressUpdate);
	}
}

// Called every frame
void ABaseHatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HatchTimeline.TickTimeline(DeltaTime);
}

void ABaseHatch::ShowInteractionUI_Implementation()
{
	if (EWidget)
	{
		EWidget->SetVisibility(true);
		UE_LOG(LogTemp, Log, TEXT("[Hatch] Show Widget"));
	}
}

void ABaseHatch::HideInteractionUI_Implementation()
{
	if (EWidget)
	{
		EWidget->SetVisibility(false);
		UE_LOG(LogTemp, Log, TEXT("[Hatch] Hide Widget"));
	}
}

void ABaseHatch::Interact_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[Hatch] EButton Interact Called"));
}

void ABaseHatch::UpdateHatchState(ObjectState newState)
{
	if (_currentState == newState) 
		return;
	
	ObjectState oldState = _currentState;
	_currentState = newState;

	UE_LOG(LogTemp, Log, TEXT("[Hatch] State Changed: %d -> %d"), (int)oldState, (int)newState);

	// 애니메이션 실행
	OnStateChanged(oldState, newState);
}

void ABaseHatch::SetHatchRotation(ObjectState state)
{
	if (!LeftDoorMesh || !RightDoorMesh)
		return;

	switch (state)
	{
	case ObjectState::OPEN:
		LeftDoorMesh->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
		RightDoorMesh->SetRelativeLocation(FVector(-100.f, 0.f, 0.f));
		HatchTimeline.SetPlaybackPosition(1.0f, false);
		break;
	case ObjectState::CLOSE:
		LeftDoorMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		RightDoorMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		HatchTimeline.SetPlaybackPosition(0.0f, false);
		break;
	}
}

void ABaseHatch::OnStateChanged(ObjectState oldState, ObjectState newState)
{
	switch (newState)
	{
	case ObjectState::OPEN:
		HatchTimeline.Play();
		break;
	case ObjectState::CLOSE:
		HatchTimeline.Reverse();
		break;
	}

	UE_LOG(LogTemp, Display, TEXT("[Hatch] Animation"));
}

void ABaseHatch::UpdateHatchSlide(float value)
{
	float Offset = value * MaxSlideDistance;

	LeftDoorMesh->SetRelativeLocation(FVector(-Offset, 0.f, 0.f));
	RightDoorMesh->SetRelativeLocation(FVector(Offset, 0.f, 0.f));
}