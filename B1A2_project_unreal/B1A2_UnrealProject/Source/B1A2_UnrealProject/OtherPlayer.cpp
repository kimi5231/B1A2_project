// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AOtherPlayer::AOtherPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

}

// Called when the game starts or when spawned
void AOtherPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOtherPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isInterpolation)	// MyPlayer에서는 보간 X
	{
		FVector newLocation = FMath::VInterpTo(GetActorLocation(), _destPos, DeltaTime, InterpolationSpeed);
		FRotator newRotation = FMath::RInterpTo(GetActorRotation(), _destRot, DeltaTime, InterpolationSpeed);

		SetActorLocation(newLocation);
		SetActorRotation(newRotation);
	}
}

void AOtherPlayer::SetPlayerLocation(FVector location, FRotator rotation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Other Player Received Pos: %s"),*location.ToString());

	_destPos = location;
	_destRot = rotation;
}

void AOtherPlayer::SetPlayerState(MoveState state)
{
	_state = state;
}
