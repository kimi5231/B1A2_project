// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class UMain;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AMainGameMode();

	virtual void BeginPlay() override;

private:
	UMain* _main;
};
