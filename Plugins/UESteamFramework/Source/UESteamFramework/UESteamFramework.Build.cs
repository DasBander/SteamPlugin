// Copyright Marc Fraedrich. All Rights Reserved.

using UnrealBuildTool;

public class UESteamFramework : ModuleRules
{
	public UESteamFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"Steamworks",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"DeveloperSettings",
		});

		// Steamworks SDK include paths are managed by the Steamworks module.
		// Adding it as a private static dependency makes the SDK headers available.
		AddEngineThirdPartyPrivateStaticDependencies(Target, "Steamworks");

		DynamicallyLoadedModuleNames.AddRange(new string[]
		{
			"OnlineSubsystemSteam",
		});
	}
}
