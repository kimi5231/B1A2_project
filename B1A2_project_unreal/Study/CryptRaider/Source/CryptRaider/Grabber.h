// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void Grab();
	UFUNCTION(BlueprintCallable) void Release();

private:

	UPROPERTY(EditAnywhere) float MaxGrabDistance = 400.f;
	UPROPERTY(EditAnywhere) float GrabRadius = 100.f;

	UPROPERTY(EditAnywhere) float HoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;	// const: 이 함수를 호출할 때 아무것도 변하지 않음

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
