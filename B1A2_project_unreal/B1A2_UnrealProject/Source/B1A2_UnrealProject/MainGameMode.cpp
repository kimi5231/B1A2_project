// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Main.h"

AMainGameMode::AMainGameMode()
{

}

void AMainGameMode::BeginPlay()
{
	_main = Cast<UMain>(GetWorld()->GetGameInstance());

	if (!_main)
		return;

	_main->ConnectServer();
}
