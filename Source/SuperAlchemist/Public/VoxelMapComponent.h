// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "VoxelMapComponent.generated.h"

class UVoxelMap;

/**
* Renders a voxel map into the world via a RuntimeMeshComponent.
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class SUPERALCHEMIST_API UVoxelMapComponent : public USceneComponent
{
public:
	GENERATED_UCLASS_BODY()

	// Functions
private:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);

public:
	void UpdateMesh();

	UFUNCTION(BlueprintCallable) void SetVoxelMap(UVoxelMap* Map);
	UFUNCTION(BlueprintCallable) UVoxelMap* GetVoxelMap();

private:
	// Voxel Map we use
	UPROPERTY(Category = "Voxels", EditAnywhere)
	UVoxelMap* MapAsset;

public:
	// The procedurally generated mesh that represents our voxels
	UPROPERTY(Category = "Voxels", VisibleAnywhere)
	class URuntimeMeshComponent* Mesh;
};