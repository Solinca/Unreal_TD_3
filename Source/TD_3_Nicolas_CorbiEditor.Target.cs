// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TD_3_Nicolas_CorbiEditorTarget : TargetRules
{
	public TD_3_Nicolas_CorbiEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "TD_3_Nicolas_Corbi" } );
	}
}
