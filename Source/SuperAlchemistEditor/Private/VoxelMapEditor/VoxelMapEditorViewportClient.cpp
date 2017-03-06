//

#include "SuperAlchemistEditor.h"
#include "VoxelMapEditor/VoxelMapEditorViewportClient.h"

#include "Modules/ModuleManager.h"
#include "CanvasItem.h"
#include "Utils.h"
#include "AssetEditorModeManager.h"
#include "ScopedTransaction.h"

#include "ComponentReregisterContext.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "ARFilter.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "AssetRegistryModule.h"
#include "CanvasTypes.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#include "VoxelMap.h"
#include "VoxelMapFactory.h"

#define LOCTEXT_NAMESPACE "VoxelMapEditor"

//////////////////////////////////////////////////////////////////////////
// FVoxelMapEditorViewportClient

FVoxelMapEditorViewportClient::FVoxelMapEditorViewportClient(TWeakPtr<FVoxelMapEditor> InVoxelMapEditor, TWeakPtr<class SEditorViewport> InVoxelMapEditorViewportPtr)
	: CurrentMode(EVoxelMapEditorMode::ViewMode)
	, VoxelMapEditorPtr(InVoxelMapEditor)
	, VoxelMapEditorViewportPtr(InVoxelMapEditorViewportPtr)
	, FEditorViewportClient(new FAssetEditorModeManager(), nullptr, nullptr)
{
	check(VoxelMapEditorPtr.IsValid() && VoxelMapEditorViewportPtr.IsValid());

	// Paper2D does this so I'm doing it too don't judge me
	Widget->SetUsesEditorModeTools(ModeTools);

	PreviewScene = &OwnedPreviewScene;
	((FAssetEditorModeManager*)ModeTools)->SetPreviewScene(PreviewScene);

	SetRealtime(true);

	bManipulating = false;
	bManipulationDirtiedSomething = false;
	ScopedTransaction = nullptr;

	bShowRelatedVoxelMaps = true;
	bShowNamesForVoxelMaps = true;

	DrawHelper.bDrawGrid = true; //GetDefault<UVoxelMapEditorSettings>()->bShowGridByDefault;

	EngineShowFlags.DisableAdvancedFeatures();
	EngineShowFlags.SetCompositeEditorPrimitives(true);

	// Create a render component for the VoxelMap being edited
	{
		RenderVoxelMapComponent = NewObject<UVoxelMapComponent>();
		UVoxelMap* VoxelMap = GetVoxelMapBeingEdited();
		RenderVoxelMapComponent->SetVoxelMap(VoxelMap);

		PreviewScene->AddComponent(RenderVoxelMapComponent, FTransform::Identity);
	}
}

void FVoxelMapEditorViewportClient::DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas)
{
	const bool bIsHitTesting = Canvas.IsHitTesting();
	if (!bIsHitTesting)
	{
		Canvas.SetHitProxy(nullptr);
	}

	if (!VoxelMapEditorPtr.IsValid())
	{
		return;
	}

	UVoxelMap* VoxelMap = GetVoxelMapBeingEdited();

	int32 YPos = 42;

	static const FText SourceRegionHelpStr = LOCTEXT("SourceRegionHelp", "Drag handles to adjust source region\nDouble-click on an image region to select all connected pixels (Ctrl creates a new VoxelMap)\nHold down Ctrl and drag a rectangle to create a new VoxelMap at that position\nClick on other VoxelMap rectangles to change the active VoxelMap");

	switch (CurrentMode)
	{
	case EVoxelMapEditorMode::ViewMode:
	default:
	{
		
	}
	break;

	case EVoxelMapEditorMode::PlaceMode:
	{
		
	}
	break;

	case EVoxelMapEditorMode::EditMode:
	{
		
	}
	break;

	}

	FEditorViewportClient::DrawCanvas(InViewport, View, Canvas);
}

void FVoxelMapEditorViewportClient::Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	FEditorViewportClient::Draw(View, PDI);
}

void FVoxelMapEditorViewportClient::ToggleShowVoxelMapNames()
{
	bShowNamesForVoxelMaps = !bShowNamesForVoxelMaps;
	Invalidate();
}

FBox FVoxelMapEditorViewportClient::GetDesiredFocusBounds() const
{
	UVoxelMapComponent* ComponentToFocusOn = RenderVoxelMapComponent;
	return ComponentToFocusOn->Bounds.GetBox();
}

UVoxelMap* FVoxelMapEditorViewportClient::CreateNewVoxelMap(const FIntPoint & Dimensions)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	UVoxelMap* CurrentVoxelMap = GetVoxelMapBeingEdited();
	UVoxelMap* CreatedVoxelMap = nullptr;

	// Create the factory used to generate the VoxelMap
	UVoxelMapFactory* VoxelMapFactory = NewObject<UVoxelMapFactory>();

	// Get a unique name for the VoxelMap
	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(CurrentVoxelMap->GetOutermost()->GetName(), TEXT(""), /*out*/ PackageName, /*out*/ Name);
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
	if (UObject* NewAsset = AssetToolsModule.Get().CreateAsset(Name, PackagePath, UVoxelMap::StaticClass(), VoxelMapFactory))
	{
		TArray<UObject*> Objects;
		Objects.Add(NewAsset);
		ContentBrowserModule.Get().SyncBrowserToAssets(Objects);

		UVoxelMap* NewVoxelMap = Cast<UVoxelMap>(NewAsset);
		if (VoxelMapEditorPtr.IsValid() && (NewVoxelMap != nullptr))
		{
			VoxelMapEditorPtr.Pin()->SetVoxelMapBeingEdited(NewVoxelMap);
		}

		CreatedVoxelMap = NewVoxelMap;
	}

	return CreatedVoxelMap;
}

void FVoxelMapEditorViewportClient::InternalActivateNewMode(EVoxelMapEditorMode::Type NewMode)
{
	CurrentMode = NewMode;
	Viewport->InvalidateHitProxy();

	UVoxelMap* Sprite = GetVoxelMapBeingEdited();

	switch (CurrentMode)
	{
	default:
	case EVoxelMapEditorMode::ViewMode:
		break;
	case EVoxelMapEditorMode::PlaceMode:
		break;
	case EVoxelMapEditorMode::EditMode:
		break;
	}
}

void FVoxelMapEditorViewportClient::Tick(float DeltaSeconds)
{
	if (UVoxelMap* VoxelMap = GetVoxelMapBeingEdited())
	{
		// ...
	}

	FEditorViewportClient::Tick(DeltaSeconds);

	if (!GIntraFrameDebuggingGameThread)
	{
		OwnedPreviewScene.GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
	}
}

void FVoxelMapEditorViewportClient::ToggleShowMeshEdges()
{
	EngineShowFlags.SetMeshEdges(!EngineShowFlags.MeshEdges);
	Invalidate();
}

bool FVoxelMapEditorViewportClient::IsShowMeshEdgesChecked() const
{
	return EngineShowFlags.MeshEdges;
}

void FVoxelMapEditorViewportClient::ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY)
{
	const FViewportClick Click(&View, this, Key, Event, HitX, HitY);
	const bool bIsCtrlKeyDown = Viewport->KeyState(EKeys::LeftControl) || Viewport->KeyState(EKeys::RightControl);
	const bool bIsShiftKeyDown = Viewport->KeyState(EKeys::LeftShift) || Viewport->KeyState(EKeys::RightShift);
	const bool bIsAltKeyDown = Viewport->KeyState(EKeys::LeftAlt) || Viewport->KeyState(EKeys::RightAlt);
	bool bHandled = false;

	if (IsInPlaceMode())
	{
		UVoxelMap* VoxelMap = GetVoxelMapBeingEdited();

		if ((Event == EInputEvent::IE_Pressed) && (Key == EKeys::LeftMouseButton))
		{
			FVector4 WorldPoint = View.PixelToWorld(HitX, HitY, 0);
			
			// Place a voxel


			bHandled = true;
		}
		else if ((Event == EInputEvent::IE_Pressed) && (Key == EKeys::RightMouseButton))
		{
			FVector4 WorldPoint = View.PixelToWorld(HitX, HitY, 0);

			// Remove a voxel


			bHandled = true;
		}
	}
	else if (IsInEditMode()) {
		// not sure how this works yet
	}

	if (!bHandled)
	{
		FEditorViewportClient::ProcessClick(View, HitProxy, Key, Event, HitX, HitY);
	}
}

bool FVoxelMapEditorViewportClient::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
{
	bool bHandled = false;
	FInputEventState InputState(InViewport, Key, Event);

	// Handle marquee tracking in source region edit mode
	

	// Pass keys to standard controls, if we didn't consume input
	return (bHandled) ? true : FEditorViewportClient::InputKey(InViewport, ControllerId, Key, Event, AmountDepressed, bGamepad);
}

void FVoxelMapEditorViewportClient::TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge)
{
	// I think this is for if the user is dragging the mouse around.
	// we don't need it for the moment so it's blank
}

void FVoxelMapEditorViewportClient::TrackingStopped()
{
	// ^
	// |
}

FLinearColor FVoxelMapEditorViewportClient::GetBackgroundColor() const
{
	return FColor(150, 150, 150); //GetDefault<UVoxelMapEditorSettings>()->BackgroundColor;
}

void FVoxelMapEditorViewportClient::InvalidateViewportAndHitProxies()
{
	Viewport->Invalidate();
}

void FVoxelMapEditorViewportClient::NotifyVoxelMapBeingEditedHasChanged()
{
	// Refresh the viewport in case we were not in realtime mode
	Invalidate();

	// Update components to know about the new VoxelMap being edited
	UVoxelMap* VoxelMap = GetVoxelMapBeingEdited();

	RenderVoxelMapComponent->SetVoxelMap(VoxelMap);
	InternalActivateNewMode(CurrentMode);

	if (VoxelMap != nullptr)
	{
		// Create and display a notification about the new VoxelMap being edited
		const FText NotificationErrorText = FText::Format(LOCTEXT("SwitchingToVoxelMap", "Editing {0}"), FText::AsCultureInvariant(VoxelMap->GetName()));
		FNotificationInfo Info(NotificationErrorText);
		Info.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
}