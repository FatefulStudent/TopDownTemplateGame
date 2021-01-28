// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownTemplateGame : ModuleRules
{
	public TopDownTemplateGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
