// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamUGCSubsystem.h"
#include "SteamSDK.h"
#include "SteamCoreSubsystem.h"
#include "UESteamFramework.h"
#include "Async/Async.h"

// Re-use the TLambdaCallResult template from SteamLobbySubsystem.cpp —
// since this is a separate translation unit, we duplicate the minimal version.
template<class P>
class TLambdaCallResultUGC : private CCallbackBase
{
public:
	using Func = TFunction<void(P*, bool)>;
	TLambdaCallResultUGC() { m_iCallback = P::k_iCallback; }
	~TLambdaCallResultUGC() { Cancel(); }

	void Set(SteamAPICall_t Handle, Func InFunc)
	{
		Cancel();
		m_hAPICall = Handle;
		m_Func     = MoveTemp(InFunc);
		if (m_hAPICall != k_uAPICallInvalid) SteamAPI_RegisterCallResult(this, m_hAPICall);
	}
	void Cancel()
	{
		if (m_hAPICall != k_uAPICallInvalid) { SteamAPI_UnregisterCallResult(this, m_hAPICall); m_hAPICall = k_uAPICallInvalid; }
	}
private:
	virtual int  GetCallbackSizeBytes() override { return sizeof(P); }
	virtual void Run(void* p) override { m_hAPICall = k_uAPICallInvalid; if (m_Func) m_Func((P*)p, false); }
	virtual void Run(void* p, bool bFail, SteamAPICall_t h) override { if (h == m_hAPICall) { m_hAPICall = k_uAPICallInvalid; if (m_Func) m_Func((P*)p, bFail); } }
	SteamAPICall_t m_hAPICall = k_uAPICallInvalid;
	Func m_Func;
};

static TLambdaCallResultUGC<SteamUGCQueryCompleted_t> GUGCQueryResult;

static bool IsSteamReady(const UGameInstanceSubsystem* Sub)
{
	if (const auto* Core = Sub->GetGameInstance()->GetSubsystem<USteamCoreSubsystem>())
	{
		return Core->IsSteamInitialized();
	}
	return false;
}

static EUGCMatchingUGCType ToSteamUGCType(EUGCMatchingType T)
{
	switch (T)
	{
	case EUGCMatchingType::Items:              return k_EUGCMatchingUGCType_Items;
	case EUGCMatchingType::Items_Mtx:          return k_EUGCMatchingUGCType_Items_Mtx;
	case EUGCMatchingType::Items_ReadyToUse:   return k_EUGCMatchingUGCType_Items_ReadyToUse;
	case EUGCMatchingType::Collections:        return k_EUGCMatchingUGCType_Collections;
	case EUGCMatchingType::Artwork:            return k_EUGCMatchingUGCType_Artwork;
	case EUGCMatchingType::Videos:             return k_EUGCMatchingUGCType_Videos;
	case EUGCMatchingType::Screenshots:        return k_EUGCMatchingUGCType_Screenshots;
	case EUGCMatchingType::AllGuides:          return k_EUGCMatchingUGCType_AllGuides;
	case EUGCMatchingType::WebGuides:          return k_EUGCMatchingUGCType_WebGuides;
	case EUGCMatchingType::IntegratedGuides:   return k_EUGCMatchingUGCType_IntegratedGuides;
	case EUGCMatchingType::UsableInGame:       return k_EUGCMatchingUGCType_UsableInGame;
	case EUGCMatchingType::ControllerBindings: return k_EUGCMatchingUGCType_ControllerBindings;
	case EUGCMatchingType::GameManagedItems:   return k_EUGCMatchingUGCType_GameManagedItems;
	default:                                   return k_EUGCMatchingUGCType_All;
	}
}

static void ParseQueryResults(UGCQueryHandle_t Handle, uint32 Count, TArray<FSteamUGCItem>& Out)
{
	for (uint32 i = 0; i < Count; ++i)
	{
		SteamUGCDetails_t Details;
		if (!SteamUGC()->GetQueryUGCResult(Handle, i, &Details)) continue;

		FSteamUGCItem Item;
		Item.PublishedFileID = static_cast<int64>(Details.m_nPublishedFileId);
		Item.Title           = UTF8_TO_TCHAR(Details.m_rgchTitle);
		Item.Description     = UTF8_TO_TCHAR(Details.m_rgchDescription);
		Item.OwnerSteamID    = FSteamID(Details.m_ulSteamIDOwner);
		Item.Score           = Details.m_flScore;
		Item.VotesUp         = static_cast<int32>(Details.m_unVotesUp);
		Item.VotesDown       = static_cast<int32>(Details.m_unVotesDown);

		uint32 SubCount = 0;
		SteamUGC()->GetNumSubscribedItems();  // ensure cache
		const uint32 StateFlags = SteamUGC()->GetItemState(Details.m_nPublishedFileId);
		Item.bIsSubscribed = (StateFlags & k_EItemStateSubscribed) != 0;
		Item.bIsInstalled  = (StateFlags & k_EItemStateInstalled) != 0;

		if (Item.bIsInstalled)
		{
			uint64 SizeOnDisk = 0; uint32 Timestamp = 0;
			char PathBuf[1024] = {};
			SteamUGC()->GetItemInstallInfo(Details.m_nPublishedFileId,
				&SizeOnDisk, PathBuf, sizeof(PathBuf), &Timestamp);
			Item.InstallPath = UTF8_TO_TCHAR(PathBuf);
		}

		Out.Add(Item);
	}
}

// ---------------------------------------------------------------------------
// UGameInstanceSubsystem
// ---------------------------------------------------------------------------

void USteamUGCSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
}

void USteamUGCSubsystem::Deinitialize()
{
	GUGCQueryResult.Cancel();
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Querying
// ---------------------------------------------------------------------------

void USteamUGCSubsystem::QueryAllItems(EUGCMatchingType MatchingType, int32 MaxResults)
{
	if (!IsSteamReady(this)) return;

	const AppId_t AppID = SteamUtils()->GetAppID();
	UGCQueryHandle_t QHandle = SteamUGC()->CreateQueryAllUGCRequest(
		k_EUGCQuery_RankedByVote,
		ToSteamUGCType(MatchingType),
		AppID, AppID, 1);

	if (QHandle == k_UGCQueryHandleInvalid) return;

	SteamUGC()->SetReturnOnlyIDs(QHandle, false);
	SteamUGC()->SetReturnLongDescription(QHandle, true);

	const SteamAPICall_t Call = SteamUGC()->SendQueryUGCRequest(QHandle);
	GUGCQueryResult.Set(Call, [this, QHandle, MaxResults](SteamUGCQueryCompleted_t* Res, bool bFail)
	{
		TArray<FSteamUGCItem> Items;
		const bool bOK = !bFail && Res->m_eResult == k_EResultOK;
		if (bOK)
		{
			const uint32 Count = FMath::Min((int32)Res->m_unNumResultsReturned, MaxResults);
			ParseQueryResults(Res->m_handle, Count, Items);
		}
		SteamUGC()->ReleaseQueryUGCRequest(QHandle);
		AsyncTask(ENamedThreads::GameThread, [this, bOK, Items]()
		{
			OnQueryComplete.Broadcast(bOK, Items);
		});
	});
}

void USteamUGCSubsystem::QuerySubscribedItems(EUGCMatchingType MatchingType)
{
	if (!IsSteamReady(this)) return;

	const AppId_t AppID = SteamUtils()->GetAppID();
	UGCQueryHandle_t QHandle = SteamUGC()->CreateQueryUserUGCRequest(
		SteamUser()->GetSteamID().GetAccountID(),
		k_EUserUGCList_Subscribed,
		ToSteamUGCType(MatchingType),
		k_EUGCQuery_RankedByVote,
		AppID, AppID, 1);

	if (QHandle == k_UGCQueryHandleInvalid) return;

	const SteamAPICall_t Call = SteamUGC()->SendQueryUGCRequest(QHandle);
	GUGCQueryResult.Set(Call, [this, QHandle](SteamUGCQueryCompleted_t* Res, bool bFail)
	{
		TArray<FSteamUGCItem> Items;
		const bool bOK = !bFail && Res->m_eResult == k_EResultOK;
		if (bOK) ParseQueryResults(Res->m_handle, Res->m_unNumResultsReturned, Items);
		SteamUGC()->ReleaseQueryUGCRequest(QHandle);
		AsyncTask(ENamedThreads::GameThread, [this, bOK, Items]()
		{
			OnQueryComplete.Broadcast(bOK, Items);
		});
	});
}

void USteamUGCSubsystem::QueryItemByID(int64 PublishedFileID)
{
	if (!IsSteamReady(this)) return;

	const PublishedFileId_t PFid = static_cast<PublishedFileId_t>(PublishedFileID);
	UGCQueryHandle_t QHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&PFid, 1);
	if (QHandle == k_UGCQueryHandleInvalid) return;

	const SteamAPICall_t Call = SteamUGC()->SendQueryUGCRequest(QHandle);
	GUGCQueryResult.Set(Call, [this, QHandle](SteamUGCQueryCompleted_t* Res, bool bFail)
	{
		TArray<FSteamUGCItem> Items;
		const bool bOK = !bFail && Res->m_eResult == k_EResultOK;
		if (bOK) ParseQueryResults(Res->m_handle, Res->m_unNumResultsReturned, Items);
		SteamUGC()->ReleaseQueryUGCRequest(QHandle);
		AsyncTask(ENamedThreads::GameThread, [this, bOK, Items]()
		{
			OnQueryComplete.Broadcast(bOK, Items);
		});
	});
}

// ---------------------------------------------------------------------------
// Subscriptions
// ---------------------------------------------------------------------------

void USteamUGCSubsystem::SubscribeItem(int64 PublishedFileID)
{
	if (!IsSteamReady(this)) return;
	SteamUGC()->SubscribeItem(static_cast<PublishedFileId_t>(PublishedFileID));
}

void USteamUGCSubsystem::UnsubscribeItem(int64 PublishedFileID)
{
	if (!IsSteamReady(this)) return;
	SteamUGC()->UnsubscribeItem(static_cast<PublishedFileId_t>(PublishedFileID));
}

bool USteamUGCSubsystem::IsItemInstalled(int64 PublishedFileID, FString& OutInstallPath) const
{
	OutInstallPath.Empty();
	if (!IsSteamReady(this)) return false;

	const PublishedFileId_t PFid = static_cast<PublishedFileId_t>(PublishedFileID);
	const uint32 State = SteamUGC()->GetItemState(PFid);
	if (!(State & k_EItemStateInstalled)) return false;

	uint64 Size = 0; uint32 Timestamp = 0;
	char Buf[1024] = {};
	SteamUGC()->GetItemInstallInfo(PFid, &Size, Buf, sizeof(Buf), &Timestamp);
	OutInstallPath = UTF8_TO_TCHAR(Buf);
	return true;
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamUGCSubsystem::HandleDownloadItemResult(DownloadItemResult_t* Param)
{
	const int64 PFid = static_cast<int64>(Param->m_nPublishedFileId);
	const bool  bOK  = Param->m_eResult == k_EResultOK;
	AsyncTask(ENamedThreads::GameThread, [this, PFid, bOK]()
	{
		OnDownloadComplete.Broadcast(PFid, bOK);
	});
}
