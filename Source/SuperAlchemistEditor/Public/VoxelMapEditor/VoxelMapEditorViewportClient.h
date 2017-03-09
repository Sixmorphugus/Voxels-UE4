// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "PreviewScene.h"
#include "AssetData.h"
#include "VoxelMapEditor/VoxelMapEditor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"

//////////////////////////////////////////////////////////////////////////
// FRelatedVoxelMap

struct FRelatedVoxelMap
{
	FAssetData AssetData;
	FVector2D SourceUV;
	FVector2D SourceDimension;
};

//////////////////////////////////////////////////////////////////////////
// FVoxelMapEditorViewportClient
// Controls how the viewport behaves and can be used in the Voxel Map Editor

class FVoxelMapEditorViewportClient : public FEditorViewportClient
{
public:
	/** Constructor */
	FVoxelMapEditorViewportClient(TWeakPtr<FVoxelMapEditor> InVoxelMapEditor, TWeakPtr<class SEditorViewport> InVoxelMapEditorViewportPtr);

	// FViewportClient interface
	virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
	virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;
	virtual void Tick(float DeltaSeconds) override;
	// End of FViewportClient interface

	// FEditorViewportClient interface
	virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad) override;
	virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;
	virtual void TrackingStopped() override;
	virtual FLinearColor GetBackgroundColor() const override;
	// End of FEditorViewportClient interface

	void ToggleShowMeshEdges();
	bool IsShowMeshEdgesChecked() const;

	void EnterViewMode() { InternalActivateNewMode(EVoxelMapEditorMode::ViewMode); }
	void EnterEditMode() { InternalActivateNewMode(EVoxelMapEditorMode::EditMode); }
	void EnterPlaceMode() { InternalActivateNewMode(EVoxelMapEditorMode::PlaceMode); }

	bool IsInViewMode() const { return CurrentMode == EVoxelMapEditorMode::ViewMode; }
	bool IsInEditMode() const { return CurrentMode == EVoxelMapEditorMode::EditMode; }
	bool IsInPlaceMode() const { return CurrentMode == EVoxelMapEditorMode::PlaceMode; }

	void ToggleShowVoxelMapNames();
	bool IsShowVoxelMapNamesChecked() const { return bShowNamesForVoxelMaps; }

	// Invalidate any references to the VoxelMap being edited; it has changed
	void NotifyVoxelMapBeingEditedHasChanged();
	void InvalidateViewportAndHitProxies();

	virtual FBox GetDesiredFocusBounds() const;

	UVoxelMap* CreateNewVoxelMap(const FIntPoint& Dimensions);

	EVoxelMapEditorMode::Type GetCurrentMode() const
	{
		return CurrentMode;
	}

private:
	// Editor mode
	EVoxelMapEditorMode::Type CurrentMode;

	// The preview scene
	FPreviewScene OwnedPreviewScene;

	// VoxelMap editor that owns this viewport
	TWeakPtr<FVoxelMapEditor> VoxelMapEditorPtr;

	// Render component for the VoxelMap being edited
	class AVoxelMapActor* RenderVoxelMap;

	// Widget mode
	// 	FWidget::EWidgetMode DesiredWidgetMode;

	// Are we currently manipulating something?
	bool bManipulating;

	// Did we dirty something during manipulation?
	bool bManipulationDirtiedSomething;

	// Pointer back to the VoxelMap editor viewport control that owns us
	TWeakPtr<class SEditorViewport> VoxelMapEditorViewportPtr;

	// The current transaction for undo/redo
	class FScopedTransaction* ScopedTransaction;

	// Should we show related VoxelMaps in the source texture?
	bool bShowRelatedVoxelMaps;

	// Should we show names for VoxelMaps in the source region edit mode?
	bool bShowNamesForVoxelMaps;

	// Other VoxelMaps that share the same source texture
	TArray<FRelatedVoxelMap> RelatedVoxelMaps;

private:
	UVoxelMap* GetVoxelMapBeingEdited() const
	{
		return VoxelMapEditorPtr.Pin()->GetVoxelMapBeingEdited();
	}

	// Activates a new mode, clearing selection set, etc...
	void InternalActivateNewMode(EVoxelMapEditorMode::Type NewMode);
};