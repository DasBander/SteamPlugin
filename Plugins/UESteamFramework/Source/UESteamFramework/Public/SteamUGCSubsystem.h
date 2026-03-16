// Copyright Marc Fraedrich. All Rights Reserved.
// SteamUGCSubsystem.h
// Steam Workshop / User-Generated Content (ISteamUGC).
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

#include "SteamUGCSubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamUGCOnQueryComplete,
	bool, bSuccess, TArray<FSteamUGCItem>, Items);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamUGCOnDownloadComplete,
	int64, PublishedFileID, bool, bSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamUGCOnSubmitComplete,
	int64, PublishedFileID, bool, bSuccess);

/**
 * USteamUGCSubsystem
 *
 * Provides access to the Steam Workshop (ISteamUGC).
 * Supports querying/browsing items, subscribing/unsubscribing, checking
 * install state, and submitting new or updated items.
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamUGCSubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamUGCSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Querying items
	// -----------------------------------------------------------------------

	/**
	 * Queries the Workshop for items by type, sorted by vote.
	 * Results are delivered via OnQueryComplete.
	 * @param MaxResults  1–50.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|UGC|Query")
	void QueryAllItems(EUGCMatchingType MatchingType, int32 MaxResults = 20);

	/**
	 * Queries Workshop items the local user has subscribed to.
	 * Results are delivered via OnQueryComplete.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|UGC|Query")
	void QuerySubscribedItems(EUGCMatchingType MatchingType);

	/**
	 * Queries a specific item by published file ID.
	 * Result is delivered via OnQueryComplete (1-element array on success).
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|UGC|Query")
	void QueryItemByID(int64 PublishedFileID);

	// -----------------------------------------------------------------------
	// Subscriptions
	// -----------------------------------------------------------------------

	/** Subscribe to a Workshop item.  Steam will download it in the background. */
	UFUNCTION(BlueprintCallable, Category = "Steam|UGC|Subscriptions")
	void SubscribeItem(int64 PublishedFileID);

	/** Unsubscribe from a Workshop item and remove it from disk. */
	UFUNCTION(BlueprintCallable, Category = "Steam|UGC|Subscriptions")
	void UnsubscribeItem(int64 PublishedFileID);

	/** Returns the download/install state of a subscribed item. */
	UFUNCTION(BlueprintPure, Category = "Steam|UGC|Subscriptions")
	bool IsItemInstalled(int64 PublishedFileID, FString& OutInstallPath) const;

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	/** Fires after any QueryAllItems / QuerySubscribedItems / QueryItemByID call. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|UGC|Callbacks")
	FSteamUGCOnQueryComplete OnQueryComplete;

	/** Fires when an item download finishes (subscribe triggers a background download). */
	UPROPERTY(BlueprintAssignable, Category = "Steam|UGC|Callbacks")
	FSteamUGCOnDownloadComplete OnDownloadComplete;

private:
	STEAM_CALLBACK(USteamUGCSubsystem, HandleDownloadItemResult, DownloadItemResult_t);
};
