// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "Modules/ModuleInterface.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"

#define SUPERALCHEMIST_EDITOR_MODULE_NAME "SuperAlchemistEditor"

//////////////////////////////////////////////////////////////////////////
// FSuperAlchemistEditor

class FSuperAlchemistEditor : public IModuleInterface
{
public:
	FSuperAlchemistEditor();

	// FSuperAlchemistEditor interface
	
	// End of FSuperAlchemistEditor

private:
	EAssetTypeCategories::Type VoxelMapAssetCategoryBit;

	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;

public:
	virtual void StartupModule();
	virtual void ShutdownModule();

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	// Called when a property on the specified object is modified
	void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);
	void OnObjectReimported(UObject* InObject);
};

