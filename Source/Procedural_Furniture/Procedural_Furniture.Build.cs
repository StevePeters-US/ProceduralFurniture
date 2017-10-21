// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Procedural_Furniture : ModuleRules
{
	public Procedural_Furniture(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        //PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI", "RuntimeMeshComponent", "ProceduralMeshComponent" });
        PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI", "RuntimeMeshComponent", "ProceduralMeshComponent" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
