// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMapActor.h"

AVoxelMapActor::AVoxelMapActor(const FObjectInitializer& ObjectInitializer)
{
	// Initialize our mesh component
	Mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Map Mesh"));
}

void AVoxelMapActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetMeshFromMapAsset();
}

void AVoxelMapActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	GetMeshFromMapAsset();
}

void AVoxelMapActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GetMeshFromMapAsset();
}

void AVoxelMapActor::GetMeshFromMapAsset()
{
	if (MapAsset)
		MapAsset->GetMesh(Mesh);
	else
		Mesh->ClearAllMeshSections();
}
