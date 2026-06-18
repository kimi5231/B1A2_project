// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "Containers/Queue.h"
#include "VoiceSynthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class B1A2_UNREALPROJECT_API UVoiceSynthComponent : public USynthComponent
{
	GENERATED_BODY()

public:
	UVoiceSynthComponent(const FObjectInitializer& ObjectInitializer);

	void PushAudioByteData(const TArray<uint8>& RawBytes);

	// 3D °¨¼â
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundAttenuation* VoiceAttenuationSettings;
protected:
	virtual bool Init(int32& InSampleRate) override;
	virtual void BeginPlay() override;

	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;

private:
	TQueue<int16, EQueueMode::Mpsc> AudioQueue;
};