// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "PlayerStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// HP Bar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	// Staminar Bar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	// Battery Bar
	UPROPERTY(meta = (BindWidget))
	UProgressBar* BatteryBar;

	// Weight
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightText;

public:
	void SetHealth(float Ratio) { if (HealthBar) HealthBar->SetPercent(Ratio); }
	void SetStamina(float Ratio) { if (StaminaBar) StaminaBar->SetPercent(Ratio); }
	void SetBattery(float Ratio);
	void SetWeight(float currentWeight);
};
