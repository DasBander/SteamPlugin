/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/
#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "steamsdk_lambda_callresults.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSteamFramework, Log, All);

class FUESteamFrameworkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};