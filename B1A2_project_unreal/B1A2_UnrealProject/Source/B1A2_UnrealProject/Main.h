#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Main.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API UMain : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;
};
