// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PolyVoxBridge.h"
#include "RuntimeMeshComponent.h"

#include "VoxelMap.generated.h"

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

/**
 * 
 */
UCLASS()
class SUPERALCHEMIST_API UVoxelMap : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	void GetMesh(URuntimeMeshComponent* Mesh);

	// The materials to apply to our voxel terrain
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere)
	TArray<UMaterialInterface*> TerrainMaterials;

	// TODO: stored map data

private:
	TSharedPtr<FVoxelVolume> VoxelVolume;
};
