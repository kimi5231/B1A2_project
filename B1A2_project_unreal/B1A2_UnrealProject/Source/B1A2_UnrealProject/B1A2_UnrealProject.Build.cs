// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class B1A2_UnrealProject : ModuleRules
{
	public B1A2_UnrealProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"OpenCVHelper",
			"OpenCV",
			"NavigationSystem",
			"NavMesh",
			"AudioCapture",
			"AudioCaptureCore",
			"AudioMixer",
			"Voice",
			"SignalProcessing",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"B1A2_UnrealProject",
			"B1A2_UnrealProject/Variant_Platforming",
			"B1A2_UnrealProject/Variant_Platforming/Animation",
			"B1A2_UnrealProject/Variant_Combat",
			"B1A2_UnrealProject/Variant_Combat/AI",
			"B1A2_UnrealProject/Variant_Combat/Animation",
			"B1A2_UnrealProject/Variant_Combat/Gameplay",
			"B1A2_UnrealProject/Variant_Combat/Interfaces",
			"B1A2_UnrealProject/Variant_Combat/UI",
			"B1A2_UnrealProject/Variant_SideScrolling",
			"B1A2_UnrealProject/Variant_SideScrolling/AI",
			"B1A2_UnrealProject/Variant_SideScrolling/Gameplay",
			"B1A2_UnrealProject/Variant_SideScrolling/Interfaces",
			"B1A2_UnrealProject/Variant_SideScrolling/UI"
		});

        PublicAdditionalLibraries.Add("Ws2_32.lib");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
