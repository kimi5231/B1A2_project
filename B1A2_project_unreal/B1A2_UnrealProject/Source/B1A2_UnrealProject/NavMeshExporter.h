// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavMeshExporter.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ANavMeshExporter : public AActor
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Navigation")
	void ExportNavMeshToBinary(FString FilePath);
};
