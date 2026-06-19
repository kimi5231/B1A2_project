// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Main.h"
#include "AmbientSoundManager.h"

AMainGameMode::AMainGameMode()
{

}

void AMainGameMode::BeginPlay()
{
	_main = Cast<UMain>(GetWorld()->GetGameInstance());

	if (!_main)
		return;

	_main->CreateBase();

	if (AmbientSoundManagerClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AAmbientSoundManager>(AmbientSoundManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		UE_LOG(LogTemp, Warning, TEXT("[Audio] AmbientSoundManager Spawned!"));
	}
}
