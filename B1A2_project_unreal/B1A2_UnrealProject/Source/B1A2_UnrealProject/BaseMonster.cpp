// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseMonster::SetTargetTransform(FVector Pos, FRotator Rot)
{
	_targetLocation = Pos;
	_targetRotation = Rot;
	_isHasTarget = true;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_isHasTarget)
    {
        FVector newLocation = FMath::VInterpTo(GetActorLocation(), _targetLocation, DeltaTime, 15.0f);
        SetActorLocation(newLocation);

        FRotator newRotation = FMath::RInterpTo(GetActorRotation(), _targetRotation, DeltaTime, 15.0f);
        SetActorRotation(newRotation);
    }
}
