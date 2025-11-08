// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		UE_LOG(LogTemp, Display, TEXT("Unlocking"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Relocking"));
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)	// TArray의 모든 액터를 순회
	{
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return Actor;
		}
	}

	return nullptr;		// 액터를 발견하지 못한 경우
}