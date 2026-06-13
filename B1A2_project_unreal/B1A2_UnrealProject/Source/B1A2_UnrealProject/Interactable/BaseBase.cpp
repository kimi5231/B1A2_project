// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBase.h"
#include "Main/Main.h"

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

    // 레버
    LeverCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeverCollisionBox"));
    LeverCollisionBox->SetupAttachment(RootComponent);
    LeverCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    LeverCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    LeverCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    LeverWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LeverWidget"));
    LeverWidget->SetupAttachment(LeverCollisionBox); // 레버 충돌 박스 위치를 기준으로 배치
    LeverWidget->SetVisibility(false);

    LeverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeverMesh"));
    LeverMesh->SetupAttachment(RootComponent);

    bIsPlayerNearLever = false;
}

void ABaseBase::BeginPlay()
{
    Super::BeginPlay();

    if (LeverCollisionBox)
    {
        LeverCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseBase::OnLeverOverlapBegin);
        LeverCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseBase::OnLeverOverlapEnd);
    }
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

void ABaseBase::PlayLeverAnimation()
{
    if (LeverMesh && LeverPullAnim)
    {
        LeverMesh->PlayAnimation(LeverPullAnim, false);
        UE_LOG(LogTemp, Log, TEXT("[Base] Lever Pull Animation Played by Server Packet!"));
    }
}

void ABaseBase::RequestLeverPull()
{
    if (!bIsPlayerNearLever) return;

    UMain* gameInstance = Cast<UMain>(GetGameInstance());
    if (!gameInstance) return;

    // 첫 번째 레버를 당길 때 (Stage 시작 패킷)
    if (LeverPullCount == 0)
    {
        LeverPullCount = 1;
        gameInstance->SendStartStage(true);
        UE_LOG(LogTemp, Display, TEXT("[Stage] Send C_StartStage_Packet (Count: 0->1)"));
    }
    // 두 번째 레버를 당길 때 (Stage 종료 패킷)
    else if (LeverPullCount == 1)
    {
        LeverPullCount = 0;
        gameInstance->SendEndStage(true);
        UE_LOG(LogTemp, Display, TEXT("[Stage] Send C_EndStage_Packet (Count: 1->0)"));
    }
}

void ABaseBase::OnLeverOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->IsA(APawn::StaticClass()))
    {
        bIsPlayerNearLever = true;
        if (LeverWidget)
        {
            LeverWidget->SetVisibility(true);
        }
        UE_LOG(LogTemp, Log, TEXT("[Base] Player Entered Lever Range"));
    }
}

void ABaseBase::OnLeverOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->IsA(APawn::StaticClass()))
    {
        bIsPlayerNearLever = false;
        if (LeverWidget)
        {
            LeverWidget->SetVisibility(false); // 위젯 숨김
        }
        UE_LOG(LogTemp, Log, TEXT("[Base] Player Left Lever Range"));
    }
}
