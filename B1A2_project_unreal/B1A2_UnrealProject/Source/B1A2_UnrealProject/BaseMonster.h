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

private:
	FVector _targetLocation;
	FRotator _targetRotation;
	bool _isHasTarget = false;
};
