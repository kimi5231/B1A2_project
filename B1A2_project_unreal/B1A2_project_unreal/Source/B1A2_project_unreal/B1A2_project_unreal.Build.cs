// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class B1A2_project_unreal : ModuleRules
{
	public B1A2_project_unreal(ReadOnlyTargetRules Target) : base(Target)
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
			"B1A2_project_unreal",
			"B1A2_project_unreal/Variant_Platforming",
			"B1A2_project_unreal/Variant_Platforming/Animation",
			"B1A2_project_unreal/Variant_Combat",
			"B1A2_project_unreal/Variant_Combat/AI",
			"B1A2_project_unreal/Variant_Combat/Animation",
			"B1A2_project_unreal/Variant_Combat/Gameplay",
			"B1A2_project_unreal/Variant_Combat/Interfaces",
			"B1A2_project_unreal/Variant_Combat/UI",
			"B1A2_project_unreal/Variant_SideScrolling",
			"B1A2_project_unreal/Variant_SideScrolling/AI",
			"B1A2_project_unreal/Variant_SideScrolling/Gameplay",
			"B1A2_project_unreal/Variant_SideScrolling/Interfaces",
			"B1A2_project_unreal/Variant_SideScrolling/UI"
		});

		// Winsock 라이브러리 추가
		PublicAdditionalLibraries.Add("ws2_32.lib");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
