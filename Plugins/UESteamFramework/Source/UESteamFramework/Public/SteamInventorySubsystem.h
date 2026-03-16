// Copyright Marc Fraedrich. All Rights Reserved.
// SteamInventorySubsystem.h
// Steam Inventory / Economy items.
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

#include "SteamInventorySubsystem.generated.h"

// ---------------------------------------------------------------------------
// Delegates
// ---------------------------------------------------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamInvOnItemsUpdated, TArray<FSteamInventoryItem>, Items);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSteamInvOnDefinitionsUpdated);

/**
 * USteamInventorySubsystem
 *
 * Provides access to the Steam Inventory Service (ISteamInventory).
 * Item definitions are loaded once at startup; instance data (what the player
 * actually owns) must be requested explicitly with GetAllItems().
 *
 * Access in Blueprint:
 *   GetGameInstance → GetSubsystem(SteamInventorySubsystem)
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// -----------------------------------------------------------------------
	// Item instances (what the player owns)
	// -----------------------------------------------------------------------

	/**
	 * Requests a list of all items owned by the local user.
	 * Results are delivered via OnItemsUpdated.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Inventory")
	void GetAllItems();

	/**
	 * Returns the items from the last successful GetAllItems() call.
	 * Call GetAllItems() first to refresh.
	 */
	UFUNCTION(BlueprintPure, Category = "Steam|Inventory")
	TArray<FSteamInventoryItem> GetCachedItems() const { return CachedItems; }

	/**
	 * Consumes (decrements quantity) an owned item instance.
	 * @param InstanceID  The item instance to consume.
	 * @param Quantity    Number of uses to consume (1–N).
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Inventory")
	void ConsumeItem(int64 InstanceID, int32 Quantity = 1);

	/**
	 * Grants a promotional item if the user is eligible.
	 * @param DefinitionID  The item definition to grant.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Inventory")
	void AddPromoItem(int32 DefinitionID);

	/**
	 * Triggers a randomised item drop ("playtime drop").
	 * Steam decides whether to actually grant an item based on drop rules.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam|Inventory")
	void TriggerItemDrop(int32 DropListDefinitionID);

	// -----------------------------------------------------------------------
	// Item definitions (catalogue)
	// -----------------------------------------------------------------------

	/** Returns all known item definition IDs for this app. */
	UFUNCTION(BlueprintPure, Category = "Steam|Inventory|Definitions")
	TArray<int32> GetItemDefinitionIDs() const;

	/**
	 * Returns a named property for an item definition.
	 * Common property names: "name", "description", "price_category", "icon_url".
	 */
	UFUNCTION(BlueprintPure, Category = "Steam|Inventory|Definitions")
	FString GetItemDefinitionProperty(int32 DefinitionID, const FString& PropertyName) const;

	// -----------------------------------------------------------------------
	// Callbacks
	// -----------------------------------------------------------------------

	/** Fires after GetAllItems() or ConsumeItem() returns results. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Inventory|Callbacks")
	FSteamInvOnItemsUpdated OnItemsUpdated;

	/** Fires when the item definitions catalogue is (re)loaded from Steam. */
	UPROPERTY(BlueprintAssignable, Category = "Steam|Inventory|Callbacks")
	FSteamInvOnDefinitionsUpdated OnDefinitionsUpdated;

private:
	TArray<FSteamInventoryItem> CachedItems;

	STEAM_CALLBACK(USteamInventorySubsystem, HandleInventoryResultReady,  SteamInventoryResultReady_t);
	STEAM_CALLBACK(USteamInventorySubsystem, HandleInventoryFullUpdate,   SteamInventoryFullUpdate_t);
	STEAM_CALLBACK(USteamInventorySubsystem, HandleInventoryDefinitionUpdate, SteamInventoryDefinitionUpdate_t);

	void ParseResultHandle(int32 ResultHandle);
};
