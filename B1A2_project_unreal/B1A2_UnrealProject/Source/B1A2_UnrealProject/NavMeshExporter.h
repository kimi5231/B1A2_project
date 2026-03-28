// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityActor.h"
#include "NavMeshExporter.generated.h"

UCLASS()
class B1A2_UNREALPROJECT_API ANavMeshExporter : public AEditorUtilityActor
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ExportNavMeshToBinary(FString FilePath);
};
