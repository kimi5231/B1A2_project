// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceSynthComponent.h"

UVoiceSynthComponent::UVoiceSynthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = true;

	NumChannels = 1;
}

bool UVoiceSynthComponent::Init(int32& InSampleRate)
{
	InSampleRate = 48000;
	return true;
}

void UVoiceSynthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVolumeMultiplier(1.0f);
}

void UVoiceSynthComponent::PushAudioByteData(const TArray<uint8>& RawBytes)
{
	if (RawBytes.Num() % 2 != 0) return;

	const int16* PcmData = reinterpret_cast<const int16*>(RawBytes.GetData());
	int32 ElementCount = RawBytes.Num() / 2;

	for (int32 i = 0; i < ElementCount; ++i)
	{
		AudioQueue.Enqueue(PcmData[i]);
	}
}

int32 UVoiceSynthComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
	for (int32 i = 0; i < NumSamples; ++i)
	{
		int16 PcmSample = 0;
		if (AudioQueue.Dequeue(PcmSample))
		{
			OutAudio[i] = static_cast<float>(PcmSample) / 32768.0f;
		}
		else
		{
			OutAudio[i] = 0.0f;
		}
	}
	return NumSamples;
}