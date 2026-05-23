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

    FVector oldLocation = GetActorLocation();

    float distance = FVector::Dist(oldLocation, _destPos);
    const float teleportThreshold = 300.f;  // 3미터 이상 차이나면 텔레포트

    if (distance > teleportThreshold)
    {
        // 보간을 타지 않고 즉시 위치/회전 설정
        SetActorLocationAndRotation(_destPos, _destRot, false, nullptr, ETeleportType::TeleportPhysics);

        // 보간용 내부 변수들도 즉시 업데이트해서 Tick에서 튀는 현상 방지
        _currentAnimSpeed = 0.f;
        CalculatedSpeed = 0.f;
    }

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
