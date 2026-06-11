// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Widget/ScanInfoWidget.h"

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

    ScanInfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScanWidget"));
    ScanInfoWidget->SetupAttachment(RootComponent);
    ScanInfoWidget->SetVisibility(false);
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

void ABaseItem::OnScanned()
{
    if (ScanInfoWidget)
    {
        ScanInfoWidget->SetVisibility(true);

        // 이미 타이머가 돌면 초기화 (다시 스캔 시)
        GetWorldTimerManager().ClearTimer(ScanDisplayTimerHandle);

        // 3초 후 위젯 숨김
        GetWorldTimerManager().SetTimer(ScanDisplayTimerHandle, this, &ABaseItem::HideScanInfo, 3.0f, false);

        UE_LOG(LogTemp, Display, TEXT("[Scan] Item [%d]"), _itemID);
    }
}

void ABaseItem::HideScanInfo()
{
    if (ScanInfoWidget)
    {
        ScanInfoWidget->SetVisibility(false);
    }
}

void ABaseItem::InitScanInfoWidget()
{
    if (!ScanInfoWidget)
        return;

    UScanInfoWidget* scanWidget = Cast<UScanInfoWidget>(ScanInfoWidget->GetUserWidgetObject());
    if (scanWidget)
    {
        FString name = GetItemNameToString();
        scanWidget->SetScanInfo(_isTool, name, _cost);
    }
}

FString ABaseItem::GetItemNameToString()
{
    switch (_type)
    {
    case ItemType::CardboardBox:  return TEXT("Cardboard Box");
    case ItemType::GoldBar:       return TEXT("Gold Bar");
    case ItemType::RubberDuck:    return TEXT("Rubber Duck");
    case ItemType::PlasticCrate:  return TEXT("Plastic Crate");
    case ItemType::Screw:         return TEXT("Screw");
    case ItemType::PirateHat:     return TEXT("Pirate Hat");
    case ItemType::HardHat:       return TEXT("Hard Hat");
    case ItemType::EngineCore:    return TEXT("Engine Core");
    case ItemType::ScrapMetal:    return TEXT("Scrap Metal");
    case ItemType::EmptyCan:      return TEXT("Empty Can");
    case ItemType::CUTLASS:       return TEXT("Cutlass");
    case ItemType::Blaster:       return TEXT("Blaster");
    case ItemType::Key:           return TEXT("Key");
    case ItemType::LANTERN:       return TEXT("Lantern");
    }
    return TEXT("Unknown Item");
}

