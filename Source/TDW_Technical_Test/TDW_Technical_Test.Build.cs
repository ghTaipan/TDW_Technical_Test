// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDW_Technical_Test : ModuleRules
{
	public TDW_Technical_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "NavigationSystem",
	        "AIModule", 
	        "Niagara",
	        "EnhancedInput",
	        "GameplayAbilities",
	        "GameplayTasks",
	        "GameplayTags"
        });
	}
}
