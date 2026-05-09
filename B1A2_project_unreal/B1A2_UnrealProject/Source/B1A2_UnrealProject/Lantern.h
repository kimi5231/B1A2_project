// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Lantern.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API ALantern : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ALantern();

	void UpdateLantern(bool isOn, float range);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPointLightComponent* PointLight;
};
