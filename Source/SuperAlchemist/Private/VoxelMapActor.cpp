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
// This function will automatically generate our voxel-based terrain
void FVoxelMapPager::pageIn(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{
	// Now that we have our noise setup, let's loop over our chunk and apply it.
	for (int x = region.getLowerX(); x <= region.getUpperX(); x++)
	{
		for (int y = region.getLowerY(); y <= region.getUpperY(); y++)
		{
			int32 towerHeight = 1;

			for (int z = region.getLowerZ(); z <= region.getUpperZ(); z++) {
				MaterialDensityPair44 Voxel;

				bool bSolid = (z < towerHeight);

				int32 zMat = z+1;

				if (zMat > towerHeight)
					zMat = towerHeight;

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

	// This isn't the most efficient way to handle this, but it works.
	// To improve the performance of this code, you'll want to modify 
	// the code so that you only run this section of code once.
	for (int32 Material = 0; Material < TerrainMaterials.Num(); Material++)
	{
		// Define variables to pass into the CreateMeshSection function
		auto Vertices = TArray<FVector>();
		auto Indices = TArray<int32>();
		auto Normals = TArray<FVector>();
		auto UV0 = TArray<FVector2D>();
		auto Colors = TArray<FColor>();
		auto Tangents = TArray<FProcMeshTangent>();

		// Loop over all of the triangle vertex indices
		for (uint32 i = 0; i < DecodedMesh.getNoOfIndices() - 2; i += 3)
		{
			// We need to add the vertices of each triangle in reverse or the mesh will be upside down
			auto Index = DecodedMesh.getIndex(i + 2);
			auto Vertex2 = DecodedMesh.getVertex(Index);
			auto TriangleMaterial = Vertex2.data.getMaterial();

			float uSize = 16.f;

			// Before we continue, we need to be sure that the triangle is the right material; we don't want to use verticies from other materials
			if (TriangleMaterial == (Material + 1))
			{
				// If it is of the same material, then we need to add the correct indices now
				Indices.Add(Vertices.Add(FPolyVoxVector(Vertex2.position) * uSize));

				Index = DecodedMesh.getIndex(i + 1);
				auto Vertex1 = DecodedMesh.getVertex(Index);
				Indices.Add(Vertices.Add(FPolyVoxVector(Vertex1.position) * uSize));

				Index = DecodedMesh.getIndex(i);
				auto Vertex0 = DecodedMesh.getVertex(Index);
				Indices.Add(Vertices.Add(FPolyVoxVector(Vertex0.position) * uSize));

				// Calculate the tangents of our triangle
				const FVector Edge01 = FPolyVoxVector(Vertex1.position - Vertex0.position);
				const FVector Edge02 = FPolyVoxVector(Vertex2.position - Vertex0.position);

				FVector Normal = (Edge01 ^ Edge02).GetSafeNormal();
				FVector Tangent = Edge01.GetSafeNormal();

				UE_LOG(LogTemp, Warning, TEXT("%s"),
					*Tangent.ToString());

				for (int32 v = 0; v < 3; v++)
				{
					Tangents.Add(FProcMeshTangent(Tangent, false));
					Normals.Add(Normal);
				}
			}
		}

		// Finally create the mesh
		Mesh->CreateMeshSection(Material, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
		Mesh->SetMaterial(Material, TerrainMaterials[Material]);
	}
}
