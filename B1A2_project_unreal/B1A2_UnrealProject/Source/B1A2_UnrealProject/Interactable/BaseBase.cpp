// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBase.h"

ABaseBase::ABaseBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);   // 충돌 판정(물리 충돌 X)
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);   // 다른 Collision Channel 만났을 때 무시
    CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);    // Pawn만 감지하도록

    EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
    EWidget->SetupAttachment(RootComponent);
    EWidget->SetVisibility(false);
}

void ABaseBase::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseBase::ShowInteractionUI_Implementation()
{
    if (EWidget)
    {
        EWidget->SetVisibility(true);
        UE_LOG(LogTemp, Log, TEXT("[Shop] Widget Show Called"));
    }
}

void ABaseBase::HideInteractionUI_Implementation()
{
    if (EWidget)
    {
        EWidget->SetVisibility(false);
        UE_LOG(LogTemp, Log, TEXT("[Shop] Widget Hide Called"));
    }
}

void ABaseBase::Interact_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("[Shop] EButton Interact Called"));
}
