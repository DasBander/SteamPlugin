/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/

#include "SteamSettings.h"
#define LOCTEXT_NAMESPACE "SteamSettings"

USteamSettings::USteamSettings(const FObjectInitializer&)
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule)
	{
		SettingsModule->RegisterSettings("Project", "Project", "SteamSettings",LOCTEXT("SteamSettingsName", "Steam Framework Settings"),
			LOCTEXT("SteamSettingsDescription", "Steam Framework Settings, stored per-project"),
			GetMutableDefault<USteamSettings>());
	}
}


#undef LOCTEXT_NAMESPACE