// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/GCObject.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"

class FToolBarBuilder;
class UVoxelMap;
class SVoxelMapEditorViewport;

//////////////////////////////////////////////////////////////////////////
// 

namespace EVoxelMapEditorMode
{
	enum Type
	{
		ViewMode,
		PlaceMode,
		EditMode
	};
}

//////////////////////////////////////////////////////////////////////////
// FVoxelMapEditor

class FVoxelMapEditor : public FAssetEditorToolkit, public FGCObject
{
public:
	FVoxelMapEditor();

	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;
	// End of FAssetEditorToolkit

	// FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FSerializableObject interface
public:
	void InitVoxelMapEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UVoxelMap* InitVoxelMap);

	UVoxelMap* GetVoxelMapBeingEdited() const { return VoxelMapBeingEdited; }
	void SetVoxelMapBeingEdited(UVoxelMap* NewVoxelMap);

	EVoxelMapEditorMode::Type GetMode();

protected:
	UVoxelMap* VoxelMapBeingEdited;
	TSharedPtr<SVoxelMapEditorViewport> ViewportPtr;

protected:
	void BindCommands();
	void ExtendMenu();
	void ExtendToolbar();

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	//TSharedRef<SDockTab> SpawnTab_VoxelMapList(const FSpawnTabArgs& Args);

	void CreateModeToolbarWidgets(FToolBarBuilder& ToolbarBuilder);
};