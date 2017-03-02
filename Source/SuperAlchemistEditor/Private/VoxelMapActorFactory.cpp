// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SuperAlchemistEditor.h"
#include "VoxelMapActorFactory.h"
#include "AssetData.h"
#include "VoxelMapActor.h"
#include "VoxelMapComponent.h"
#include "VoxelMap.h"

//////////////////////////////////////////////////////////////////////////
// UVoxelMapActorFactory

UVoxelMapActorFactory::UVoxelMapActorFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DisplayName = NSLOCTEXT("SuperAlchemist", "VoxelMapFactoryDisplayName", "Add Voxel Map");
	NewActorClass = AVoxelMapActor::StaticClass();
}

void UVoxelMapActorFactory::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);

	if (UVoxelMap* VM = Cast<UVoxelMap>(Asset))
	{
		AVoxelMapActor* TypedActor = CastChecked<AVoxelMapActor>(NewActor);
		TypedActor->Map->SetVoxelMap(VM);
	}
}

bool UVoxelMapActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (AssetData.IsValid() && AssetData.GetClass()->IsChildOf(UVoxelMap::StaticClass()))
	{
		return true;
	}
	else
	{
		OutErrorMsg = NSLOCTEXT("SuperAlchemist", "CanCreateActorFrom_NoVM", "No map was specified.");
		return false;
	}
}