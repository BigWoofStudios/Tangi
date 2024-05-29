// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;

public class Tangi : ModuleRules
{
	public Tangi(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			// Core
			"Core", "CoreUObject", "Engine",
			// Input
			"InputCore", "EnhancedInput", 
			// Networking
			"NetCore", 
			// GAS
			"GameplayAbilities",
			// Animation
			"MotionWarping", "MotionTrajectory"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayTags", "GameplayTasks", "Niagara"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
