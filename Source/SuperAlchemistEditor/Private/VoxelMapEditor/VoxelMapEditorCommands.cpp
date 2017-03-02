#include "SuperAlchemistEditor.h"
#include "VoxelMapEditor/VoxelMapEditorCommands.h"

#define LOCTEXT_NAMESPACE "VoxelMapEditor"

//////////////////////////////////////////////////////////////////////////
// FVoxelMapEditorCommands

void FVoxelMapEditorCommands::RegisterCommands()
{
	// Show toggles
	UI_COMMAND(SetShowGrid, "Grid", "Displays the viewport grid.", EUserInterfaceActionType::ToggleButton, FInputChord());
	
	// Source region edit mode
	UI_COMMAND(ToggleShowVoxelMapNames, "VoxelMap Names", "Toggles display of the name of each VoxelMap that shares the same source texture.", EUserInterfaceActionType::ToggleButton, FInputChord());

	// Editing modes
	UI_COMMAND(EnterViewMode, "View", "View the VoxelMap.", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(EnterPlaceMode, "Place Voxels", "Edit the VoxelMap.", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(EnterEditMode, "Edit Voxels", "Edit a Voxel's settings.", EUserInterfaceActionType::ToggleButton, FInputChord());
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
