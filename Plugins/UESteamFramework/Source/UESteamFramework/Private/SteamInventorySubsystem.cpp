// Copyright Marc Fraedrich. All Rights Reserved.

#include "SteamInventorySubsystem.h"
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

void USteamInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<USteamCoreSubsystem>();
	Super::Initialize(Collection);
}

void USteamInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

// ---------------------------------------------------------------------------
// Items
// ---------------------------------------------------------------------------

void USteamInventorySubsystem::GetAllItems()
{
	if (!IsSteamReady(this)) return;
	SteamInventoryResult_t Result;
	SteamInventory()->GetAllItems(&Result);
	// Result will be consumed by HandleInventoryResultReady callback
}

void USteamInventorySubsystem::ConsumeItem(int64 InstanceID, int32 Quantity)
{
	if (!IsSteamReady(this)) return;
	SteamInventoryResult_t Result;
	SteamInventory()->ConsumeItem(&Result,
		static_cast<SteamItemInstanceID_t>(InstanceID),
		static_cast<uint32>(Quantity));
}

void USteamInventorySubsystem::AddPromoItem(int32 DefinitionID)
{
	if (!IsSteamReady(this)) return;
	SteamInventoryResult_t Result;
	SteamInventory()->AddPromoItem(&Result, static_cast<SteamItemDef_t>(DefinitionID));
}

void USteamInventorySubsystem::TriggerItemDrop(int32 DropListDefinitionID)
{
	if (!IsSteamReady(this)) return;
	SteamInventoryResult_t Result;
	SteamInventory()->TriggerItemDrop(&Result, static_cast<SteamItemDef_t>(DropListDefinitionID));
}

// ---------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------

TArray<int32> USteamInventorySubsystem::GetItemDefinitionIDs() const
{
	TArray<int32> Out;
	if (!IsSteamReady(this)) return Out;

	uint32 Count = 0;
	if (!SteamInventory()->GetItemDefinitionIDs(nullptr, &Count) || Count == 0)
	{
		return Out;
	}

	TArray<SteamItemDef_t> Defs;
	Defs.SetNum(Count);
	if (SteamInventory()->GetItemDefinitionIDs(Defs.GetData(), &Count))
	{
		for (SteamItemDef_t D : Defs)
		{
			Out.Add(static_cast<int32>(D));
		}
	}
	return Out;
}

FString USteamInventorySubsystem::GetItemDefinitionProperty(int32 DefinitionID, const FString& PropertyName) const
{
	if (!IsSteamReady(this)) return FString();

	uint32 BufLen = 0;
	const SteamItemDef_t Def = static_cast<SteamItemDef_t>(DefinitionID);
	const char* PropCStr = TCHAR_TO_UTF8(*PropertyName);

	SteamInventory()->GetItemDefinitionProperty(Def, PropCStr, nullptr, &BufLen);
	if (BufLen == 0) return FString();

	TArray<char> Buf;
	Buf.SetNum(BufLen);
	SteamInventory()->GetItemDefinitionProperty(Def, PropCStr, Buf.GetData(), &BufLen);
	return UTF8_TO_TCHAR(Buf.GetData());
}

// ---------------------------------------------------------------------------
// Result helper
// ---------------------------------------------------------------------------

void USteamInventorySubsystem::ParseResultHandle(int32 ResultHandle)
{
	const SteamInventoryResult_t Handle = static_cast<SteamInventoryResult_t>(ResultHandle);
	if (Handle == k_SteamInventoryResultInvalid) return;

	uint32 Count = 0;
	SteamInventory()->GetResultItems(Handle, nullptr, &Count);

	TArray<SteamItemDetails_t> Details;
	Details.SetNum(Count);

	TArray<FSteamInventoryItem> Items;
	if (SteamInventory()->GetResultItems(Handle, Details.GetData(), &Count))
	{
		for (const SteamItemDetails_t& D : Details)
		{
			FSteamInventoryItem I;
			I.InstanceID  = static_cast<int64>(D.m_itemId);
			I.DefinitionID = static_cast<int32>(D.m_iDefinition);
			I.Quantity     = static_cast<int32>(D.m_unQuantity);
			Items.Add(I);
		}
	}

	SteamInventory()->DestroyResult(Handle);

	CachedItems = Items;
	AsyncTask(ENamedThreads::GameThread, [this, Items]()
	{
		OnItemsUpdated.Broadcast(Items);
	});
}

// ---------------------------------------------------------------------------
// Steam callbacks
// ---------------------------------------------------------------------------

void USteamInventorySubsystem::HandleInventoryResultReady(SteamInventoryResultReady_t* Param)
{
	if (Param->m_result == k_EResultOK)
	{
		ParseResultHandle(static_cast<int32>(Param->m_handle));
	}
}

void USteamInventorySubsystem::HandleInventoryFullUpdate(SteamInventoryFullUpdate_t* Param)
{
	ParseResultHandle(static_cast<int32>(Param->m_handle));
}

void USteamInventorySubsystem::HandleInventoryDefinitionUpdate(SteamInventoryDefinitionUpdate_t* /*Param*/)
{
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		OnDefinitionsUpdated.Broadcast();
	});
}
