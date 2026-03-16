// Copyright Marc Fraedrich. All Rights Reserved.

#include "UESteamFramework.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FUESteamFrameworkModule"

DEFINE_LOG_CATEGORY(LogSteamFramework);

void FUESteamFrameworkModule::StartupModule()
{
}

void FUESteamFrameworkModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUESteamFrameworkModule, UESteamFramework)
