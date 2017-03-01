#include "SuperAlchemistEditor.h"
#include "VoxelMapAssetTypeActions.h"

#include "VoxelMap.h"
#include "VoxelMapEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FVoxelMapAssetTypeActions::FVoxelMapAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FVoxelMapAssetTypeActions::GetName() const
{
	return LOCTEXT("FVoxelMapAssetTypeActionsName", "VoxelMap");
}

FColor FVoxelMapAssetTypeActions::GetTypeColor() const
{
	return FColor::White;
}

UClass * FVoxelMapAssetTypeActions::GetSupportedClass() const
{
	return UVoxelMap::StaticClass();
}

void FVoxelMapAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	/*
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UVoxelMap* Map = Cast<UVoxelMap>(*ObjIt))
		{
			TSharedRef<FVoxelMapEditor> NewEditor(new FVoxelMapEditor());
			NewEditor->InitVoxelMapEditor(Mode, EditWithinLevelEditor, Map);
		}
	}
	*/
}

uint32 FVoxelMapAssetTypeActions::GetCategories()
{
	return MyAssetCategory;
}
