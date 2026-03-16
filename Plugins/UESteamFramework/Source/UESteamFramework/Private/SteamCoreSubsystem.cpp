// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamCoreSubsystem.h"
#include "SteamSDK.h"
#include "SteamSettings.h"
#include "UESteamFramework.h"
#include "Async/Async.h"
#include "Misc/MessageDialog.h"

// ---------------------------------------------------------------------------
// UGameInstanceSubsystem
// ---------------------------------------------------------------------------

void USteamCoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	bInitialized = SteamAPI_Init();

	if (!bInitialized)
	{
		UE_LOG(LogSteamFramework, Error,
			TEXT("SteamAPI_Init() failed. Make sure Steam is running and steam_appid.txt is present."));

		const FText Msg   = NSLOCTEXT("SteamFramework", "SteamNotRunning",
			"This game requires Steam to be running.\nPlease start Steam and try again.");
		const FText Title = NSLOCTEXT("SteamFramework", "SteamNotRunningTitle", "Steam Not Running");
		FMessageDialog::Open(EAppMsgType::Ok, Msg, Title);
		return;
	}

	UE_LOG(LogSteamFramework, Log, TEXT("Steam API initialised. AppID: %u"), SteamUtils()->GetAppID());

	// Optionally enforce ownership
	const USteamSettings* Settings = GetDefault<USteamSettings>();
	if (Settings && Settings->bEnforceOwnershipCheck)
	{
		if ((int32)SteamUtils()->GetAppID() != Settings->AppID)
		{
			const FText Msg   = NSLOCTEXT("SteamFramework", "OwnershipFailed",
				"App ownership check failed.\nYou must own this game before launching it.");
			const FText Title = NSLOCTEXT("SteamFramework", "OwnershipFailedTitle", "Ownership Check Failed");
			FMessageDialog::Open(EAppMsgType::Ok, Msg, Title);
			FPlatformMisc::RequestExit(true);
			return;
		}
	}
}

void USteamCoreSubsystem::Deinitialize()
{
	if (bInitialized)
	{
		SteamAPI_Shutdown();
		bInitialized = false;
		UE_LOG(LogSteamFramework, Log, TEXT("Steam API shut down."));
	}
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// FTickableGameObject
// ---------------------------------------------------------------------------

void USteamCoreSubsystem::Tick(float /*DeltaTime*/)
{
	SteamAPI_RunCallbacks();
}

bool USteamCoreSubsystem::IsTickable() const
{
	return bInitialized;
}

TStatId USteamCoreSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(USteamCoreSubsystem, STATGROUP_Tickables);
}

// ---------------------------------------------------------------------------
// Steam status
// ---------------------------------------------------------------------------

int32 USteamCoreSubsystem::GetAppID() const
{
	return bInitialized ? static_cast<int32>(SteamUtils()->GetAppID()) : 0;
}

int32 USteamCoreSubsystem::GetBuildID() const
{
	return bInitialized ? SteamApps()->GetAppBuildId() : 0;
}

FString USteamCoreSubsystem::GetCurrentGameLanguage() const
{
	if (!bInitialized) return FString();
	return UTF8_TO_TCHAR(SteamApps()->GetCurrentGameLanguage());
}

FString USteamCoreSubsystem::GetAvailableGameLanguages() const
{
	if (!bInitialized) return FString();
	return UTF8_TO_TCHAR(SteamApps()->GetAvailableGameLanguages());
}

bool USteamCoreSubsystem::IsSubscribed() const
{
	return bInitialized && SteamApps()->BIsSubscribed();
}

bool USteamCoreSubsystem::IsVACBanned() const
{
	return bInitialized && SteamApps()->BIsVACBanned();
}

// ---------------------------------------------------------------------------
// Local user
// ---------------------------------------------------------------------------

FSteamID USteamCoreSubsystem::GetLocalUserSteamID() const
{
	if (!bInitialized) return FSteamID();
	return FSteamID(SteamUser()->GetSteamID().ConvertToUint64());
}

FString USteamCoreSubsystem::GetLocalPersonaName() const
{
	if (!bInitialized) return FString();
	return UTF8_TO_TCHAR(SteamFriends()->GetPersonaName());
}

UTexture2D* USteamCoreSubsystem::GetAvatar(FSteamID SteamID, bool bLarge) const
{
	if (!bInitialized) return nullptr;
	const CSteamID Native(SteamID.AsUInt64());
	const int Handle = bLarge
		? SteamFriends()->GetLargeFriendAvatar(Native)
		: SteamFriends()->GetMediumFriendAvatar(Native);
	return SteamImageToTexture(Handle);
}

// ---------------------------------------------------------------------------
// Rich Presence
// ---------------------------------------------------------------------------

void USteamCoreSubsystem::SetRichPresence(const FString& Key, const FString& Value)
{
	if (!bInitialized) return;
	SteamFriends()->SetRichPresence(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}

void USteamCoreSubsystem::ClearRichPresence()
{
	if (!bInitialized) return;
	SteamFriends()->ClearRichPresence();
}

FString USteamCoreSubsystem::GetFriendRichPresence(FSteamID SteamID, const FString& Key) const
{
	if (!bInitialized) return FString();
	const char* Value = SteamFriends()->GetFriendRichPresence(
		CSteamID(SteamID.AsUInt64()), TCHAR_TO_UTF8(*Key));
	return Value ? UTF8_TO_TCHAR(Value) : FString();
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamCoreSubsystem::HandleGameOverlayActivated(GameOverlayActivated_t* Param)
{
	const bool bActive = Param->m_bActive != 0;
	AsyncTask(ENamedThreads::GameThread, [this, bActive]()
	{
		OnGameOverlayActivated.Broadcast(bActive);
	});
}

void USteamCoreSubsystem::HandleSteamShutdown(SteamShutdown_t* /*Param*/)
{
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		OnSteamShutdown.Broadcast();
	});
}
