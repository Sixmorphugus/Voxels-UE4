#include "SuperAlchemistEditor.h"
#include "VoxelMapEditor.h"

#include "VoxelMap.h"

#include "Framework/MultiBox/MultiBoxDefs.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorViewportClient.h"
#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "SSingleObjectDetailsPanel.h"

#include "SEditorViewport.h"
#include "VoxelMapEditor/VoxelMapEditorViewportClient.h"
#include "VoxelMapEditor/VoxelMapEditorCommands.h"
#include "VoxelMapEditor/SVoxelMapEditorViewportToolbar.h"
#include "SCommonEditorViewportToolbarBase.h"

#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "VoxelMapEditor"

namespace FVoxelMapEditorTabs
{
	// Tab identifiers
	const FName DetailsID = FName(TEXT("Details"));
	const FName ViewportID = FName(TEXT("Viewport"));
	//const FName VoxelMapsListID = FName(TEXT("Voxel Maps"));
}

const FName VoxelMapEditorAppName = FName(TEXT("VoxelMapEditorApp"));

//////////////////////////////////////////////////////////////////////////
// SVoxelMapEditorViewport

class SVoxelMapEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(SVoxelMapEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedPtr<FVoxelMapEditor> InVoxelMapEditor);

	// SEditorViewport interface
	virtual void BindCommands() override;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	virtual EVisibility GetTransformToolbarVisibility() const override;
	virtual void OnFocusViewportToSelection() override;
	// End of SEditorViewport interface

	// ICommonEditorViewportToolbarInfoProvider interface
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	// End of ICommonEditorViewportToolbarInfoProvider interface

	// Invalidate any references to the VoxelMap being edited; it has changed
	void NotifyVoxelMapBeingEditedHasChanged()
	{
		EditorViewportClient->NotifyVoxelMapBeingEditedHasChanged();
	}

	EVoxelMapEditorMode::Type GetCurrentMode() const
	{
		return EditorViewportClient->GetCurrentMode();
	}

private:
	// Pointer back to owning VoxelMap editor instance (the keeper of state)
	TWeakPtr<class FVoxelMapEditor> VoxelMapEditorPtr;

	// Viewport client
	TSharedPtr<FVoxelMapEditorViewportClient> EditorViewportClient;
};

void SVoxelMapEditorViewport::Construct(const FArguments& InArgs, TSharedPtr<FVoxelMapEditor> InVoxelMapEditor)
{
	VoxelMapEditorPtr = InVoxelMapEditor;

	SEditorViewport::Construct(SEditorViewport::FArguments());
}

void SVoxelMapEditorViewport::BindCommands()
{
	SEditorViewport::BindCommands();

	const FVoxelMapEditorCommands& Commands = FVoxelMapEditorCommands::Get();

	TSharedRef<FVoxelMapEditorViewportClient> EditorViewportClientRef = EditorViewportClient.ToSharedRef();

	// Show toggles
	CommandList->MapAction(
		Commands.SetShowGrid,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FEditorViewportClient::SetShowGrid),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FEditorViewportClient::IsSetShowGridChecked));

	CommandList->MapAction(
		Commands.ToggleShowVoxelMapNames,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::ToggleShowVoxelMapNames),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsShowVoxelMapNamesChecked),
		FIsActionButtonVisible::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsInEditMode));

	CommandList->MapAction(
		Commands.SetShowMeshEdges,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::ToggleShowMeshEdges),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsShowMeshEdgesChecked));

	// Editing modes
	CommandList->MapAction(
		Commands.EnterViewMode,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::EnterViewMode),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsInViewMode));
	CommandList->MapAction(
		Commands.EnterPlaceMode,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::EnterPlaceMode),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsInPlaceMode));
	CommandList->MapAction(
		Commands.EnterEditMode,
		FExecuteAction::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::EnterEditMode),
		FCanExecuteAction(),
		FIsActionChecked::CreateSP(EditorViewportClientRef, &FVoxelMapEditorViewportClient::IsInEditMode));
}

TSharedRef<FEditorViewportClient> SVoxelMapEditorViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FVoxelMapEditorViewportClient(VoxelMapEditorPtr, SharedThis(this)));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SVoxelMapEditorViewport::MakeViewportToolbar()
{
	return SNew(SVoxelMapEditorViewportToolbar, SharedThis(this));
}

EVisibility SVoxelMapEditorViewport::GetTransformToolbarVisibility() const
{
	return EVisibility::Visible;
}

void SVoxelMapEditorViewport::OnFocusViewportToSelection()
{
	// ...
}

TSharedRef<class SEditorViewport> SVoxelMapEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> SVoxelMapEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void SVoxelMapEditorViewport::OnFloatingButtonClicked()
{
}

/////////////////////////////////////////////////////

FVoxelMapEditor::FVoxelMapEditor()
	: VoxelMapBeingEdited(nullptr)
{
}

TSharedRef<SDockTab> FVoxelMapEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("ViewportTab_Title", "Viewport"))
		[
			SNew(SOverlay)

			// The voxel editor viewport
			+ SOverlay::Slot()
			[
				ViewportPtr.ToSharedRef()
			]
		];
}

TSharedRef<SDockTab> FVoxelMapEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	TSharedPtr<FVoxelMapEditor> VMEditorPtr = SharedThis(this);

	// Spawn the tab
	return SNew(SDockTab)
		.Label(LOCTEXT("DetailsTab_Title", "Details"))
		[
			SNew(SSingleObjectDetailsPanel, true)
		];
}

/*
TSharedRef<SDockTab> FVoxelMapEditor::SpawnTab_MaterialsList(const FSpawnTabArgs& Args)
{
	// Spawn the tab
	return SNew(SDockTab)
		.Label(LOCTEXT("MaterialsListTab_Title", "Materials List"))
		[
			 TODO
		];
}
*/

void FVoxelMapEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SpriteEditor", "Sprite Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FVoxelMapEditorTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FVoxelMapEditor::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

	InTabManager->RegisterTabSpawner(FVoxelMapEditorTabs::DetailsID, FOnSpawnTab::CreateSP(this, &FVoxelMapEditor::SpawnTab_Details))
		.SetDisplayName(LOCTEXT("DetailsTabLabel", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	/*
	InTabManager->RegisterTabSpawner(FVoxelMapEditorTabs::MaterialsListID, FOnSpawnTab::CreateSP(this, &FVoxelMapEditor::SpawnTab_MaterialsList))
		.SetDisplayName(LOCTEXT("MaterialsListTabLabel", "Materials List"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.ContentBrowser"));
		*/
}

void FVoxelMapEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(FVoxelMapEditorTabs::ViewportID);
	InTabManager->UnregisterTabSpawner(FVoxelMapEditorTabs::DetailsID);
	//InTabManager->UnregisterTabSpawner(FVoxelMapEditorTabs::MaterialsListID);
}

FName FVoxelMapEditor::GetToolkitFName() const
{
	return FName("VoxelMapEditor");
}

FText FVoxelMapEditor::GetBaseToolkitName() const
{
	return LOCTEXT("VoxelMapEditorAppLabel", "Voxel Map Editor");
}

FText FVoxelMapEditor::GetToolkitName() const
{
	const bool bDirtyState = VoxelMapBeingEdited->GetOutermost()->IsDirty();

	FFormatNamedArguments Args;
	Args.Add(TEXT("VoxelMapName"), FText::FromString(VoxelMapBeingEdited->GetName()));
	Args.Add(TEXT("DirtyState"), bDirtyState ? FText::FromString(TEXT("*")) : FText::GetEmpty());
	return FText::Format(LOCTEXT("SpriteEditorToolkitName", "{SpriteName}{DirtyState}"), Args);
}

FText FVoxelMapEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(VoxelMapBeingEdited);
}

FString FVoxelMapEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("SpriteEditor");
}

FString FVoxelMapEditor::GetDocumentationLink() const
{
	return TEXT("");
}

void FVoxelMapEditor::OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit)
{
	//@TODO: MODETOOLS: Need to be able to register the widget in the toolbox panel with ToolkitHost, so it can instance the ed mode widgets into it
	// 	TSharedPtr<SWidget> InlineContent = Toolkit->GetInlineContent();
	// 	if (InlineContent.IsValid())
	// 	{
	// 		ToolboxPtr->SetContent(InlineContent.ToSharedRef());
	// 	}
}

void FVoxelMapEditor::OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit)
{
	//ToolboxPtr->SetContent(SNullWidget::NullWidget);
	//@TODO: MODETOOLS: How to handle multiple ed modes at once in a standalone asset editor?
}

FLinearColor FVoxelMapEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

void FVoxelMapEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(VoxelMapBeingEdited);
}

void FVoxelMapEditor::ExtendMenu()
{
	// no menu extensions
}

void FVoxelMapEditor::ExtendToolbar()
{
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			const FVoxelMapEditorCommands& VoxelMapCommands = FVoxelMapEditorCommands::Get();

			ToolbarBuilder.BeginSection("Command");
			{
				ToolbarBuilder.AddToolBarButton(VoxelMapCommands.ToggleShowVoxelMapNames);
			}
			ToolbarBuilder.EndSection();
		}
	};

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		ViewportPtr->GetCommandList(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar)
	);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		ViewportPtr->GetCommandList(),
		FToolBarExtensionDelegate::CreateSP(this, &FVoxelMapEditor::CreateModeToolbarWidgets));

	AddToolbarExtender(ToolbarExtender);
}

void FVoxelMapEditor::BindCommands()
{
	// no commands
}

void FVoxelMapEditor::SetVoxelMapBeingEdited(UVoxelMap* NewVM)
{
	if ((NewVM != VoxelMapBeingEdited) && (NewVM != nullptr))
	{
		UVoxelMap* OldMap = VoxelMapBeingEdited;
		VoxelMapBeingEdited = NewVM;

		// Let the viewport know that we are editing something different
		//ViewportPtr->NotifySpriteBeingEditedHasChanged();

		// Let the editor know that are editing something different
		RemoveEditingObject(OldMap);
		AddEditingObject(NewVM);
	}
}

void FVoxelMapEditor::CreateModeToolbarWidgets(FToolBarBuilder& IgnoredBuilder)
{

}

void FVoxelMapEditor::InitVoxelMapEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UVoxelMap* InitVM)
{
	VoxelMapBeingEdited = InitVM;

	BindCommands();

	TSharedPtr<FVoxelMapEditor> VoxelMapEditorPtr = SharedThis(this);
	ViewportPtr = SNew(SVoxelMapEditorViewport, VoxelMapEditorPtr);
	//MaterialsListPtr = SNew(SVoxelMapMaterialsList, VoxelMapEditorPtr);

	// Default layout
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_VoxelMapEditor_Layout_v6")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(FVoxelMapEditorTabs::ViewportID, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.75f)
						->SetHideTabWell(true)
						->AddTab(FVoxelMapEditorTabs::DetailsID, ETabState::OpenedTab)
					)
					/*
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.25f)
						->AddTab(FVoxelMapEditorTabs::MaterialsListID, ETabState::OpenedTab)
					)
					*/
				)
			)
		);

	// Initialize the asset editor
	InitAssetEditor(Mode, InitToolkitHost, VoxelMapEditorAppName, StandaloneDefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, InitVM);

	//ViewportPtr->ActivateEditMode();

	// Extend things
	ExtendMenu();
	ExtendToolbar();
	RegenerateMenusAndToolbars();
}