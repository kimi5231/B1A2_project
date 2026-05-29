// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonster.h"
#include "Components/SceneComponent.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 루트 컴포넌트 생성 및 설정
    DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
    RootComponent = DefaultRoot;
}

void ABaseMonster::SetTargetTransform(FVector Pos, FRotator Rot)
{
	_destPos = Pos;
	_destRot = Rot;
	_isHasTarget = true;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
    _destPos = GetActorLocation();
    _destRot = GetActorRotation();
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!_isHasTarget)
        return;

    // 보간하지 않을 경우(EmotionGame 텔포)
    if (!_isInterpolation)
    {
        SetActorLocationAndRotation(_destPos, _destRot, false, nullptr, ETeleportType::TeleportPhysics);

        _currentAnimSpeed = 0.f;
        CalculatedSpeed = 0.f;
        return;
    }

    FVector oldLocation = GetActorLocation();
  
    // 보간
    FVector newLocation = FMath::VInterpTo(oldLocation, _destPos, DeltaTime, InterpolationSpeed);
    FRotator newRotation = FMath::RInterpTo(GetActorRotation(), _destRot, DeltaTime, InterpolationSpeed);

    SetActorLocationAndRotation(newLocation, newRotation, false, nullptr, ETeleportType::TeleportPhysics);

    FVector deltaMove = (newLocation - oldLocation);
    FVector horizonDelta = FVector(deltaMove.X, deltaMove.Y, 0.f);
    float horizonInstantSpeed = horizonDelta.Size() / DeltaTime;
    float verticalInstantSpeed = deltaMove.Z / DeltaTime;

    float targetSpeed = (FVector::DistSquared(newLocation, _destPos) < 1.f) ? 0.f : horizonInstantSpeed;
    _currentAnimSpeed = FMath::FInterpTo(_currentAnimSpeed, targetSpeed, DeltaTime, AnimSmoothingSpeed);
    CalculatedSpeed = _currentAnimSpeed;

    if (horizonInstantSpeed > 5.f)
    {
        FVector LocalMove = GetActorTransform().InverseTransformVectorNoScale(horizonDelta);
        float TargetAngle = FRotationMatrix::MakeFromX(LocalMove).Rotator().Yaw;
        _currentAnimAngle = FMath::FInterpTo(_currentAnimAngle, TargetAngle, DeltaTime, AnimSmoothingSpeed);
        CalculatedAngle = _currentAnimAngle;
    }

    //UE_LOG(LogTemp, Display, TEXT("[Rotation] %f, %f, %f"), newRotation.Pitch, newRotation.Yaw, newRotation.Roll);
    
    // 공중 상태는 몬스터 필요 없을듯?
    /*  if (GetCharacterMovement())
    {
        IsAirborne = GetCharacterMovement()->IsFalling();
    }
    else
    {
        IsAirborne = FMath::Abs(verticalInstantSpeed) > 150.f;
    }*/
}
