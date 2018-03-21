/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/
#pragma once

#include "CoreMinimal.h"
#include "UESteamFramework.h"
#include "UObject/NoExportTypes.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"




#include "SteamSettings.generated.h"


/**
 * 
 */
UCLASS(config = SteamFramework, defaultconfig, meta = (DisplayName = "Steam Framework"))
class UESTEAMFRAMEWORK_API USteamSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
		UPROPERTY(config, EditAnywhere, Category = "Steam | Core")
		FString AppID;

		UPROPERTY(config, EditAnywhere, Category = "Steam | Dedicated Server")
			FString ProductID;

		UPROPERTY(config, EditAnywhere, Category = "Steam | Dedicated Server")
			FString SteamVersion;
		
		UPROPERTY(config, EditAnywhere, Category = "Steam | Product Protection")
			bool EnableProductProtection;
	
};
