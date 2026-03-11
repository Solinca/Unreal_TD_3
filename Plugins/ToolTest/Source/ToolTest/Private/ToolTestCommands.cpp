// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolTestCommands.h"

#define LOCTEXT_NAMESPACE "FToolTestModule"

void FToolTestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ToolTest", "Bring up ToolTest window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
