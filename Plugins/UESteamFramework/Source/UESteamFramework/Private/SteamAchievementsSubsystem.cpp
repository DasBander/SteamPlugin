// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamAchievementsSubsystem.h"
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

void USteamAchievementsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
	// Automatically kick off a stats request on startup
	RequestCurrentStats();
}

void USteamAchievementsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Stats sync
// ---------------------------------------------------------------------------

void USteamAchievementsSubsystem::RequestCurrentStats()
{
	if (!IsSteamReady(this)) return;
	bStatsRequested = SteamUserStats()->RequestCurrentStats();
}

bool USteamAchievementsSubsystem::StoreStats()
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	return SteamUserStats()->StoreStats();
}

bool USteamAchievementsSubsystem::ResetAllStats(bool bAchievementsToo)
{
	if (!IsSteamReady(this)) return false;
	return SteamUserStats()->ResetAllStats(bAchievementsToo);
}

// ---------------------------------------------------------------------------
// Achievements
// ---------------------------------------------------------------------------

bool USteamAchievementsSubsystem::SetAchievement(const FString& APIName)
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	return SteamUserStats()->SetAchievement(TCHAR_TO_UTF8(*APIName));
}

bool USteamAchievementsSubsystem::GetAchievement(const FString& APIName) const
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	bool bUnlocked = false;
	SteamUserStats()->GetAchievement(TCHAR_TO_UTF8(*APIName), &bUnlocked);
	return bUnlocked;
}

bool USteamAchievementsSubsystem::ClearAchievement(const FString& APIName)
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	return SteamUserStats()->ClearAchievement(TCHAR_TO_UTF8(*APIName));
}

FSteamAchievement USteamAchievementsSubsystem::GetAchievementByIndex(int32 Index) const
{
	FSteamAchievement Out;
	if (!IsSteamReady(this)) return Out;

	const char* Name = SteamUserStats()->GetAchievementName(Index);
	if (!Name) return Out;

	Out.APIName     = UTF8_TO_TCHAR(Name);
	Out.DisplayName = UTF8_TO_TCHAR(
		SteamUserStats()->GetAchievementDisplayAttribute(Name, "name"));
	Out.Description = UTF8_TO_TCHAR(
		SteamUserStats()->GetAchievementDisplayAttribute(Name, "desc"));

	bool bUnlocked = false;
	uint32 UnlockTime = 0;
	SteamUserStats()->GetAchievementAndUnlockTime(Name, &bUnlocked, &UnlockTime);
	Out.bUnlocked   = bUnlocked;
	Out.UnlockTime  = FDateTime::FromUnixTimestamp(UnlockTime);
	return Out;
}

int32 USteamAchievementsSubsystem::GetNumAchievements() const
{
	if (!IsSteamReady(this)) return 0;
	return static_cast<int32>(SteamUserStats()->GetNumAchievements());
}

void USteamAchievementsSubsystem::IndicateAchievementProgress(
	const FString& APIName, int32 CurrentProgress, int32 MaxProgress)
{
	if (!IsSteamReady(this)) return;
	SteamUserStats()->IndicateAchievementProgress(
		TCHAR_TO_UTF8(*APIName),
		static_cast<uint32>(CurrentProgress),
		static_cast<uint32>(MaxProgress));
}

float USteamAchievementsSubsystem::GetAchievementGlobalUnlockPercent(const FString& APIName) const
{
	if (!IsSteamReady(this)) return 0.f;
	float Percent = 0.f;
	SteamUserStats()->GetAchievementAchievedPercent(TCHAR_TO_UTF8(*APIName), &Percent);
	return Percent;
}

// ---------------------------------------------------------------------------
// Stats — integer
// ---------------------------------------------------------------------------

int32 USteamAchievementsSubsystem::GetStatInt(const FString& Name) const
{
	if (!bStatsValid || !IsSteamReady(this)) return 0;
	int32 Val = 0;
	SteamUserStats()->GetStat(TCHAR_TO_UTF8(*Name), &Val);
	return Val;
}

bool USteamAchievementsSubsystem::SetStatInt(const FString& Name, int32 Value)
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	return SteamUserStats()->SetStat(TCHAR_TO_UTF8(*Name), Value);
}

// ---------------------------------------------------------------------------
// Stats — float
// ---------------------------------------------------------------------------

float USteamAchievementsSubsystem::GetStatFloat(const FString& Name) const
{
	if (!bStatsValid || !IsSteamReady(this)) return 0.f;
	float Val = 0.f;
	SteamUserStats()->GetStat(TCHAR_TO_UTF8(*Name), &Val);
	return Val;
}

bool USteamAchievementsSubsystem::SetStatFloat(const FString& Name, float Value)
{
	if (!bStatsValid || !IsSteamReady(this)) return false;
	return SteamUserStats()->SetStat(TCHAR_TO_UTF8(*Name), Value);
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamAchievementsSubsystem::HandleUserStatsReceived(UserStatsReceived_t* Param)
{
	// Only care about our own app
	if (Param->m_nGameID != SteamUtils()->GetAppID()) return;

	bStatsValid = (Param->m_eResult == k_EResultOK);
	const bool bOK = bStatsValid;
	AsyncTask(ENamedThreads::GameThread, [this, bOK]()
	{
		OnStatsReceived.Broadcast(bOK);
	});
}

void USteamAchievementsSubsystem::HandleUserStatsStored(UserStatsStored_t* Param)
{
	if (Param->m_nGameID != SteamUtils()->GetAppID()) return;
	const bool bOK = (Param->m_eResult == k_EResultOK);
	AsyncTask(ENamedThreads::GameThread, [this, bOK]()
	{
		OnStatsStored.Broadcast(bOK);
	});
}

void USteamAchievementsSubsystem::HandleAchievementStored(UserAchievementStored_t* Param)
{
	const FString AchName(UTF8_TO_TCHAR(Param->m_rgchAchievementName));
	AsyncTask(ENamedThreads::GameThread, [this, AchName]()
	{
		OnAchievementUnlocked.Broadcast(AchName);
	});
}
