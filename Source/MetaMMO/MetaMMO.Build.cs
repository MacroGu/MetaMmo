// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MetaMMO : ModuleRules
{
	public MetaMMO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            OptimizeCode = CodeOptimization.Never;
        }

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore"});

        PublicIncludePaths.AddRange(
            new string[]
            {
                "MetaMMO"
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "KBEnginePlugins"
        });

    }
}
