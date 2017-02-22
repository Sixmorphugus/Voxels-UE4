// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Main Includes
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PolyVoxBridge.h"

#include "VoxelMapActor.generated.h"

class SUPERALCHEMIST_API FVoxelMapPager : public PolyVox::PagedVolume<FVoxel>::Pager
{
public:
	// Constructor
	FVoxelMapPager();

	// Destructor
	virtual ~FVoxelMapPager() {};

	// PagedVolume::Pager functions - used to translate (or generate) voxels to give to polyvox and save them respectively
	virtual void pageIn(const PolyVox::Region& region, PolyVox::PagedVolume<FVoxel>::Chunk* pChunk);
	virtual void pageOut(const PolyVox::Region& region, PolyVox::PagedVolume<FVoxel>::Chunk* pChunk);
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
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, VisibleAnywhere)
	class UProceduralMeshComponent* Mesh;

	// The material to apply to our voxel terrain
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere)
	TArray<UMaterialInterface*> TerrainMaterials;

private:
	TSharedPtr<FVoxelVolume> VoxelVolume;
};
