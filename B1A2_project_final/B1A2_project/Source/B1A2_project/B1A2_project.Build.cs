// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class B1A2_project : ModuleRules
{
	public B1A2_project(ReadOnlyTargetRules Target) : base(Target)
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
			"B1A2_project",
			"B1A2_project/Variant_Platforming",
			"B1A2_project/Variant_Platforming/Animation",
			"B1A2_project/Variant_Combat",
			"B1A2_project/Variant_Combat/AI",
			"B1A2_project/Variant_Combat/Animation",
			"B1A2_project/Variant_Combat/Gameplay",
			"B1A2_project/Variant_Combat/Interfaces",
			"B1A2_project/Variant_Combat/UI",
			"B1A2_project/Variant_SideScrolling",
			"B1A2_project/Variant_SideScrolling/AI",
			"B1A2_project/Variant_SideScrolling/Gameplay",
			"B1A2_project/Variant_SideScrolling/Interfaces",
			"B1A2_project/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
