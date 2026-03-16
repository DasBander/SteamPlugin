// Copyright Marc Fraedrich. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SteamSettings.generated.h"

/**
 * Project-wide Steam Framework settings.
 * Accessible via Edit > Project Settings > Plugins > Steam Framework.
 * Values are saved to Config/DefaultGame.ini under [/Script/UESteamFramework.SteamSettings].
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Steam Framework"))
class UESTEAMFRAMEWORK_API USteamSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	USteamSettings();

	// -------------------------------------------------------------------
	// Core
	// -------------------------------------------------------------------

	/** Your Steam App ID.  480 = Spacewar (development/testing). */
	UPROPERTY(Config, EditAnywhere, Category = "Core",
		meta = (DisplayName = "App ID", ClampMin = "1"))
	int32 AppID = 480;

	/**
	 * When true the framework verifies at startup that the running App ID matches
	 * what Steam reports.  Disable during development if you are testing with
	 * a different App ID than the one set here.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Core",
		meta = (DisplayName = "Enforce App Ownership Check"))
	bool bEnforceOwnershipCheck = true;

	// -------------------------------------------------------------------
	// Dedicated Server (GameServer API)
	// -------------------------------------------------------------------

	/** Product name shown in server browser / backend. */
	UPROPERTY(Config, EditAnywhere, Category = "Dedicated Server",
		meta = (DisplayName = "Product Name"))
	FString ProductName = TEXT("MyGame");

	/** Game description shown in server browser. */
	UPROPERTY(Config, EditAnywhere, Category = "Dedicated Server",
		meta = (DisplayName = "Game Description"))
	FString GameDescription = TEXT("My Steam Game");

	/** Mod directory / game dir. */
	UPROPERTY(Config, EditAnywhere, Category = "Dedicated Server",
		meta = (DisplayName = "Game Directory"))
	FString GameDirectory = TEXT("mygame");

	/** Server version string sent to Steam. */
	UPROPERTY(Config, EditAnywhere, Category = "Dedicated Server",
		meta = (DisplayName = "Server Version"))
	FString ServerVersion = TEXT("1.0.0.0");

	// -------------------------------------------------------------------
	// UDeveloperSettings interface
	// -------------------------------------------------------------------
	virtual FName GetCategoryName() const override { return FName("Plugins"); }
};
