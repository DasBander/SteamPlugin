// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamNetworkingSubsystem.h"
#include "SteamSDK.h"
#include "SteamCoreSubsystem.h"
#include "UESteamFramework.h"
#include "Async/Async.h"

static bool IsSteamReady(const UGameInstanceSubsystem* Sub)
{
	if (const auto* Core = Sub->GetGameInstance()->GetSubsystem<USteamCoreSubsystem>())
	{
		return Core->IsSteamInitialized();
	}
	return false;
}

static EP2PSend ToSteamSendType(ESteamP2PSendType T)
{
	switch (T)
	{
	case ESteamP2PSendType::Unreliable:            return k_EP2PSendUnreliable;
	case ESteamP2PSendType::UnreliableNoDelay:     return k_EP2PSendUnreliableNoDelay;
	case ESteamP2PSendType::ReliableWithBuffering: return k_EP2PSendReliableWithBuffering;
	default:                                       return k_EP2PSendReliable;
	}
}

// ---------------------------------------------------------------------------
// UGameInstanceSubsystem
// ---------------------------------------------------------------------------

void USteamNetworkingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
	bIsActive = IsSteamReady(this);
}

void USteamNetworkingSubsystem::Deinitialize()
{
	bIsActive = false;
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// FTickableGameObject — pump incoming packets
// ---------------------------------------------------------------------------

void USteamNetworkingSubsystem::Tick(float /*DeltaTime*/)
{
	if (!bIsActive) return;

	for (int32 Channel : ActiveChannels)
	{
		uint32 MsgSize = 0;
		while (SteamNetworking()->IsP2PPacketAvailable(&MsgSize, Channel))
		{
			TArray<uint8> Data;
			Data.SetNumUninitialized(MsgSize);
			CSteamID SenderID;
			uint32 BytesRead = 0;
			if (SteamNetworking()->ReadP2PPacket(Data.GetData(), MsgSize, &BytesRead, &SenderID, Channel))
			{
				Data.SetNum(BytesRead);
				FSteamID Sender(SenderID.ConvertToUint64());
				// Dispatch on game thread — already on game thread since Tick() is game-thread
				OnPacketReceived.Broadcast(Sender, Channel, Data);
			}
		}
	}
}

bool USteamNetworkingSubsystem::IsTickable() const
{
	return bIsActive;
}

TStatId USteamNetworkingSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(USteamNetworkingSubsystem, STATGROUP_Tickables);
}

// ---------------------------------------------------------------------------
// Sending
// ---------------------------------------------------------------------------

bool USteamNetworkingSubsystem::SendPacket(
	FSteamID RemoteSteamID, int32 Channel,
	const TArray<uint8>& Data, ESteamP2PSendType SendType)
{
	if (!bIsActive || Data.Num() == 0) return false;
	return SteamNetworking()->SendP2PPacket(
		CSteamID(RemoteSteamID.AsUInt64()),
		Data.GetData(), Data.Num(),
		ToSteamSendType(SendType), Channel);
}

bool USteamNetworkingSubsystem::SendString(
	FSteamID RemoteSteamID, int32 Channel,
	const FString& Message, ESteamP2PSendType SendType)
{
	const FTCHARToUTF8 UTF8(*Message);
	TArray<uint8> Data(reinterpret_cast<const uint8*>(UTF8.Get()), UTF8.Length() + 1);
	return SendPacket(RemoteSteamID, Channel, Data, SendType);
}

// ---------------------------------------------------------------------------
// Session management
// ---------------------------------------------------------------------------

bool USteamNetworkingSubsystem::AcceptP2PSession(FSteamID RemoteSteamID)
{
	if (!bIsActive) return false;
	return SteamNetworking()->AcceptP2PSessionWithUser(CSteamID(RemoteSteamID.AsUInt64()));
}

bool USteamNetworkingSubsystem::CloseP2PSession(FSteamID RemoteSteamID)
{
	if (!bIsActive) return false;
	return SteamNetworking()->CloseP2PSessionWithUser(CSteamID(RemoteSteamID.AsUInt64()));
}

bool USteamNetworkingSubsystem::CloseP2PChannel(FSteamID RemoteSteamID, int32 Channel)
{
	if (!bIsActive) return false;
	return SteamNetworking()->CloseP2PChannelWithUser(
		CSteamID(RemoteSteamID.AsUInt64()), Channel);
}

bool USteamNetworkingSubsystem::GetP2PSessionState(
	FSteamID RemoteSteamID, bool& bConnecting, bool& bActive,
	int32& BytesQueuedForSend, int32& PacketsQueuedForSend) const
{
	bConnecting = bActive = false;
	BytesQueuedForSend = PacketsQueuedForSend = 0;
	if (!bIsActive) return false;

	P2PSessionState_t State;
	if (!SteamNetworking()->GetP2PSessionState(CSteamID(RemoteSteamID.AsUInt64()), &State))
	{
		return false;
	}
	bConnecting         = State.m_bConnecting != 0;
	bActive             = State.m_bConnectionActive != 0;
	BytesQueuedForSend  = static_cast<int32>(State.m_nBytesQueuedForSend);
	PacketsQueuedForSend = static_cast<int32>(State.m_nPacketsQueuedForSend);
	return true;
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamNetworkingSubsystem::HandleP2PSessionRequest(P2PSessionRequest_t* Param)
{
	FSteamID Remote(Param->m_steamIDRemote.ConvertToUint64());
	AsyncTask(ENamedThreads::GameThread, [this, Remote]()
	{
		OnSessionRequest.Broadcast(Remote, 0);
	});
}

void USteamNetworkingSubsystem::HandleP2PSessionConnectFail(P2PSessionConnectFail_t* Param)
{
	FSteamID Remote(Param->m_steamIDRemote.ConvertToUint64());
	const int32 ErrCode = static_cast<int32>(Param->m_eP2PSessionError);
	AsyncTask(ENamedThreads::GameThread, [this, Remote, ErrCode]()
	{
		OnSessionFailed.Broadcast(Remote, 0, ErrCode);
	});
}
