// Copyright Marc Fraedrich. All Rights Reserved.
// SteamCoreSubsystem.h
// Handles Steam API init/shutdown, per-frame RunCallbacks, and queries about
// the local user (profile, app info, rich presence).
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "SteamTypes.h"
#include "Engine/Texture2D.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(push)
#pragma warning(disable : 4996 4265 4828)
#include "steam/steam_api.h"
#pragma warning(pop)
THIRD_PARTY_INCLUDES_END

#include "SteamCoreSubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSteamCoreOnSteamShutdown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamCoreOnGameOverlayActivated, bool, bActive);

/**
 * USteamCoreSubsystem
 *
 * Initialises the Steamworks API when the game instance starts and shuts it
 * down when the instance is destroyed.  Also drives SteamAPI_RunCallbacks()
 * once per frame so every other subsystem receives its callbacks.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamCoreSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamCoreSubsystem
	: public UGameInstanceSubsystem
	, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// -----------------------------------------------------------------------
	// UGameInstanceSubsystem interface
	// -----------------------------------------------------------------------
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// FTickableGameObject interface
	// -----------------------------------------------------------------------
	virtual void    Tick(float DeltaTime) override;
	virtual bool    IsTickable() const override;
	virtual TStatId GetStatId() const override;

	// -----------------------------------------------------------------------
	// Steam status
	// -----------------------------------------------------------------------

	/** True after SteamAPI_Init() succeeded. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	bool IsSteamInitialized() const { return bInitialized; }

	/** Returns the Steam App ID the game is running under. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	int32 GetAppID() const;

	/** Returns the Steam build ID (increments with each Steam build). */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	int32 GetBuildID() const;

	/** Returns the current Steam UI language (e.g. "english", "german"). */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	FString GetCurrentGameLanguage() const;

	/** Returns a comma-separated list of all available languages for this app. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	FString GetAvailableGameLanguages() const;

	/** True if the user owns the application. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	bool IsSubscribed() const;

	/** True if the user has a VAC ban. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core")
	bool IsVACBanned() const;

	// -----------------------------------------------------------------------
	// Local user
	// -----------------------------------------------------------------------

	/** Returns the local user's Steam ID. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core|User")
	FSteamID GetLocalUserSteamID() const;

	/** Returns the local user's display name. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core|User")
	FString GetLocalPersonaName() const;

	/**
	 * Retrieves the avatar texture for any Steam user.
	 * @param SteamID  Target user.  Pass GetLocalUserSteamID() for yourself.
	 * @param bLarge   True = 184x184, False = 64x64.
	 * @returns A transient UTexture2D or nullptr when not yet available.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Core|User")
	UTexture2D* GetAvatar(FSteamID SteamID, bool bLarge = true) const;

	// -----------------------------------------------------------------------
	// Rich Presence
	// -----------------------------------------------------------------------

	/**
	 * Sets a rich-presence key/value pair for the local user.
	 * Keys are limited to 64 characters; values to 256 characters.
	 * Passing an empty value removes the key.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Core|RichPresence")
	void SetRichPresence(const FString& Key, const FString& Value);

	/** Clears all rich-presence data for the local user. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Core|RichPresence")
	void ClearRichPresence();

	/** Returns the value of a rich-presence key for any user. */
	UFUNCTION(BlueprintPure, Category = "Steam|Core|RichPresence")
	FString GetFriendRichPresence(FSteamID SteamID, const FString& Key) const;

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	/** Fired when Steam requests the game to exit (e.g. user closes Steam). */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Core|Callbacks")
	FSteamCoreOnSteamShutdown OnSteamShutdown;

	/** Fired when the Steam overlay opens or closes. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Core|Callbacks")
	FSteamCoreOnGameOverlayActivated OnGameOverlayActivated;

private:
	bool bInitialized = false;

	// Steam callbacks
	STEAM_CALLBACK(USteamCoreSubsystem, HandleGameOverlayActivated, GameOverlayActivated_t);
	STEAM_CALLBACK(USteamCoreSubsystem, HandleSteamShutdown, SteamShutdown_t);
};
