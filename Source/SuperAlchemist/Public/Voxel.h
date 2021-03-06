// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Polyvox Includes
#include "PolyVox/MaterialDensityPair.h"

class SUPERALCHEMIST_API FVoxel : public PolyVox::MaterialDensityPair44
{
public:
	FVoxel();
	FVoxel(uint8_t materialId, uint8_t density, const FColor& col = FColor(255, 255, 255));

	FColor getColor();
	void setColor(const FColor& col);

private:
	FColor color;
};