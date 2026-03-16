// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamLobbySubsystem.h"
#include "SteamSDK.h"
#include "SteamCoreSubsystem.h"
#include "SteamFriendsSubsystem.h"
#include "UESteamFramework.h"
#include "Async/Async.h"

// ---------------------------------------------------------------------------
// Lambda call-result helper (replaces steamsdk_lambda_callresults.h)
// ---------------------------------------------------------------------------

template<class P>
class TLambdaCallResult : private CCallbackBase
{
public:
	using Func = TFunction<void(P*, bool)>;

	TLambdaCallResult() { m_iCallback = P::k_iCallback; }
	~TLambdaCallResult() { Cancel(); }

	void Set(SteamAPICall_t Handle, Func InFunc)
	{
		Cancel();
		m_hAPICall = Handle;
		m_Func     = MoveTemp(InFunc);
		if (m_hAPICall != k_uAPICallInvalid)
		{
			SteamAPI_RegisterCallResult(this, m_hAPICall);
		}
	}

	void Cancel()
	{
		if (m_hAPICall != k_uAPICallInvalid)
		{
			SteamAPI_UnregisterCallResult(this, m_hAPICall);
			m_hAPICall = k_uAPICallInvalid;
		}
	}

	bool IsActive() const { return m_hAPICall != k_uAPICallInvalid; }

private:
	virtual int  GetCallbackSizeBytes() override { return sizeof(P); }
	virtual void Run(void* pParam) override
	{
		m_hAPICall = k_uAPICallInvalid;
		if (m_Func) m_Func(static_cast<P*>(pParam), false);
	}
	virtual void Run(void* pParam, bool bIOFailure, SteamAPICall_t hCall) override
	{
		if (hCall == m_hAPICall)
		{
			m_hAPICall = k_uAPICallInvalid;
			if (m_Func) m_Func(static_cast<P*>(pParam), bIOFailure);
		}
	}

	SteamAPICall_t m_hAPICall = k_uAPICallInvalid;
	Func           m_Func;
};

// ---------------------------------------------------------------------------

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

void USteamLobbySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);

	CallResult_LobbyCreated = new TLambdaCallResult<LobbyCreated_t>;
	CallResult_LobbyEntered = new TLambdaCallResult<LobbyEnter_t>;
	CallResult_LobbyList    = new TLambdaCallResult<LobbyMatchList_t>;
}

// Helper casts (avoids repeating in every function)
#define LOBBY_CR_CREATED  (static_cast<TLambdaCallResult<LobbyCreated_t>*>(CallResult_LobbyCreated))
#define LOBBY_CR_ENTERED  (static_cast<TLambdaCallResult<LobbyEnter_t>*>(CallResult_LobbyEntered))
#define LOBBY_CR_LIST     (static_cast<TLambdaCallResult<LobbyMatchList_t>*>(CallResult_LobbyList))

void USteamLobbySubsystem::Deinitialize()
{
	delete LOBBY_CR_CREATED; CallResult_LobbyCreated = nullptr;
	delete LOBBY_CR_ENTERED; CallResult_LobbyEntered = nullptr;
	delete LOBBY_CR_LIST;    CallResult_LobbyList    = nullptr;
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Lobby lifecycle
// ---------------------------------------------------------------------------

static ELobbyType ToSteamLobbyType(ELobbyVisibility V)
{
	switch (V)
	{
	case ELobbyVisibility::Private:     return k_ELobbyTypePrivate;
	case ELobbyVisibility::FriendsOnly: return k_ELobbyTypeFriendsOnly;
	case ELobbyVisibility::Invisible:   return k_ELobbyTypeInvisible;
	default:                            return k_ELobbyTypePublic;
	}
}

void USteamLobbySubsystem::CreateLobby(FLobbyCreateParams Params)
{
	if (!IsSteamReady(this)) return;

	SteamAPICall_t Call = SteamMatchmaking()->CreateLobby(
		ToSteamLobbyType(Params.Visibility), Params.MaxPlayers);

	LOBBY_CR_CREATED->Set(Call, [this, Params](LobbyCreated_t* Result, bool bIOFailure)
	{
		FLobbyCreateResult Out;
		if (bIOFailure || Result->m_eResult != k_EResultOK)
		{
			switch (Result ? Result->m_eResult : k_EResultFail)
			{
			case k_EResultTimeout:      Out.Result = ELobbyCreateResult::Timeout;      break;
			case k_EResultNoConnection: Out.Result = ELobbyCreateResult::NoConnection; break;
			default:                    Out.Result = ELobbyCreateResult::Failed;       break;
			}
		}
		else
		{
			Out.Result  = ELobbyCreateResult::Success;
			Out.LobbyID = FSteamID(Result->m_ulSteamIDLobby);
			bIsInLobby   = true;
			CurrentLobbyID = Out.LobbyID;

			// Set lobby metadata
			const CSteamID LobbyNative(Result->m_ulSteamIDLobby);
			SteamMatchmaking()->SetLobbyData(LobbyNative, "LobbyName", TCHAR_TO_UTF8(*Params.LobbyName));
			const FString OwnerID = FString::Printf(TEXT("%llu"),
				SteamUser()->GetSteamID().ConvertToUint64());
			SteamMatchmaking()->SetLobbyData(LobbyNative, "LobbyOwner", TCHAR_TO_UTF8(*OwnerID));
			const FString PwHash = Params.GetPasswordHash();
			SteamMatchmaking()->SetLobbyData(LobbyNative, "LobbyPassword", TCHAR_TO_UTF8(*PwHash));
		}

		AsyncTask(ENamedThreads::GameThread, [this, Out]()
		{
			OnLobbyCreated.Broadcast(Out);
		});
	});
}

void USteamLobbySubsystem::JoinLobby(FSteamID LobbyID)
{
	if (!IsSteamReady(this)) return;

	SteamAPICall_t Call = SteamMatchmaking()->JoinLobby(CSteamID(LobbyID.AsUInt64()));

	LOBBY_CR_ENTERED->Set(Call, [this](LobbyEnter_t* Result, bool bIOFailure)
	{
		if (!bIOFailure && Result->m_EChatRoomEnterResponse == k_EChatRoomEnterResponseSuccess)
		{
			bIsInLobby     = true;
			CurrentLobbyID = FSteamID(Result->m_ulSteamIDLobby);
			const FSteamID LobbyID = CurrentLobbyID;
			AsyncTask(ENamedThreads::GameThread, [this, LobbyID]()
			{
				OnLobbyEntered.Broadcast(LobbyID);
			});
		}
	});
}

void USteamLobbySubsystem::LeaveLobby()
{
	if (!bIsInLobby || !IsSteamReady(this)) return;

	SteamMatchmaking()->LeaveLobby(CSteamID(CurrentLobbyID.AsUInt64()));
	bIsInLobby     = false;
	CurrentLobbyID = FSteamID();
	OnLobbyLeft.Broadcast();
}

// ---------------------------------------------------------------------------
// Lobby search
// ---------------------------------------------------------------------------

void USteamLobbySubsystem::AddStringFilter(const FString& Key, const FString& Value, ELobbyComparison Comparison)
{
	if (!IsSteamReady(this)) return;
	const auto Cmp = static_cast<ELobbyComparison_t>((int)Comparison - 2); // map enum to SDK values
	SteamMatchmaking()->AddRequestLobbyListStringFilter(
		TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value), Cmp);
}

void USteamLobbySubsystem::AddNumericalFilter(const FString& Key, int32 Value, ELobbyComparison Comparison)
{
	if (!IsSteamReady(this)) return;
	const auto Cmp = static_cast<ELobbyComparison_t>((int)Comparison - 2);
	SteamMatchmaking()->AddRequestLobbyListNumericalFilter(
		TCHAR_TO_UTF8(*Key), Value, Cmp);
}

void USteamLobbySubsystem::AddSlotsAvailableFilter(int32 MinOpenSlots)
{
	if (!IsSteamReady(this)) return;
	SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(MinOpenSlots);
}

void USteamLobbySubsystem::SetDistanceFilter(ELobbyDistanceFilter Filter)
{
	if (!IsSteamReady(this)) return;
	SteamMatchmaking()->AddRequestLobbyListDistanceFilter(
		static_cast<ELobbyDistanceFilter_t>((int)Filter));
}

void USteamLobbySubsystem::SetResultCountLimit(int32 Max)
{
	if (!IsSteamReady(this)) return;
	SteamMatchmaking()->AddRequestLobbyListResultCountFilter(Max);
}

void USteamLobbySubsystem::RequestLobbyList()
{
	if (!IsSteamReady(this)) return;

	SteamAPICall_t Call = SteamMatchmaking()->RequestLobbyList();

	LOBBY_CR_LIST->Set(Call, [this](LobbyMatchList_t* Result, bool bIOFailure)
	{
		TArray<FLobbySearchResult> Results;
		if (!bIOFailure)
		{
			for (uint32 i = 0; i < Result->m_nLobbiesMatching; ++i)
			{
				const CSteamID LID = SteamMatchmaking()->GetLobbyByIndex(i);
				FLobbySearchResult R;
				R.LobbyID     = FSteamID(LID.ConvertToUint64());
				R.LobbyName   = UTF8_TO_TCHAR(SteamMatchmaking()->GetLobbyData(LID, "LobbyName"));
				R.MemberCount = SteamMatchmaking()->GetNumLobbyMembers(LID);
				R.MaxMembers  = SteamMatchmaking()->GetLobbyMemberLimit(LID);
				const FString PwHash(SteamMatchmaking()->GetLobbyData(LID, "LobbyPassword"));
				R.bHasPassword = !PwHash.IsEmpty();
				Results.Add(R);
			}
		}
		AsyncTask(ENamedThreads::GameThread, [this, Results]()
		{
			OnSearchComplete.Broadcast(Results);
		});
	});
}

// ---------------------------------------------------------------------------
// Lobby metadata
// ---------------------------------------------------------------------------

FString USteamLobbySubsystem::GetLobbyData(const FString& Key) const
{
	if (!bIsInLobby || !IsSteamReady(this)) return FString();
	return UTF8_TO_TCHAR(SteamMatchmaking()->GetLobbyData(
		CSteamID(CurrentLobbyID.AsUInt64()), TCHAR_TO_UTF8(*Key)));
}

bool USteamLobbySubsystem::SetLobbyData(const FString& Key, const FString& Value)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->SetLobbyData(
		CSteamID(CurrentLobbyID.AsUInt64()), TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}

FString USteamLobbySubsystem::GetMemberData(FSteamID MemberSteamID, const FString& Key) const
{
	if (!bIsInLobby || !IsSteamReady(this)) return FString();
	return UTF8_TO_TCHAR(SteamMatchmaking()->GetLobbyMemberData(
		CSteamID(CurrentLobbyID.AsUInt64()),
		CSteamID(MemberSteamID.AsUInt64()),
		TCHAR_TO_UTF8(*Key)));
}

void USteamLobbySubsystem::SetMemberData(const FString& Key, const FString& Value)
{
	if (!bIsInLobby || !IsSteamReady(this)) return;
	SteamMatchmaking()->SetLobbyMemberData(
		CSteamID(CurrentLobbyID.AsUInt64()),
		TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}

// ---------------------------------------------------------------------------
// Members
// ---------------------------------------------------------------------------

TArray<FSteamFriend> USteamLobbySubsystem::GetMembers() const
{
	TArray<FSteamFriend> Out;
	if (!bIsInLobby || !IsSteamReady(this)) return Out;

	const CSteamID LobbyNative(CurrentLobbyID.AsUInt64());
	const int Count = SteamMatchmaking()->GetNumLobbyMembers(LobbyNative);
	for (int i = 0; i < Count; ++i)
	{
		const CSteamID MemberID = SteamMatchmaking()->GetLobbyMemberByIndex(LobbyNative, i);
		FSteamFriend F;
		F.SteamID     = FSteamID(MemberID.ConvertToUint64());
		F.PersonaName = UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(MemberID));
		Out.Add(F);
	}
	return Out;
}

int32 USteamLobbySubsystem::GetMemberCount() const
{
	if (!bIsInLobby || !IsSteamReady(this)) return 0;
	return SteamMatchmaking()->GetNumLobbyMembers(CSteamID(CurrentLobbyID.AsUInt64()));
}

FSteamID USteamLobbySubsystem::GetOwner() const
{
	if (!bIsInLobby || !IsSteamReady(this)) return FSteamID();
	return FSteamID(SteamMatchmaking()->GetLobbyOwner(
		CSteamID(CurrentLobbyID.AsUInt64())).ConvertToUint64());
}

bool USteamLobbySubsystem::IsOwner() const
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->GetLobbyOwner(CSteamID(CurrentLobbyID.AsUInt64()))
		== SteamUser()->GetSteamID();
}

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------

bool USteamLobbySubsystem::SetLobbyVisibility(ELobbyVisibility Visibility)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->SetLobbyType(
		CSteamID(CurrentLobbyID.AsUInt64()), ToSteamLobbyType(Visibility));
}

bool USteamLobbySubsystem::SetJoinable(bool bJoinable)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->SetLobbyJoinable(
		CSteamID(CurrentLobbyID.AsUInt64()), bJoinable);
}

bool USteamLobbySubsystem::SetMemberLimit(int32 MaxMembers)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->SetLobbyMemberLimit(
		CSteamID(CurrentLobbyID.AsUInt64()), MaxMembers);
}

// ---------------------------------------------------------------------------
// Chat
// ---------------------------------------------------------------------------

bool USteamLobbySubsystem::SendChatMessage(const FString& Message)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	const FTCHARToUTF8 UTF8(*Message);
	return SteamMatchmaking()->SendLobbyChatMsg(
		CSteamID(CurrentLobbyID.AsUInt64()),
		UTF8.Get(), UTF8.Length() + 1);
}

// ---------------------------------------------------------------------------
// Invites
// ---------------------------------------------------------------------------

bool USteamLobbySubsystem::InviteFriend(FSteamID FriendSteamID)
{
	if (!bIsInLobby || !IsSteamReady(this)) return false;
	return SteamMatchmaking()->InviteUserToLobby(
		CSteamID(CurrentLobbyID.AsUInt64()),
		CSteamID(FriendSteamID.AsUInt64()));
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamLobbySubsystem::HandleLobbyDataUpdate(LobbyDataUpdate_t* Param)
{
	if (!Param->m_bSuccess) return;
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		OnLobbyDataUpdated.Broadcast();
	});
}

void USteamLobbySubsystem::HandleLobbyChatUpdate(LobbyChatUpdate_t* Param)
{
	const FSteamID AffectedID(Param->m_ulSteamIDUserChanged);
	const uint32 Change = Param->m_rgfChatMemberStateChange;

	AsyncTask(ENamedThreads::GameThread, [this, AffectedID, Change]()
	{
		OnLobbyDataUpdated.Broadcast();
		if (Change & k_EChatMemberStateChangeEntered)
		{
			OnMemberJoined.Broadcast(AffectedID);
		}
		if (Change & (k_EChatMemberStateChangeLeft |
		              k_EChatMemberStateChangeDisconnected |
		              k_EChatMemberStateChangeKicked |
		              k_EChatMemberStateChangeBanned))
		{
			OnMemberLeft.Broadcast(AffectedID);
		}
	});
}

void USteamLobbySubsystem::HandleLobbyChatMessage(LobbyChatMsg_t* Param)
{
	// Read the message data from Steam
	CSteamID SenderID;
	EChatEntryType EntryType;
	char Buffer[4096] = {};
	const int Written = SteamMatchmaking()->GetLobbyChatEntry(
		CSteamID(Param->m_ulSteamIDLobby),
		Param->m_iChatID, &SenderID, Buffer, sizeof(Buffer), &EntryType);

	if (Written <= 0 || EntryType != k_EChatEntryTypeChatMsg) return;

	const FSteamID SenderSteamID(SenderID.ConvertToUint64());
	const FString  Msg(UTF8_TO_TCHAR(Buffer));

	AsyncTask(ENamedThreads::GameThread, [this, SenderSteamID, Msg]()
	{
		OnChatMessageReceived.Broadcast(SenderSteamID, Msg);
	});
}

void USteamLobbySubsystem::HandleLobbyJoinRequested(GameLobbyJoinRequested_t* Param)
{
	// User accepted a game invite from outside the game — auto-join
	FSteamID LobbyID(Param->m_steamIDLobby.ConvertToUint64());
	AsyncTask(ENamedThreads::GameThread, [this, LobbyID]()
	{
		JoinLobby(LobbyID);
	});
}

void USteamLobbySubsystem::HandleLobbyInviteReceived(LobbyInvite_t* Param)
{
	FSteamID Inviter(Param->m_ulSteamIDUser);
	AsyncTask(ENamedThreads::GameThread, [this, Inviter]()
	{
		OnInviteReceived.Broadcast(Inviter);
	});
}

void USteamLobbySubsystem::HandleLobbyKicked(LobbyKicked_t* Param)
{
	bIsInLobby     = false;
	CurrentLobbyID = FSteamID();
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		OnLobbyLeft.Broadcast();
	});
}
