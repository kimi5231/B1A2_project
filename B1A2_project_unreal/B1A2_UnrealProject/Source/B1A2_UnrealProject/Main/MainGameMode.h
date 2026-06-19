// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class UMain;
class AAmbientSoundManager;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AMainGameMode();

protected:
	virtual void BeginPlay() override;

	// πË∞Ê¿Ω
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TSubclassOf<AAmbientSoundManager> AmbientSoundManagerClass;

private:
	UMain* _main;
};
