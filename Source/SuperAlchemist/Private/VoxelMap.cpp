// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemist.h"
#include "VoxelMap.h"

#include "PolyVox/CubicSurfaceExtractor.h"

FVoxelMapPager::FVoxelMapPager()
	: FVoxelVolume::Pager()
{

}

// Called when a new chunk is paged in
// This function will automatically generate our voxel-based terrain
void FVoxelMapPager::pageIn(const FVoxelRegion& region, FVoxelVolume::Chunk* Chunk)
{
	// Now that we have our noise setup, let's loop over our chunk and apply it.
	for (int x = region.getLowerX(); x <= region.getUpperX(); x++)
	{
		for (int y = region.getLowerY(); y <= region.getUpperY(); y++)
		{
			int32 towerHeight = (FMath::Rand() % 3) + 1;

			if (towerHeight < 3)
				towerHeight = 1;

			for (int z = region.getLowerZ(); z <= region.getUpperZ(); z++) {
				FVoxel Voxel;

				bool bSolid = (z < towerHeight);

				int32 zMat = z + 1;

				zMat = (towerHeight > 1) + 1;

				if (bSolid) {
					Voxel.setDensity(255);
					Voxel.setMaterial(zMat);
				}
				else {
					Voxel.setDensity(0);
					Voxel.setMaterial(0);
				}

				// Voxel position within a chunk always start from zero. So if a chunk represents region (4, 8, 12) to (11, 19, 15)
				// then the valid chunk voxels are from (0, 0, 0) to (7, 11, 3). Hence we subtract the lower corner position of the
				// region from the volume space position in order to get the chunk space position.
				Chunk->setVoxel(x - region.getLowerX(), y - region.getLowerY(), z - region.getLowerZ(), Voxel);
			}
		}
	}
}

// Called when a chunk is paged out
void FVoxelMapPager::pageOut(const FVoxelRegion& region, FVoxelVolume::Chunk* Chunk)
{

}

// ---------------------------------

UVoxelMap::UVoxelMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Initialize our paged volume.
	VoxelVolume = MakeShareable(new FVoxelVolume(new FVoxelMapPager()));
}

void UVoxelMap::GetMesh(URuntimeMeshComponent* Mesh)
{
	if (!Mesh)
		return;

	Mesh->ClearAllMeshSections();

	// Extract the voxel mesh from PolyVox
	FVoxelRegion ToExtract(FVoxIntVector(0, 0, 0).convert(), FVoxIntVector(127, 127, 63).convert());
	FIsVoxelQuadNeeded iqn; // nonsense tbh

	auto ExtractedMesh = PolyVox::extractCubicMesh(VoxelVolume.Get(), ToExtract, iqn, false);
	auto DecodedMesh = PolyVox::decodeMesh(ExtractedMesh);

	// This isn't the most efficient way to handle this, but it works.
	for (int32 Material = 0; Material < TerrainMaterials.Num(); Material++)
	{
		// Define variables to pass into the CreateMeshSection function
		auto Vertices = TArray<FVector>();
		auto Indices = TArray<int32>();
		auto Normals = TArray<FVector>();
		auto UV0 = TArray<FVector2D>();
		auto Colors = TArray<FColor>();
		auto Tangents = TArray<FRuntimeMeshTangent>();

		// Loop over all of the triangle vertex indices
		for (uint32 i = 0; i < DecodedMesh.getNoOfIndices() - 2; i += 3)
		{
			// We need to add the vertices of each triangle in reverse or the mesh will be upside down
			auto Index = DecodedMesh.getIndex(i + 2);
			auto Vertex2 = DecodedMesh.getVertex(Index);
			auto TriangleMaterial = Vertex2.data.getMaterial();
			auto Color = Vertex2.data.getColor();

			float uSize = VoxelScale;

			// Before we continue, we need to be sure that the triangle is the right material; we don't want to use verticies from other materials
			if (TriangleMaterial == (Material + 1)) {
				// If it is of the same material, then we need to add the correct indices now
				Indices.Add(Vertices.Add(FVoxVector(Vertex2.position) * uSize));

				Index = DecodedMesh.getIndex(i + 1);
				auto Vertex1 = DecodedMesh.getVertex(Index);
				Indices.Add(Vertices.Add(FVoxVector(Vertex1.position) * uSize));

				Index = DecodedMesh.getIndex(i);
				auto Vertex0 = DecodedMesh.getVertex(Index);
				Indices.Add(Vertices.Add(FVoxVector(Vertex0.position) * uSize));

				// Calculate the tangents of our triangle
				FVector Edge1 = FVoxVector(Vertex0.position - Vertex1.position);
				FVector Edge2 = FVoxVector(Vertex1.position - Vertex2.position);

				FVector Normal = FVector::CrossProduct(Edge1, Edge2);
				FVector Tangent;

				FVector c1 = FVector::CrossProduct(Normal, FVector(0.0, 0.0, 1.0));
				FVector c2 = FVector::CrossProduct(Normal, FVector(0.0, 1.0, 0.0));

				if (c1.Size() > c2.Size())
				{
					Tangent = c1;
				}
				else
				{
					Tangent = c2;
				}

				for (int32 v = 0; v < 3; v++)
				{
					Normals.Add(Normal);
					Tangents.Add(FRuntimeMeshTangent(Tangent, false));
					Colors.Add(Color);
				}
			}
		}

		// Finally create the mesh
		Mesh->CreateMeshSection(Material, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
		Mesh->SetMaterial(Material, TerrainMaterials[Material]);
	}
}
