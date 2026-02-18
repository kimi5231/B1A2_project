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

void ABaseItem::ShowInteractionUI()
{
    if (EWidget)
    {
        EWidget->SetVisibility(true);
        UE_LOG(LogTemp, Log, TEXT("[Item] Widget Show Called"), *GetName());
    }
}

void ABaseItem::HideInteractionUI()
{
}

void ABaseItem::Interact()
{
    if (EWidget)
    {
        EWidget->SetVisibility(false);
    }
}

