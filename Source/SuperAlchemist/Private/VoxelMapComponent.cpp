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
	Mesh->bEditableWhenInherited = false;
	Mesh->SetRelativeLocation(FVector(0, 0, 0), false);

	bWantsInitializeComponent = true;
}

void UVoxelMapComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	UpdateMesh();
}

void UVoxelMapComponent::PostLoad()
{
	Super::PostLoad();
	UpdateMesh();
}

void UVoxelMapComponent::UpdateMesh()
{
	if (MapAsset) {
		UE_LOG(LogTemp, Warning, TEXT("Generated mesh"));
		MapAsset->GetMesh(Mesh);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Cleared mesh"));
		Mesh->ClearAllMeshSections();
	}
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
