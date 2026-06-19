// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientSoundManager.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"

AAmbientSoundManager::AAmbientSoundManager()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientAudio"));
	AudioComponent->bAutoActivate = false;

	AudioComponent->bAllowSpatialization = false;
	RootComponent = AudioComponent;
}

void AAmbientSoundManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SequenceTimerHandle, this, &AAmbientSoundManager::PlayNextAmbient, PlayInterval, true, FirstPlayDelay);
}

void AAmbientSoundManager::PlayNextAmbient()
{
	if (PlayCount >= 4)
	{
		GetWorldTimerManager().ClearTimer(SequenceTimerHandle);
		return;
	}

	if (PlayCount % 2 == 0)
	{
		if (FactorySound)
		{
			AudioComponent->SetSound(FactorySound);
			AudioComponent->FadeIn(FadeTime, 1.0f);

			GetWorldTimerManager().SetTimer(StopTimerHandle, this, &AAmbientSoundManager::StartFadeOut, FactoryDuration, false);
		}
	}
	else
	{
		if (AtmosphereSound)
		{
			AudioComponent->SetSound(AtmosphereSound);
			AudioComponent->FadeIn(FadeTime, 1.0f);

			GetWorldTimerManager().SetTimer(StopTimerHandle, this, &AAmbientSoundManager::StartFadeOut, AtmosphereDuration, false);
		}
	}

	PlayCount++;
}

void AAmbientSoundManager::StartFadeOut()
{
	AudioComponent->FadeOut(FadeTime, 0.0f);
}