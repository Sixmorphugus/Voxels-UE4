#pragma once

#include "Vector.h"
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"
#include "PolyVox/Vector.h"
#include "PolyVox/Mesh.h"

#include "Voxel.h"

//typedef PolyVox::MaterialDensityPair44 FVoxel;
typedef PolyVox::PagedVolume<FVoxel> FVoxelVolume;
typedef PolyVox::Region FVoxelRegion;
typedef PolyVox::DefaultIsQuadNeeded<PolyVox::MaterialDensityPair44> FIsVoxelQuadNeeded;

// Bridge between PolyVox Vector3DFloat and Unreal Engine 4 FVector
struct FVoxVector : public FVector
{
    FORCEINLINE FVoxVector()
    {}
 
    explicit FORCEINLINE FVoxVector(EForceInit E)
        : FVector(E)
    {}
 
    FORCEINLINE FVoxVector(float InX, float InY, float InZ)
        : FVector(InX, InY, InX)
    {}
 
    FORCEINLINE FVoxVector(const FVector &InVec)
    {
        FVector::operator=(InVec);
    }
 
    FORCEINLINE FVoxVector(const PolyVox::Vector3DFloat &InVec)
    {
		FVoxVector::operator=(InVec);
    }
 
    FORCEINLINE FVoxVector& operator=(const PolyVox::Vector3DFloat& Other)
    {
        this->X = Other.getX();
        this->Y = Other.getY();
        this->Z = Other.getZ();
 
        DiagnosticCheckNaN();
 
        return *this;
    }

	FORCEINLINE PolyVox::Vector3DFloat convert()
	{
		return PolyVox::Vector3DFloat(X, Y, Z);
	}
};

// Bridge between PolyVox Vector3DInt32 and Unreal Engine 4 FIntVector
struct FVoxIntVector : public FIntVector
{
	FORCEINLINE FVoxIntVector()
	{}

	explicit FORCEINLINE FVoxIntVector(EForceInit E)
		: FIntVector(E)
	{}

	FORCEINLINE FVoxIntVector(int32 InX, int32 InY, int32 InZ)
		: FIntVector(InX, InY, InX)
	{}

	FORCEINLINE FVoxIntVector(const FIntVector &InVec)
	{
		FIntVector::operator=(InVec);
	}

	FORCEINLINE FVoxIntVector(const PolyVox::Vector3DInt32 &InVec)
	{
		FVoxIntVector::operator=(InVec);
	}

	FORCEINLINE FVoxIntVector& operator=(const PolyVox::Vector3DInt32& Other)
	{
		this->X = Other.getX();
		this->Y = Other.getY();
		this->Z = Other.getZ();

		return *this;
	}

	FORCEINLINE PolyVox::Vector3DInt32 convert()
	{
		return PolyVox::Vector3DInt32(X, Y, Z);
	}
};