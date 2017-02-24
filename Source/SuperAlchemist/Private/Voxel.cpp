// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "Voxel.h"

FVoxel::FVoxel()
	: PolyVox::MaterialDensityPair44()
{
}

FVoxel::FVoxel(uint8_t materialId, uint8_t density, const FColor& col)
	: PolyVox::MaterialDensityPair44(materialId, density)
{
	color = col;
}

FColor FVoxel::getColor()
{
	return color;
}

void FVoxel::setColor(const FColor& col)
{
	color = col;
}
