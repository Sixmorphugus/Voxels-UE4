// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperAlchemistEditor.h"

#include "AssetToolsModule.h"
#include "VoxelMapAssetTypeActions.h"
#include "VoxelMapEditor/VoxelMapEditorCommands.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FSuperAlchemistEditor, SuperAlchemistEditor, "SuperAlchemistEditor" );

#define LOCTEXT_NAMESPACE "SuperAlchemistEditor"

FSuperAlchemistEditor::FSuperAlchemistEditor()
{}

void FSuperAlchemistEditor::StartupModule()
{
	FVoxelMapEditorCommands::Register(); // we need to register these commands

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	VoxelMapAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("SuperAlchemist")), LOCTEXT("SuperAlchemistAssetCategory", "SuperAlchemist"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FVoxelMapAssetTypeActions(VoxelMapAssetCategoryBit)));
}

void FSuperAlchemistEditor::ShutdownModule()
{
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	CreatedAssetTypeActions.Empty();
}

void FSuperAlchemistEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FSuperAlchemistEditor::OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent)
{

}

void FSuperAlchemistEditor::OnObjectReimported(UObject* InObject)
{

}
