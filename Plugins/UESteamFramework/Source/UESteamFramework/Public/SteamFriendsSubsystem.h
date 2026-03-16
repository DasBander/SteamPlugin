// Copyright Marc Fraedrich. All Rights Reserved.
// SteamFriendsSubsystem.h
// Friends list, overlay control, and rich-presence reads.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamTypes.h"
#include "Engine/Texture2D.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(push)
#pragma warning(disable : 4996 4265 4828)
#include "steam/steam_api.h"
#pragma warning(pop)
THIRD_PARTY_INCLUDES_END

#include "SteamFriendsSubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamFriendsOnPersonaStateChanged, FSteamID, SteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamFriendsOnAvatarLoaded,         FSteamID, SteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamFriendsOnGameInviteReceived,   FSteamID, InviterSteamID);

/**
 * USteamFriendsSubsystem
 *
 * Provides access to the Steam Friends List, avatar textures, the Steam
 * overlay, and game-invite functionality.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamFriendsSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamFriendsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Friends list
	// -----------------------------------------------------------------------

	/**
	 * Returns all immediate friends (accepted friend relationships).
	 * @param bOnlineOnly  When true only Online / Busy / Away / Snooze users are returned.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends")
	TArray<FSteamFriend> GetFriendsList(bool bOnlineOnly = false) const;

	/** Returns info for a single Steam user. */
	UFUNCTION(BlueprintPure, Category = "Steam|Friends")
	FSteamFriend GetFriendInfo(FSteamID SteamID) const;

	/** Returns the persona name for any Steam user (local or remote). */
	UFUNCTION(BlueprintPure, Category = "Steam|Friends")
	FString GetPersonaName(FSteamID SteamID) const;

	/** Returns the online state of any Steam user. */
	UFUNCTION(BlueprintPure, Category = "Steam|Friends")
	ESteamPersonaState GetPersonaState(FSteamID SteamID) const;

	/** True if the local user has the given ID as a friend. */
	UFUNCTION(BlueprintPure, Category = "Steam|Friends")
	bool HasFriend(FSteamID SteamID) const;

	/**
	 * Returns an avatar texture for any Steam user.
	 * The texture is transient — create a material or widget to display it.
	 * @param bLarge   True = 184x184, False = 64x64.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends")
	UTexture2D* GetFriendAvatar(FSteamID SteamID, bool bLarge = true) const;

	// -----------------------------------------------------------------------
	// Steam Overlay
	// -----------------------------------------------------------------------

	/**
	 * Opens the Steam overlay dialog.
	 * @param Dialog  "friends", "community", "players", "settings",
	 *                "officialgamegroup", "stats", "achievements"
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|Overlay")
	void ActivateOverlay(const FString& Dialog) const;

	/**
	 * Opens the Steam overlay to a specific user.
	 * @param Dialog  "steamid", "chat", "jointrade", "stats", "achievements",
	 *                "friendadd", "friendremove", "friendrequestaccept", "friendrequestignore"
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|Overlay")
	void ActivateOverlayToUser(const FString& Dialog, FSteamID SteamID) const;

	/** Opens the Steam overlay browser to the given URL. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|Overlay")
	void ActivateOverlayToWebPage(const FString& URL) const;

	/**
	 * Opens the Steam overlay to the app's store page.
	 * @param AppID  0 = current app.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|Overlay")
	void ActivateOverlayToStore(int32 AppID = 0) const;

	// -----------------------------------------------------------------------
	// Game invites
	// -----------------------------------------------------------------------

	/**
	 * Invites a friend to the current lobby / game session.
	 * @param ConnectString  Connection string passed to the invited player (e.g. "+connect ip:port").
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|Invites")
	bool InviteFriendToGame(FSteamID FriendSteamID, const FString& ConnectString) const;

	// -----------------------------------------------------------------------
	// Rich Presence (read side)
	// -----------------------------------------------------------------------

	/** Requests updated persona data for a user (triggers OnPersonaStateChanged when done). */
	UFUNCTION(BlueprintCallable, Category = "Steam|Friends|RichPresence")
	void RequestPersonaData(FSteamID SteamID);

	/** Returns a rich-presence value for any friend. */
	UFUNCTION(BlueprintPure, Category = "Steam|Friends|RichPresence")
	FString GetFriendRichPresenceValue(FSteamID SteamID, const FString& Key) const;

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	/** Fires whenever a friend's persona state (name, status, avatar) changes. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Friends|Callbacks")
	FSteamFriendsOnPersonaStateChanged OnPersonaStateChanged;

	/** Fires when a friend avatar is loaded (you can now call GetFriendAvatar). */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Friends|Callbacks")
	FSteamFriendsOnAvatarLoaded OnAvatarLoaded;

	/** Fires when another user sends a game invite to the local player. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Friends|Callbacks")
	FSteamFriendsOnGameInviteReceived OnGameInviteReceived;

private:
	STEAM_CALLBACK(USteamFriendsSubsystem, HandlePersonaStateChange,  PersonaStateChange_t);
	STEAM_CALLBACK(USteamFriendsSubsystem, HandleAvatarImageLoaded,   AvatarImageLoaded_t);
	STEAM_CALLBACK(USteamFriendsSubsystem, HandleGameRichPresenceJoin, GameRichPresenceJoinRequested_t);
};
