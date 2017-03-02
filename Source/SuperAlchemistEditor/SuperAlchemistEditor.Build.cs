using UnrealBuildTool;

public class SuperAlchemistEditor : ModuleRules
{
	public SuperAlchemistEditor(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		// For editing
		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"UnrealEd", 
			"PropertyEditor",
			"RenderCore",
			"ContentBrowser",
			"WorkspaceMenuStructure",
			"EditorStyle",
			"MeshPaint",
			"EditorWidgets",
            "KismetWidgets"
        });

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "Settings",
                "AssetTools",
                "LevelEditor"
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "AssetTools"
            }
        );

    }
}
