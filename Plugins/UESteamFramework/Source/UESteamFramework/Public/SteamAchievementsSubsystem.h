// Copyright Marc Fraedrich. All Rights Reserved.
// SteamAchievementsSubsystem.h
// Stats, achievements, and leaderboards via ISteamUserStats.
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

#include "SteamAchievementsSubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamAchOnStatsReceived,   bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamAchOnStatsStored,     bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamAchOnAchievementUnlocked, FString, APIName);

/**
 * USteamAchievementsSubsystem
 *
 * Manages Steam Stats and Achievements for the local user.
 * Always call RequestCurrentStats() at game start and wait for OnStatsReceived
 * before reading or writing any stats.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamAchievementsSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamAchievementsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Stats synchronisation
	// -----------------------------------------------------------------------

	/**
	 * Requests stats and achievements from Steam for the local user.
	 * This is asynchronous — listen to OnStatsReceived before reading/writing.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	void RequestCurrentStats();

	/**
	 * Uploads accumulated stat changes to Steam servers.
	 * Listen to OnStatsStored for the result.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	bool StoreStats();

	/**
	 * Resets all stats and optionally clears all achievements.
	 * Use with caution — this permanently removes player progress.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	bool ResetAllStats(bool bAchievementsToo = false);

	// -----------------------------------------------------------------------
	// Achievements
	// -----------------------------------------------------------------------

	/** Unlocks the achievement.  Call StoreStats() afterwards. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	bool SetAchievement(const FString& APIName);

	/** Returns true if the local user has unlocked the achievement. */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements")
	bool GetAchievement(const FString& APIName) const;

	/** Clears (re-locks) an achievement.  Call StoreStats() afterwards. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	bool ClearAchievement(const FString& APIName);

	/**
	 * Returns full metadata for an achievement by its 0-based index.
	 * Use GetNumAchievements() to iterate all achievements.
	 */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements")
	FSteamAchievement GetAchievementByIndex(int32 Index) const;

	/** Returns the total number of achievements defined for this app. */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements")
	int32 GetNumAchievements() const;

	/**
	 * Shows the unlock notification UI for an achievement without actually
	 * unlocking it.  Useful for testing.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements")
	void IndicateAchievementProgress(const FString& APIName, int32 CurrentProgress, int32 MaxProgress);

	/** Returns the global unlock percentage (0.0–100.0) for an achievement. */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements")
	float GetAchievementGlobalUnlockPercent(const FString& APIName) const;

	// -----------------------------------------------------------------------
	// Stats — integer
	// -----------------------------------------------------------------------

	/** Returns an integer stat.  Returns 0 if the stat doesn't exist. */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements|Stats")
	int32 GetStatInt(const FString& Name) const;

	/** Sets an integer stat.  Call StoreStats() to persist. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements|Stats")
	bool SetStatInt(const FString& Name, int32 Value);

	// -----------------------------------------------------------------------
	// Stats — float
	// -----------------------------------------------------------------------

	/** Returns a float stat.  Returns 0.0 if the stat doesn't exist. */
	UFUNCTION(BlueprintPure, Category = "Steam|Achievements|Stats")
	float GetStatFloat(const FString& Name) const;

	/** Sets a float stat.  Call StoreStats() to persist. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Achievements|Stats")
	bool SetStatFloat(const FString& Name, float Value);

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	UPROPERTY(BlueprintAssignable, Category = "Steam|Achievements|Callbacks")
	FSteamAchOnStatsReceived OnStatsReceived;

	UPROPERTY(BlueprintAssignable, Category = "Steam|Achievements|Callbacks")
	FSteamAchOnStatsStored OnStatsStored;

	/** Fires when an achievement is actually unlocked and stored on Steam. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Achievements|Callbacks")
	FSteamAchOnAchievementUnlocked OnAchievementUnlocked;

private:
	bool bStatsRequested = false;
	bool bStatsValid     = false;

	STEAM_CALLBACK(USteamAchievementsSubsystem, HandleUserStatsReceived,     UserStatsReceived_t);
	STEAM_CALLBACK(USteamAchievementsSubsystem, HandleUserStatsStored,       UserStatsStored_t);
	STEAM_CALLBACK(USteamAchievementsSubsystem, HandleAchievementStored,     UserAchievementStored_t);
};
