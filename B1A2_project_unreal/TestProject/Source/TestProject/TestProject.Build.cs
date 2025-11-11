// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestProject : ModuleRules
{
	public TestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TestProject",
			"TestProject/Variant_Platforming",
			"TestProject/Variant_Platforming/Animation",
			"TestProject/Variant_Combat",
			"TestProject/Variant_Combat/AI",
			"TestProject/Variant_Combat/Animation",
			"TestProject/Variant_Combat/Gameplay",
			"TestProject/Variant_Combat/Interfaces",
			"TestProject/Variant_Combat/UI",
			"TestProject/Variant_SideScrolling",
			"TestProject/Variant_SideScrolling/AI",
			"TestProject/Variant_SideScrolling/Gameplay",
			"TestProject/Variant_SideScrolling/Interfaces",
			"TestProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
