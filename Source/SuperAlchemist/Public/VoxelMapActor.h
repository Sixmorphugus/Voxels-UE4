// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Main Includes
#include "GameFramework/Actor.h"

#include "VoxelMapActor.generated.h"

UCLASS()
class SUPERALCHEMIST_API AVoxelMapActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVoxelMapActor(const FObjectInitializer& ObjectInitializer);

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", BlueprintReadWrite, VisibleAnywhere)
	class UVoxelMapComponent* Map;
};
