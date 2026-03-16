// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamFriendsSubsystem.h"
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

// ---------------------------------------------------------------------------
// UGameInstanceSubsystem
// ---------------------------------------------------------------------------

void USteamFriendsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
}

void USteamFriendsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Friends list
// ---------------------------------------------------------------------------

TArray<FSteamFriend> USteamFriendsSubsystem::GetFriendsList(bool bOnlineOnly) const
{
	TArray<FSteamFriend> Out;
	if (!IsSteamReady(this)) return Out;

	const int Count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
	for (int i = 0; i < Count; ++i)
	{
		const CSteamID FriendID = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
		const EPersonaState State = SteamFriends()->GetFriendPersonaState(FriendID);

		if (bOnlineOnly && State == k_EPersonaStateOffline) continue;

		FSteamFriend F;
		F.SteamID     = FSteamID(FriendID.ConvertToUint64());
		F.PersonaName = UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(FriendID));
		F.PersonaState = static_cast<ESteamPersonaState>(FMath::Clamp((int32)State, 0, 6));
		F.bIsInGame = [&]()
		{
			FriendGameInfo_t GameInfo;
			return SteamFriends()->GetFriendGamePlayed(FriendID, &GameInfo) && GameInfo.m_gameID.IsValid();
		}();
		Out.Add(F);
	}
	return Out;
}

FSteamFriend USteamFriendsSubsystem::GetFriendInfo(FSteamID SteamID) const
{
	FSteamFriend F;
	if (!IsSteamReady(this)) return F;

	const CSteamID Native(SteamID.AsUInt64());
	F.SteamID     = SteamID;
	F.PersonaName = UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(Native));
	const EPersonaState State = SteamFriends()->GetFriendPersonaState(Native);
	F.PersonaState = static_cast<ESteamPersonaState>(FMath::Clamp((int32)State, 0, 6));
	FriendGameInfo_t GameInfo;
	F.bIsInGame = SteamFriends()->GetFriendGamePlayed(Native, &GameInfo) && GameInfo.m_gameID.IsValid();
	return F;
}

FString USteamFriendsSubsystem::GetPersonaName(FSteamID SteamID) const
{
	if (!IsSteamReady(this)) return FString();
	// Local user
	if (SteamID.AsUInt64() == SteamUser()->GetSteamID().ConvertToUint64())
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetPersonaName());
	}
	return UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(CSteamID(SteamID.AsUInt64())));
}

ESteamPersonaState USteamFriendsSubsystem::GetPersonaState(FSteamID SteamID) const
{
	if (!IsSteamReady(this)) return ESteamPersonaState::Offline;
	const EPersonaState State = SteamFriends()->GetFriendPersonaState(CSteamID(SteamID.AsUInt64()));
	return static_cast<ESteamPersonaState>(FMath::Clamp((int32)State, 0, 6));
}

bool USteamFriendsSubsystem::HasFriend(FSteamID SteamID) const
{
	if (!IsSteamReady(this)) return false;
	return SteamFriends()->HasFriend(CSteamID(SteamID.AsUInt64()), k_EFriendFlagImmediate);
}

UTexture2D* USteamFriendsSubsystem::GetFriendAvatar(FSteamID SteamID, bool bLarge) const
{
	if (!IsSteamReady(this)) return nullptr;
	const CSteamID Native(SteamID.AsUInt64());
	const int Handle = bLarge
		? SteamFriends()->GetLargeFriendAvatar(Native)
		: SteamFriends()->GetMediumFriendAvatar(Native);
	return SteamImageToTexture(Handle);
}

// ---------------------------------------------------------------------------
// Overlay
// ---------------------------------------------------------------------------

void USteamFriendsSubsystem::ActivateOverlay(const FString& Dialog) const
{
	if (!IsSteamReady(this)) return;
	SteamFriends()->ActivateGameOverlay(TCHAR_TO_UTF8(*Dialog));
}

void USteamFriendsSubsystem::ActivateOverlayToUser(const FString& Dialog, FSteamID SteamID) const
{
	if (!IsSteamReady(this)) return;
	SteamFriends()->ActivateGameOverlayToUser(TCHAR_TO_UTF8(*Dialog), CSteamID(SteamID.AsUInt64()));
}

void USteamFriendsSubsystem::ActivateOverlayToWebPage(const FString& URL) const
{
	if (!IsSteamReady(this)) return;
	SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_UTF8(*URL));
}

void USteamFriendsSubsystem::ActivateOverlayToStore(int32 AppID) const
{
	if (!IsSteamReady(this)) return;
	const AppId_t AID = AppID <= 0 ? SteamUtils()->GetAppID() : static_cast<AppId_t>(AppID);
	SteamFriends()->ActivateGameOverlayToStore(AID, k_EOverlayToStoreFlag_None);
}

// ---------------------------------------------------------------------------
// Game invites
// ---------------------------------------------------------------------------

bool USteamFriendsSubsystem::InviteFriendToGame(FSteamID FriendSteamID, const FString& ConnectString) const
{
	if (!IsSteamReady(this)) return false;
	return SteamFriends()->InviteUserToGame(
		CSteamID(FriendSteamID.AsUInt64()), TCHAR_TO_UTF8(*ConnectString));
}

// ---------------------------------------------------------------------------
// Rich presence read side
// ---------------------------------------------------------------------------

void USteamFriendsSubsystem::RequestPersonaData(FSteamID SteamID)
{
	if (!IsSteamReady(this)) return;
	SteamFriends()->RequestUserInformation(CSteamID(SteamID.AsUInt64()), false);
}

FString USteamFriendsSubsystem::GetFriendRichPresenceValue(FSteamID SteamID, const FString& Key) const
{
	if (!IsSteamReady(this)) return FString();
	const char* Val = SteamFriends()->GetFriendRichPresence(
		CSteamID(SteamID.AsUInt64()), TCHAR_TO_UTF8(*Key));
	return Val ? UTF8_TO_TCHAR(Val) : FString();
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamFriendsSubsystem::HandlePersonaStateChange(PersonaStateChange_t* Param)
{
	FSteamID Changed(Param->m_ulSteamID);
	AsyncTask(ENamedThreads::GameThread, [this, Changed]()
	{
		OnPersonaStateChanged.Broadcast(Changed);
	});
}

void USteamFriendsSubsystem::HandleAvatarImageLoaded(AvatarImageLoaded_t* Param)
{
	FSteamID Changed(Param->m_steamID.ConvertToUint64());
	AsyncTask(ENamedThreads::GameThread, [this, Changed]()
	{
		OnAvatarLoaded.Broadcast(Changed);
	});
}

void USteamFriendsSubsystem::HandleGameRichPresenceJoin(GameRichPresenceJoinRequested_t* Param)
{
	FSteamID Inviter(Param->m_steamIDFriend.ConvertToUint64());
	AsyncTask(ENamedThreads::GameThread, [this, Inviter]()
	{
		OnGameInviteReceived.Broadcast(Inviter);
	});
}
