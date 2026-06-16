#include "PlayerMicComponent.h"
#include "VoiceModule.h"
#include "Interfaces/VoiceCapture.h"

UPlayerMicComponent::UPlayerMicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	VoiceCaptureDevice = nullptr;
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
	StopCapture();

	VoiceCaptureDevice = FVoiceModule::Get().CreateVoiceCapture("");
	if (VoiceCaptureDevice.IsValid())
	{
		VoiceCaptureDevice->Start();
	}
}

void UPlayerMicComponent::StopCapture()
{
	if (VoiceCaptureDevice.IsValid())
	{
		VoiceCaptureDevice->Stop();
		VoiceCaptureDevice = nullptr;
	}
}

void UPlayerMicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!VoiceCaptureDevice.IsValid() || !OnVoiceCaptured.IsBound()) return;

	uint32 AvailableDataSize = 0;
	EVoiceCaptureState::Type CaptureState = VoiceCaptureDevice->GetCaptureState(AvailableDataSize);

	// 가져올 데이터가 쌓여있다면
	if (CaptureState == EVoiceCaptureState::Ok && AvailableDataSize > 0)
	{
		TArray<uint8> VoiceBuffer;
		VoiceBuffer.AddUninitialized(AvailableDataSize);

		uint32 ReadDataSize = 0;
		EVoiceCaptureState::Type ReadState = VoiceCaptureDevice->GetVoiceData(VoiceBuffer.GetData(), AvailableDataSize, ReadDataSize);

		if (ReadState == EVoiceCaptureState::Ok && ReadDataSize > 0)
		{
			// 실제로 읽어온 크기만큼 배열 크기 재조정 후 메인으로 송신
			VoiceBuffer.SetNum(ReadDataSize);
			OnVoiceCaptured.Execute(VoiceBuffer);
		}
	}
}