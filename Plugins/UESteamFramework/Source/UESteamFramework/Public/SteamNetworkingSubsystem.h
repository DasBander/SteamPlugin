// Copyright Marc Fraedrich. All Rights Reserved.
// SteamNetworkingSubsystem.h
// Peer-to-peer networking via ISteamNetworking (legacy P2P + reliable channels).
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "SteamTypes.h"

THIRD_PARTY_INCLUDES_START
#pragma warning(push)
#pragma warning(disable : 4996 4265 4828)
#include "steam/steam_api.h"
#pragma warning(pop)
THIRD_PARTY_INCLUDES_END

#include "SteamNetworkingSubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamNetOnSessionRequest,   FSteamID, RemoteSteamID, int32, Channel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSteamNetOnSessionFailed,  FSteamID, RemoteSteamID, int32, Channel, int32, SessionErrorCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSteamNetOnPacketReceived, FSteamID, SenderSteamID, int32, Channel, TArray<uint8>, Data);

/**
 * USteamNetworkingSubsystem
 *
 * Provides peer-to-peer networking through Steam Networking (ISteamNetworking).
 * Packets are automatically pumped each tick if IsActive returns true.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamNetworkingSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamNetworkingSubsystem
	: public UGameInstanceSubsystem
	, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// FTickableGameObject
	virtual void    Tick(float DeltaTime) override;
	virtual bool    IsTickable() const override;
	virtual TStatId GetStatId() const override;

	// -----------------------------------------------------------------------
	// Sending
	// -----------------------------------------------------------------------

	/**
	 * Sends a raw byte packet to a remote Steam user.
	 * @param RemoteSteamID  Target peer.
	 * @param Channel        Logical channel (0–31).
	 * @param Data           Payload bytes.
	 * @param SendType       Reliability / ordering.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Networking")
	bool SendPacket(FSteamID RemoteSteamID, int32 Channel,
	                const TArray<uint8>& Data, ESteamP2PSendType SendType = ESteamP2PSendType::Reliable);

	/**
	 * Convenience: sends a UTF-8 string as a packet.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Networking")
	bool SendString(FSteamID RemoteSteamID, int32 Channel,
	                const FString& Message, ESteamP2PSendType SendType = ESteamP2PSendType::Reliable);

	// -----------------------------------------------------------------------
	// Session management
	// -----------------------------------------------------------------------

	/**
	 * Accepts a pending P2P session from a remote peer.
	 * Call this after receiving OnSessionRequest to allow packets from that peer.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Networking")
	bool AcceptP2PSession(FSteamID RemoteSteamID);

	/** Closes the P2P session with a peer and flushes its outgoing queue. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Networking")
	bool CloseP2PSession(FSteamID RemoteSteamID);

	/** Closes a specific channel to a peer without destroying the session. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Networking")
	bool CloseP2PChannel(FSteamID RemoteSteamID, int32 Channel);

	/** Returns true if there is an active P2P session with the given peer. */
	UFUNCTION(BlueprintPure, Category = "Steam|Networking")
	bool GetP2PSessionState(FSteamID RemoteSteamID, bool& bConnecting, bool& bActive,
	                        int32& BytesQueuedForSend, int32& PacketsQueuedForSend) const;

	// -----------------------------------------------------------------------
	// Packet pump settings
	// -----------------------------------------------------------------------

	/** Channels to poll for incoming packets each tick.  Default: {0}. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam|Networking")
	TArray<int32> ActiveChannels = { 0 };

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	/** Fires when a remote peer wants to open a P2P session. Accept or ignore. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Networking|Callbacks")
	FSteamNetOnSessionRequest OnSessionRequest;

	/** Fires when a P2P session fails (e.g. remote peer unreachable). */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Networking|Callbacks")
	FSteamNetOnSessionFailed OnSessionFailed;

	/** Fires for every received packet (called from Tick). */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Networking|Callbacks")
	FSteamNetOnPacketReceived OnPacketReceived;

private:
	bool bIsActive = false;

	STEAM_CALLBACK(USteamNetworkingSubsystem, HandleP2PSessionRequest, P2PSessionRequest_t);
	STEAM_CALLBACK(USteamNetworkingSubsystem, HandleP2PSessionConnectFail, P2PSessionConnectFail_t);
};
