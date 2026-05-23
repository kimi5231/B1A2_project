#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface  // U - 객체가 인터페이스를 가지고 있다는 걸 알려줌
{
	GENERATED_BODY()
};

class B1A2_UNREALPROJECT_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowInteractionUI();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideInteractionUI();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();
};