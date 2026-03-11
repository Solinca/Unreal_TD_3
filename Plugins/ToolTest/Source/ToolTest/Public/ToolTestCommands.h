// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "ToolTestStyle.h"

class FToolTestCommands : public TCommands<FToolTestCommands>
{
public:

	FToolTestCommands()
		: TCommands<FToolTestCommands>(TEXT("ToolTest"), NSLOCTEXT("Contexts", "ToolTest", "ToolTest Plugin"), NAME_None, FToolTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
