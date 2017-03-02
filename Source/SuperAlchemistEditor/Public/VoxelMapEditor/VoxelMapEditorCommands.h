// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyle.h"

class FVoxelMapEditorCommands : public TCommands<FVoxelMapEditorCommands>
{
public:
	FVoxelMapEditorCommands()
		: TCommands<FVoxelMapEditorCommands>(
			TEXT("VoxelMapEditor"), // Context name for fast lookup
			NSLOCTEXT("Contexts", "PaperEditor", "VoxelMap Editor"), // Localized context name for displaying
			NAME_None, // Parent
			FEditorStyle::Get().GetStyleSetName() // Icon Style Set
			)
	{
	}

	// TCommand<> interface
	virtual void RegisterCommands() override;
	// End of TCommand<> interface

public:
	// Show toggles
	TSharedPtr<FUICommandInfo> SetShowGrid;
	TSharedPtr<FUICommandInfo> SetShowMeshEdges;

	// Source region edit mode
	TSharedPtr<FUICommandInfo> ToggleShowVoxelMapNames;

	// Editing modes
	TSharedPtr<FUICommandInfo> EnterViewMode;
	TSharedPtr<FUICommandInfo> EnterPlaceMode;
	TSharedPtr<FUICommandInfo> EnterEditMode;
};
