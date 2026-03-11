// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolTest.h"
#include "ToolTestStyle.h"
#include "ToolTestCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ToolTestTabName("ToolTest");

#define LOCTEXT_NAMESPACE "FToolTestModule"

void FToolTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FToolTestStyle::Initialize();
	FToolTestStyle::ReloadTextures();

	FToolTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FToolTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FToolTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FToolTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ToolTestTabName, FOnSpawnTab::CreateRaw(this, &FToolTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FToolTestTabTitle", "ToolTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FToolTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FToolTestStyle::Shutdown();

	FToolTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ToolTestTabName);
}

TSharedRef<SDockTab> FToolTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FToolTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("ToolTest.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FToolTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ToolTestTabName);
}

void FToolTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FToolTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FToolTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolTestModule, ToolTest)
