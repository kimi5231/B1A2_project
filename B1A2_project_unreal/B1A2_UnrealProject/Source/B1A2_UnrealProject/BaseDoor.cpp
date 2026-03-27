// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"

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
	
}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

    // 애니메이션 실행
    OnStateChanged(oldState, newState);

    UE_LOG(LogTemp, Log, TEXT("[Door] State Changed: %d -> %d"), (int)oldState, (int)newState);
}

void ABaseDoor::OnStateChanged(ObjectState OldState, ObjectState NewState)
{
    UE_LOG(LogTemp, Display, TEXT("[Door] Animation"));
}

