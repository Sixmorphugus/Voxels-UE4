// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMapActor.h"

AVoxelMapActor::AVoxelMapActor()
{
	// Initialize our mesh component
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Map Mesh"));
}

void AVoxelMapActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	if(e.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AVoxelMapActor, MapAsset))
		if (MapAsset)
			MapAsset->BakeMesh(Mesh);
}
