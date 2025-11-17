// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TD_3_Nicolas_CorbiTarget : TargetRules
{
	public TD_3_Nicolas_CorbiTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "TD_3_Nicolas_Corbi" } );
	}
}
