// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UESteamFramework : ModuleRules
{
	public UESteamFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"UESteamFramework/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"UESteamFramework/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "OnlineSubsystem",
                "OnlineSubsystemUtils",
                "UMG",
                "Steamworks",
                "Engine"
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Json",
                "JsonUtilities",
                "OnlineSubsystem",
                "OnlineSubsystemUtils"
				// ... add private dependencies that you statically link with here ...	
			}
            );



        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
                "OnlineSubsystemSteam",
                "OnlineSubsystemNull"
            }
			);
	}
}
