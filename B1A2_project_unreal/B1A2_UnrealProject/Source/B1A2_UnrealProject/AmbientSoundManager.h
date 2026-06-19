// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientSoundManager.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API AAmbientSoundManager : public AActor
{
	GENERATED_BODY()
	
public:
	AAmbientSoundManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* FactorySound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* AtmosphereSound;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float PlayInterval = 180.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float FirstPlayDelay = 10.0f;	// 수정해야함 테스트 위해 (기본 60)

	UPROPERTY(EditAnywhere, Category = "Settings")
	float FactoryDuration = 17.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float AtmosphereDuration = 9.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float FadeTime = 3.0f;

private:
	FTimerHandle SequenceTimerHandle;
	FTimerHandle StopTimerHandle;

	int32 PlayCount = 0;

	void PlayNextAmbient();
	void StartFadeOut();

};
