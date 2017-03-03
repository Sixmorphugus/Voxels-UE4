// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMapComponent.h"
#include "RuntimeMeshComponent.h"

#include "VoxelMap.h"

UVoxelMapComponent::UVoxelMapComponent(const FObjectInitializer& ObjectInitializer)
	: USceneComponent(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Mesh"));
	Mesh->bShouldSerializeMeshData = false;
}

void UVoxelMapComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	UpdateMesh();
}

void UVoxelMapComponent::UpdateMesh()
{
	if (MapAsset)
		MapAsset->GetMesh(Mesh);
	else
		Mesh->ClearAllMeshSections();
}

void UVoxelMapComponent::SetVoxelMap(UVoxelMap* Map)
{
	MapAsset = Map;
	UpdateMesh();
}

UVoxelMap* UVoxelMapComponent::GetVoxelMap()
{
	return MapAsset;
}
