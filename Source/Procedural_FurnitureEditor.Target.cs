// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Procedural_FurnitureEditorTarget : TargetRules
{
	public Procedural_FurnitureEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Procedural_Furniture" } );
	}
}
