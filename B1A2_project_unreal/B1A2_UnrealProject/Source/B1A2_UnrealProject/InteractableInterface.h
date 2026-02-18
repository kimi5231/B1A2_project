#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface  // U - 객체가 인터페이스를 가지고 있다는 걸 알려줌
{
	GENERATED_BODY()
};

class B1A2_UNREALPROJECT_API IInteractableInterface	 // I - 함수 직접 정의하는 클래스
{
	GENERATED_BODY()

public:
	// UI 숨김 - 보여줌
	virtual void ShowInteractionUI() = 0;
	virtual void HideInteractionUI() = 0;

	// 상호작용
	virtual void Interact() = 0;
};