// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Network/Packets.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OtherPlayer.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API AOtherPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOtherPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerLocation(FVector location, FRotator rotation);
	void SetPlayerState(ObjectState state);

private:
	FVector _prevPos;
	FRotator _prevRot;
	FVector _destPos;
	FRotator _destRot;
	
	ObjectState _state;

	// Animation 현재 속도와 각도
	float _currentAnimSpeed = 0.f;
	float _currentAnimAngle = 0.f;

protected:
	bool _isInterpolation = true;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	EMoveState _eState;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float InterpolationSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AnimSmoothingSpeed = 10.0f;	// Animation 보간 속도

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CalculatedSpeed;		// 계산된 속도(ABP 사용)

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CalculatedAngle;		// 계산된 각도(ABP 사용)
};
