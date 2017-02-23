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
	AVoxelMapActor(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual void OnConstruction(const FTransform& Transform);
	void GetMeshFromMapAsset();

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", BlueprintReadWrite, VisibleAnywhere)
	class URuntimeMeshComponent* Mesh;

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", BlueprintReadWrite, EditAnywhere)
	UVoxelMap* MapAsset;
};
