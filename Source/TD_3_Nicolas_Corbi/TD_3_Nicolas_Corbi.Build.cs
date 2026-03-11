using UnrealBuildTool;

public class TD_3_Nicolas_Corbi : ModuleRules
{
	public TD_3_Nicolas_Corbi(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemUtils", "NetCore", "Slate", "SlateCore", "UMG", "MyModule" });
	}
}
