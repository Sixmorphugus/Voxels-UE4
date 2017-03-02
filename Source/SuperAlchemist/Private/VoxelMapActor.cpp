// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMapActor.h"
#include "VoxelMapComponent.h"

AVoxelMapActor::AVoxelMapActor(const FObjectInitializer& ObjectInitializer)
{
	// Initialize our mesh component
	Map = CreateDefaultSubobject<UVoxelMapComponent>(TEXT("Map"));
}