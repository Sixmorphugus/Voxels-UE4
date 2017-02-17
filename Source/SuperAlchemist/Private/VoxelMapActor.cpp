// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMapActor.h"

#include "PolyVox/CubicSurfaceExtractor.h"
#include "PolyVox/Mesh.h"
using namespace PolyVox;

FVoxelMapPager::FVoxelMapPager()
	: PagedVolume<MaterialDensityPair44>::Pager()
{

}

// Called when a new chunk is paged in
// This function will automatically generate our voxel-based terrain from simplex noise
void FVoxelMapPager::pageIn(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{
	// Now that we have our noise setup, let's loop over our chunk and apply it.
	for (int x = region.getLowerX(); x <= region.getUpperX(); x++)
	{
		for (int y = region.getLowerY(); y <= region.getUpperY(); y++)
		{
			int32 towerHeight = FMath::Rand() % 2;

			for (int z = region.getLowerZ(); z <= region.getUpperZ(); z++) {
				MaterialDensityPair44 Voxel;

				bool bSolid = (z < (towerHeight*2));

				Voxel.setDensity(bSolid ? 255 : 0);
				Voxel.setMaterial(bSolid ? 1 : 0);

				// Voxel position within a chunk always start from zero. So if a chunk represents region (4, 8, 12) to (11, 19, 15)
				// then the valid chunk voxels are from (0, 0, 0) to (7, 11, 3). Hence we subtract the lower corner position of the
				// region from the volume space position in order to get the chunk space position.
				Chunk->setVoxel(x - region.getLowerX(), y - region.getLowerY(), z - region.getLowerZ(), Voxel);
			}
		}
	}
}

// Called when a chunk is paged out
void FVoxelMapPager::pageOut(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{

}

AVoxelMapActor::AVoxelMapActor()
{
	// Initialize our mesh component
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Map Mesh"));
}

// Called after the C++ constructor and after the properties have been initialized.
void AVoxelMapActor::PostInitializeComponents()
{
	// Initialize our paged volume.
	VoxelVolume = MakeShareable(new PagedVolume<MaterialDensityPair44>(new FVoxelMapPager()));

	// Call the base class's function.
	Super::PostInitializeComponents();

	UpdateMesh();
}

void AVoxelMapActor::UpdateMesh()
{
	Mesh->ClearAllMeshSections();

	// Extract the voxel mesh from PolyVox
	PolyVox::Region ToExtract(Vector3DInt32(0, 0, 0), Vector3DInt32(127, 127, 63));
	auto ExtractedMesh = extractCubicMesh(VoxelVolume.Get(), ToExtract);
	auto DecodedMesh = decodeMesh(ExtractedMesh);

	// Define variables to pass into the CreateMeshSection function
	auto Vertices = TArray<FVector>();
	auto Indices = TArray<int32>();
	auto Normals = TArray<FVector>();
	auto UV0 = TArray<FVector2D>();
	auto Colors = TArray<FColor>();
	auto Tangents = TArray<FProcMeshTangent>();
	auto s = 16.f;

	// Loop over all of the triangle vertex indices
	for (uint32 i = 0; i < DecodedMesh.getNoOfIndices() - 2; i += 3)
	{
		// We need to add the vertices of each triangle in reverse or the mesh will be upside down
		auto Index = DecodedMesh.getIndex(i + 2);
		auto Vertex2 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex2.position) * s));

		Index = DecodedMesh.getIndex(i + 1);
		auto Vertex1 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex1.position) * s));

		Index = DecodedMesh.getIndex(i);
		auto Vertex0 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex0.position) * s));

		// Calculate the tangents of our triangle
		const FVector Edge01 = FPolyVoxVector(Vertex1.position - Vertex0.position);
		const FVector Edge02 = FPolyVoxVector(Vertex2.position - Vertex0.position);

		const FVector TangentX = Edge01.GetSafeNormal();
		FVector TangentZ = (Edge01 ^ Edge02).GetSafeNormal();

		for (int32 j = 0; j < 3; j++)
		{
			Tangents.Add(FProcMeshTangent(TangentX, false));
			Normals.Add(TangentZ);
		}
	}

	// Finally create the mesh
	Mesh->CreateMeshSection(0, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
}
