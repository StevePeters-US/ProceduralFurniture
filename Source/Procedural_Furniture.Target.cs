// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Procedural_FurnitureTarget : TargetRules
{
	public Procedural_FurnitureTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Procedural_Furniture" } );
        
        bUseUnityBuild = false;
        bUsePCHFiles = false;
    }
}
