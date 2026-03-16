// Copyright Marc Fraedrich. All Rights Reserved.
// SteamLobbySubsystem.h
// Full lobby lifecycle: create, join, leave, search, metadata, members, chat, invites.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamTypes.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(push)
#pragma warning(disable : 4996 4265 4828)
#include "steam/steam_api.h"
#pragma warning(pop)
THIRD_PARTY_INCLUDES_END

#include "SteamLobbySubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnCreated,       FLobbyCreateResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnEntered,       FSteamID,           LobbyID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSteamLobbyOnLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSteamLobbyOnDataUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnMemberJoined,  FSteamID, MemberSteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnMemberLeft,    FSteamID, MemberSteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamLobbyOnChatMessage,  FSteamID, SenderSteamID, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnInviteReceived, FSteamID, InviterSteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamLobbyOnSearchComplete, TArray<FLobbySearchResult>, Results);

/**
 * USteamLobbySubsystem
 *
 * Manages the full lobby lifecycle through the Steam Matchmaking API.
 * Supports lobby creation, joining, leaving, searching, metadata, member lists,
 * chat, and friend invites.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamLobbySubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamLobbySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Current lobby state
	// -----------------------------------------------------------------------

	/** True when the local player is inside a lobby. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby")
	bool IsInLobby() const { return bIsInLobby; }

	/** Returns the Steam ID of the current lobby, or an invalid ID. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby")
	FSteamID GetCurrentLobbyID() const { return CurrentLobbyID; }

	// -----------------------------------------------------------------------
	// Lobby lifecycle
	// -----------------------------------------------------------------------

	/**
	 * Creates a new lobby.  Results are delivered via OnLobbyCreated.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
	void CreateLobby(FLobbyCreateParams Params);

	/**
	 * Joins an existing lobby by its Steam ID.  Results via OnLobbyEntered.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
	void JoinLobby(FSteamID LobbyID);

	/**
	 * Leaves the current lobby and clears local state.
	 * Fires OnLobbyLeft immediately (no async wait).
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
	void LeaveLobby();

	// -----------------------------------------------------------------------
	// Lobby search
	// -----------------------------------------------------------------------

	/** Adds a string filter before calling RequestLobbyList(). */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void AddStringFilter(const FString& Key, const FString& Value, ELobbyComparison Comparison);

	/** Adds a numeric filter before calling RequestLobbyList(). */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void AddNumericalFilter(const FString& Key, int32 Value, ELobbyComparison Comparison);

	/** Limits results to lobbies with at least this many open slots. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void AddSlotsAvailableFilter(int32 MinOpenSlots);

	/** Sets the distance filter for lobby searches. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void SetDistanceFilter(ELobbyDistanceFilter Filter);

	/** Caps the number of lobbies returned (default = 50). */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void SetResultCountLimit(int32 Max);

	/**
	 * Requests a lobby list using any previously-added filters.
	 * Results are delivered via OnSearchComplete.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Search")
	void RequestLobbyList();

	// -----------------------------------------------------------------------
	// Lobby metadata
	// -----------------------------------------------------------------------

	/** Returns a metadata string for the current lobby. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby|Metadata")
	FString GetLobbyData(const FString& Key) const;

	/** Sets a metadata string on the current lobby (owner only). */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Metadata")
	bool SetLobbyData(const FString& Key, const FString& Value);

	/** Returns a per-member metadata string. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby|Metadata")
	FString GetMemberData(FSteamID MemberSteamID, const FString& Key) const;

	/** Sets per-member metadata for the local user. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Metadata")
	void SetMemberData(const FString& Key, const FString& Value);

	// -----------------------------------------------------------------------
	// Members
	// -----------------------------------------------------------------------

	/** Returns all members currently in the lobby. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Members")
	TArray<FSteamFriend> GetMembers() const;

	/** Returns the number of members currently in the lobby. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby|Members")
	int32 GetMemberCount() const;

	/** Returns the Steam ID of the lobby owner. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby|Members")
	FSteamID GetOwner() const;

	/** True if the local player is the lobby owner. */
	UFUNCTION(BlueprintPure, Category = "Steam|Lobby|Members")
	bool IsOwner() const;

	// -----------------------------------------------------------------------
	// Settings (owner only)
	// -----------------------------------------------------------------------

	/** Changes the lobby visibility. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Settings")
	bool SetLobbyVisibility(ELobbyVisibility Visibility);

	/** Sets whether the lobby can be joined.  Pass false to lock the lobby. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Settings")
	bool SetJoinable(bool bJoinable);

	/** Changes the maximum number of players. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Settings")
	bool SetMemberLimit(int32 MaxMembers);

	// -----------------------------------------------------------------------
	// Chat
	// -----------------------------------------------------------------------

	/** Sends a UTF-8 text message to everyone in the lobby. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Chat")
	bool SendChatMessage(const FString& Message);

	// -----------------------------------------------------------------------
	// Invites
	// -----------------------------------------------------------------------

	/** Invites a Steam friend to join this lobby. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby|Invites")
	bool InviteFriend(FSteamID FriendSteamID);

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnCreated OnLobbyCreated;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnEntered OnLobbyEntered;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnLeft OnLobbyLeft;

	/** Fires when lobby metadata or member data changes. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnDataUpdated OnLobbyDataUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnMemberJoined OnMemberJoined;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnMemberLeft OnMemberLeft;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnChatMessage OnChatMessageReceived;

	/** Fires when someone invites the local player to a lobby. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnInviteReceived OnInviteReceived;

	/** Fires when a RequestLobbyList() search completes. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FSteamLobbyOnSearchComplete OnSearchComplete;

private:
	bool     bIsInLobby   = false;
	FSteamID CurrentLobbyID;

	/** Opaque pointers to TLambdaCallResult<> instances (defined in .cpp). */
	void* CallResult_LobbyCreated = nullptr;
	void* CallResult_LobbyEntered = nullptr;
	void* CallResult_LobbyList    = nullptr;

	// Steam callbacks — declared here, defined in .cpp
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyDataUpdate,     LobbyDataUpdate_t);
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyChatUpdate,      LobbyChatUpdate_t);
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyChatMessage,     LobbyChatMsg_t);
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyJoinRequested,   GameLobbyJoinRequested_t);
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyInviteReceived,  LobbyInvite_t);
	STEAM_CALLBACK(USteamLobbySubsystem, HandleLobbyKicked,          LobbyKicked_t);
};
