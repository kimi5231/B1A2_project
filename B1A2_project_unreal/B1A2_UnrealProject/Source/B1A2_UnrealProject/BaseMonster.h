// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

	virtual void BeginPlay();

	// 서버에서 받은 목표 위치와 회전값
	void SetTargetTransform(FVector Pos, FRotator Rot);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CalculatedSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CalculatedAngle = 0.f;

	/*UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsAirborne = false;*/

	UPROPERTY(EditAnywhere, Category = "Movement")
	float InterpolationSpeed = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AnimSmoothingSpeed = 10.0f;

private:
	FVector _destPos;
	FRotator _destRot;
	bool _isHasTarget = false;

	// 내부 보간용
	float _currentAnimSpeed = 0.f;
	float _currentAnimAngle = 0.f;
};
