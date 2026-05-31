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

    SubmitWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SubmitWidget"));
    SubmitWidget->SetupAttachment(RootComponent);
    SubmitWidget->SetVisibility(false);
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
    ShowInteractionUI_Dynamic(false);
}

void ABaseBase::HideInteractionUI_Implementation()
{
    if (EWidget) EWidget->SetVisibility(false);
    if (SubmitWidget) SubmitWidget->SetVisibility(false);
    UE_LOG(LogTemp, Log, TEXT("[Base] All Widgets Hidden"));
}

void ABaseBase::Interact_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("[Shop] EButton Interact Called"));
}

void ABaseBase::ShowInteractionUI_Dynamic(bool isInventoryOpen)
{
    if (!EWidget || !SubmitWidget) return;

    if (isInventoryOpen)
    {
        EWidget->SetVisibility(false);
        SubmitWidget->SetVisibility(true);
        UE_LOG(LogTemp, Log, TEXT("[Base] Submit Widget (V) Show Called"));
    }
    else
    {
        SubmitWidget->SetVisibility(false);
        EWidget->SetVisibility(true);
        UE_LOG(LogTemp, Log, TEXT("[Base] Shop Widget (E) Show Called"));
    }
}
