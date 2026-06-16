#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMicComponent.generated.h"

// 데이터가 추출되었을 때 Main에 알려줄 델리게이트
DECLARE_DELEGATE_OneParam(FOnVoiceCaptured, const TArray<uint8>&);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class B1A2_UNREALPROJECT_API UPlayerMicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerMicComponent();

	void StartCapture();
	void StopCapture();
	
	FOnVoiceCaptured OnVoiceCaptured;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 장치
	TSharedPtr<class IVoiceCapture> VoiceCaptureDevice;
};