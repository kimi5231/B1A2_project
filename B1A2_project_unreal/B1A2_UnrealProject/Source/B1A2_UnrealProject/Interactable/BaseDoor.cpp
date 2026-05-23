// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"
#include "BaseSellingMachine.h"

// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    DoorFrameMesh->SetupAttachment(RootComponent);

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(DoorFrameMesh);

    WindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WindowMesh"));
    WindowMesh->SetupAttachment(DoorMesh);

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
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
    if (!doorCurve)
        return;

    // 타임라인에 업데이트 함수 바인딩
    FOnTimelineFloat ProgressUpdate;
    ProgressUpdate.BindUFunction(this, FName("UpdateDoorRotation"));
    doorTimeline.AddInterpFloat(doorCurve, ProgressUpdate);

    // 상태에 따라 위젯 변경하도록 신호 보냄
    int32 state;
    switch (_currentState)
    {
    case ObjectState::CLOSE:
    case ObjectState::OPEN:
        state = 0;
        break;
    case ObjectState::LOCK:
        state = 1;
        break;
    }
    K2_UpdateWidgetByState(state);
}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    doorTimeline.TickTimeline(DeltaTime);
}

void ABaseDoor::ShowInteractionUI_Implementation()
{
    if (EWidget)
    {
        EWidget->SetVisibility(true);
    }
}

void ABaseDoor::HideInteractionUI_Implementation()
{
    if (EWidget)
    {
        EWidget->SetVisibility(false);
    }
}

void ABaseDoor::Interact_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("[Door] EButton Interact Called"));
}

void ABaseDoor::UpdateDoorState(ObjectState newState)
{
    if (_currentState == newState)
        return;

    ObjectState oldState = _currentState;
    _currentState = newState;

    UE_LOG(LogTemp, Log, TEXT("[Door] State Changed: %d -> %d"), (int)oldState, (int)newState);

    // 애니메이션 실행(Open, Close)
    if (_currentState != ObjectState::LOCK)
        OnStateChanged(oldState, newState);

    // 상태에 따라 위젯 변경하도록 신호 보냄
    int32 state;
    switch (_currentState)
    {
    case ObjectState::CLOSE:
    case ObjectState::OPEN:
        state = 0;
        break;
    case ObjectState::LOCK:
        state = 1;
        break;
    }
    K2_UpdateWidgetByState(state);
}

void ABaseDoor::SetDoorRotation(ObjectState state)
{
    if (!DoorMesh)
        return;

    switch (state)
    {
    case ObjectState::OPEN:
        DoorMesh->SetRelativeRotation(FRotator(0.f, rotationAngle, 0.f));
        doorTimeline.SetPlaybackPosition(1.0f, false);
        break;
    case ObjectState::CLOSE:
    case ObjectState::LOCK:
        DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
        doorTimeline.SetPlaybackPosition(0.0f, false);
        break;
    }
}

void ABaseDoor::OnStateChanged(ObjectState oldState, ObjectState newState)
{
    switch (newState)
    {
    case ObjectState::OPEN:
        doorTimeline.Play();    // 정방향 재생
        break;
    case ObjectState::CLOSE:
        doorTimeline.Reverse(); // 역방항 재생
        break;
    }

    UE_LOG(LogTemp, Display, TEXT("[Door] Animation"));
}

void ABaseDoor::UpdateDoorRotation(float value)
{
    FRotator newRotation = FRotator(0.f, value * rotationAngle, 0.f);
    DoorMesh->SetRelativeRotation(newRotation);
}