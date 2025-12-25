// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Screen.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API AScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
