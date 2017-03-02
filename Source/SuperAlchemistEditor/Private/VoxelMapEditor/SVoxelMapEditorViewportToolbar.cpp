// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SuperAlchemistEditor.h"
#include "VoxelMapEditor/SVoxelMapEditorViewportToolbar.h"
#include "VoxelMapEditor/VoxelMapEditorCommands.h"
#include "SEditorViewport.h"

#define LOCTEXT_NAMESPACE "SVoxelMapEditorViewportToolbar"

///////////////////////////////////////////////////////////
// SVoxelMapEditorViewportToolbar

void SVoxelMapEditorViewportToolbar::Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider)
{
	SCommonEditorViewportToolbarBase::Construct(SCommonEditorViewportToolbarBase::FArguments(), InInfoProvider);
}

TSharedRef<SWidget> SVoxelMapEditorViewportToolbar::GenerateShowMenu() const
{
	GetInfoProvider().OnFloatingButtonClicked();

	TSharedRef<SEditorViewport> ViewportRef = GetInfoProvider().GetViewportWidget();

	const bool bInShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder ShowMenuBuilder(bInShouldCloseWindowAfterMenuSelection, ViewportRef->GetCommandList());
	{
		ShowMenuBuilder.AddMenuEntry(FVoxelMapEditorCommands::Get().SetShowGrid);
		ShowMenuBuilder.AddMenuEntry(FVoxelMapEditorCommands::Get().SetShowMeshEdges);
	}

	return ShowMenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
