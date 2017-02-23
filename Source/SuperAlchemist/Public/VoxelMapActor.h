// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Main Includes
#include "GameFramework/Actor.h"
#include "VoxelMap.h"

#include "VoxelMapActor.generated.h"

UCLASS()
class SUPERALCHEMIST_API AVoxelMapActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVoxelMapActor();

	// Called after the C++ constructor and after the properties have been initialized.
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", BlueprintReadWrite, VisibleAnywhere)
	class UProceduralMeshComponent* Mesh;

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", BlueprintReadWrite, EditAnywhere)
	UVoxelMap* MapAsset;
};
