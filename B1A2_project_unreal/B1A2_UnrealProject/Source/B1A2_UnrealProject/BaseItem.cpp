// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    ItemMesh->SetupAttachment(RootComponent);
    ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // 메쉬 통과

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->SetSphereRadius(100.f);

    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);   // 충돌 판정(물리 충돌 X)
    CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);   // 다른 Collision Channel 만났을 때 무시
    CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);    // Pawn만 감지하도록

    EWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
    EWidget->SetupAttachment(RootComponent);
    EWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::ShowInteractionUI_Implementation()
{
    if (EWidget)
    {
        EWidget->SetVisibility(true);
        UE_LOG(LogTemp, Log, TEXT("[Item] Widget Show Called"));
    }
}

void ABaseItem::HideInteractionUI_Implementation()
{  
    if (EWidget)
    {
        EWidget->SetVisibility(false);
        UE_LOG(LogTemp, Log, TEXT("[Item] Widget Hide Called"));
    }
}

void ABaseItem::Interact_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("[Item] EButton Interact Called"));
}

