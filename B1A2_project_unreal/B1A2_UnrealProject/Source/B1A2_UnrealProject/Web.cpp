// Fill out your copyright notice in the Description page of Project Settings.


#include "Web.h"
#include "Components/BoxComponent.h"
#include "Player/MyPlayer.h"

// Sets default values
AWeb::AWeb()
{
	PrimaryActorTick.bCanEverTick = false;

	WebMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WebMesh"));
	RootComponent = WebMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(WebMesh);

	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

}

// Called when the game starts or when spawned
void AWeb::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWeb::OnWebOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWeb::OnWebOverlapEnd);
}

void AWeb::OnWebOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (AMyPlayer* Player = Cast<AMyPlayer>(OtherActor))
		{
			Player->AddWebOverlap();
		}
	}
}

void AWeb::OnWebOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (AMyPlayer* Player = Cast<AMyPlayer>(OtherActor))
		{
			Player->RemoveWebOverlap();
		}
	}
}
