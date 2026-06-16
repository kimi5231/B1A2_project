#include "PlayerMicComponent.h"
#include "AudioCapture.h"
#include "AudioCaptureCore.h"
#include "AudioDevice.h"

struct FMicCaptureInternal
{
	Audio::FAudioCapture NativeCapture;
};

UPlayerMicComponent::UPlayerMicComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	InternalCapture = nullptr;
}

void UPlayerMicComponent::BeginPlay()
{
	Super::BeginPlay();
	StartCapture();
}

void UPlayerMicComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopCapture();
	Super::EndPlay(EndPlayReason);
}

void UPlayerMicComponent::StartCapture()
{
	// 기존에 실행 중이던 스트림이 있다면 종료
	StopCapture();

	InternalCapture = new FMicCaptureInternal();

	Audio::FAudioCaptureDeviceParams Params;
	Params.DeviceIndex = 0; // 마이크 선택

	auto CaptureCallback = [this](const void* InAudio, int32 NumFrames, int32 NumChannels, int32 InSampleRate, double StreamTime, bool bOverflow)
		{
			if (NumFrames <= 0 || !OnVoiceCaptured.IsBound()) return;

			const float* FloatAudio = static_cast<const float*>(InAudio);
			const int32 NumSamples = NumFrames * NumChannels;

			TArray<uint8> ByteData;
			ByteData.AddUninitialized(NumSamples * sizeof(int16));
			int16* PcmBuffer = reinterpret_cast<int16*>(ByteData.GetData());

			for (int32 i = 0; i < NumSamples; ++i)
			{
				float Scaled = FMath::Clamp(FloatAudio[i], -1.0f, 1.0f) * 32767.0f;
				PcmBuffer[i] = static_cast<int16>(Scaled);
			}

			OnVoiceCaptured.ExecuteIfBound(ByteData);
		};

	InternalCapture->NativeCapture.OpenAudioCaptureStream(Params, CaptureCallback, 512);
	InternalCapture->NativeCapture.StartStream(); 
}

void UPlayerMicComponent::StopCapture()
{
	if (InternalCapture)
	{
		InternalCapture->NativeCapture.StopStream();
		InternalCapture->NativeCapture.CloseStream();
		delete InternalCapture;
		InternalCapture = nullptr;
	}
}