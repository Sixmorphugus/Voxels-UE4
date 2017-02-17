// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Polyvox Includes
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"

// Main Includes
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PolyVoxBridge.h"

#include "VoxelMapActor.generated.h"

class FVoxelMapPager : public PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Pager
{
public:
	// Constructor
	FVoxelMapPager();

	// Destructor
	virtual ~FVoxelMapPager() {};

	// PagedVolume::Pager functions
	virtual void pageIn(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);
	virtual void pageOut(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);
};

UCLASS()
class SUPERALCHEMIST_API AVoxelMapActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVoxelMapActor();

	// Called after the C++ constructor and after the properties have been initialized.
	virtual void PostInitializeComponents() override;

	// Called when the actor has begun playing in the level
	void UpdateMesh();

	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere)
	class UProceduralMeshComponent* Mesh;

private:
	TSharedPtr<PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>> VoxelVolume;
};
