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
			"EditorWidgets"
		});
		
	}
}
