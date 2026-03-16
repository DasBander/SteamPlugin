// Copyright Marc Fraedrich. All Rights Reserved.
// SteamTypes.h — Shared UE-facing types for the Steam Framework.
// No Steamworks SDK headers here; keep this includable from any Blueprint-visible code.
#pragma once

#include "CoreMinimal.h"
#include "Misc/SecureHash.h"
#include "SteamTypes.generated.h"

// ---------------------------------------------------------------------------
// Steam ID wrapper
// ---------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamID
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam")
	int64 Value = 0;

	FSteamID() = default;
	explicit FSteamID(uint64 InValue) : Value(static_cast<int64>(InValue)) {}

	uint64 AsUInt64() const { return static_cast<uint64>(Value); }
	FString ToString()  const { return FString::Printf(TEXT("%llu"), AsUInt64()); }
	bool IsValid()      const { return Value != 0; }

	bool operator==(const FSteamID& Other) const { return Value == Other.Value; }
	bool operator!=(const FSteamID& Other) const { return Value != Other.Value; }
};

// ---------------------------------------------------------------------------
// Lobby enums
// ---------------------------------------------------------------------------

UENUM(BlueprintType)
enum class ELobbyVisibility : uint8
{
	Private     UMETA(DisplayName = "Private"),
	FriendsOnly UMETA(DisplayName = "Friends Only"),
	Public      UMETA(DisplayName = "Public"),
	Invisible   UMETA(DisplayName = "Invisible"),
};

UENUM(BlueprintType)
enum class ELobbyCreateResult : uint8
{
	Success      UMETA(DisplayName = "Success"),
	Failed       UMETA(DisplayName = "Failed"),
	Timeout      UMETA(DisplayName = "Timeout"),
	NoConnection UMETA(DisplayName = "No Connection"),
};

UENUM(BlueprintType)
enum class ELobbyComparison : uint8
{
	EqualToOrLessThan    UMETA(DisplayName = "<= Value"),
	LessThan             UMETA(DisplayName = "< Value"),
	Equal                UMETA(DisplayName = "= Value"),
	GreaterThan          UMETA(DisplayName = "> Value"),
	EqualToOrGreaterThan UMETA(DisplayName = ">= Value"),
	NotEqual             UMETA(DisplayName = "!= Value"),
};

UENUM(BlueprintType)
enum class ELobbyDistanceFilter : uint8
{
	Close      UMETA(DisplayName = "Close — same or nearby region"),
	Default    UMETA(DisplayName = "Default — nearby regions"),
	Far        UMETA(DisplayName = "Far — half the world away"),
	Worldwide  UMETA(DisplayName = "Worldwide"),
};

// ---------------------------------------------------------------------------
// Lobby structs
// ---------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FLobbyCreateParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam|Lobby")
	FString LobbyName = TEXT("My Lobby");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam|Lobby")
	int32 MaxPlayers = 8;

	/** Plain-text password. Stored as MD5 hash in lobby metadata. Leave empty for no password. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam|Lobby")
	FString Password;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Steam|Lobby")
	ELobbyVisibility Visibility = ELobbyVisibility::Public;

	/** Returns the MD5 hash of Password, or empty string if no password was set. */
	FString GetPasswordHash() const
	{
		return Password.IsEmpty() ? FString() : FMD5::HashAnsiString(*Password);
	}
};

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FLobbyCreateResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	FSteamID LobbyID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	ELobbyCreateResult Result = ELobbyCreateResult::NoConnection;
};

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FLobbySearchResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	FSteamID LobbyID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	FString LobbyName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	int32 MemberCount = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	int32 MaxMembers = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
	bool bHasPassword = false;
};

// ---------------------------------------------------------------------------
// Friend / User structs
// ---------------------------------------------------------------------------

UENUM(BlueprintType)
enum class ESteamPersonaState : uint8
{
	Offline        UMETA(DisplayName = "Offline"),
	Online         UMETA(DisplayName = "Online"),
	Busy           UMETA(DisplayName = "Busy"),
	Away           UMETA(DisplayName = "Away"),
	Snooze         UMETA(DisplayName = "Snooze"),
	LookingToTrade UMETA(DisplayName = "Looking to Trade"),
	LookingToPlay  UMETA(DisplayName = "Looking to Play"),
};

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamFriend
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Friends")
	FSteamID SteamID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Friends")
	FString PersonaName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Friends")
	ESteamPersonaState PersonaState = ESteamPersonaState::Offline;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Friends")
	bool bIsInGame = false;
};

// ---------------------------------------------------------------------------
// Achievement / Stats structs
// ---------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamAchievement
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Achievements")
	FString APIName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Achievements")
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Achievements")
	FString Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Achievements")
	bool bUnlocked = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Achievements")
	FDateTime UnlockTime;
};

// ---------------------------------------------------------------------------
// Inventory structs
// ---------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamItemDef
{
	GENERATED_BODY()

	/** The item definition ID (SteamItemDef_t). */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	int32 DefinitionID = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	FString Name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	FString Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	FString IconURL;
};

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamInventoryItem
{
	GENERATED_BODY()

	/** Steam item instance ID (SteamItemInstanceID_t). */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	int64 InstanceID = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	int32 DefinitionID = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Inventory")
	int32 Quantity = 0;
};

// ---------------------------------------------------------------------------
// Cloud / Remote Storage
// ---------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamCloudFile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Cloud")
	FString FileName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Cloud")
	int32 FileSizeBytes = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Cloud")
	FDateTime Timestamp;
};

// ---------------------------------------------------------------------------
// UGC / Workshop
// ---------------------------------------------------------------------------

UENUM(BlueprintType)
enum class EUGCMatchingType : uint8
{
	Items              UMETA(DisplayName = "Items"),
	Items_Mtx          UMETA(DisplayName = "Items (Microtransaction)"),
	Items_ReadyToUse   UMETA(DisplayName = "Items (Ready to Use)"),
	Collections        UMETA(DisplayName = "Collections"),
	Artwork            UMETA(DisplayName = "Artwork"),
	Videos             UMETA(DisplayName = "Videos"),
	Screenshots        UMETA(DisplayName = "Screenshots"),
	AllGuides          UMETA(DisplayName = "All Guides"),
	WebGuides          UMETA(DisplayName = "Web Guides"),
	IntegratedGuides   UMETA(DisplayName = "Integrated Guides"),
	UsableInGame       UMETA(DisplayName = "Usable in Game"),
	ControllerBindings UMETA(DisplayName = "Controller Bindings"),
	GameManagedItems   UMETA(DisplayName = "Game Managed Items"),
	All                UMETA(DisplayName = "All"),
};

USTRUCT(BlueprintType)
struct UESTEAMFRAMEWORK_API FSteamUGCItem
{
	GENERATED_BODY()

	/** The published file / workshop item ID. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	int64 PublishedFileID = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	FString Title;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	FString Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	FSteamID OwnerSteamID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	float Score = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	int32 VotesUp = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	int32 VotesDown = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	bool bIsSubscribed = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	bool bIsInstalled = false;

	/** Local install path if the item is downloaded and installed. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|UGC")
	FString InstallPath;
};

// ---------------------------------------------------------------------------
// Networking
// ---------------------------------------------------------------------------

UENUM(BlueprintType)
enum class ESteamP2PSendType : uint8
{
	Unreliable        UMETA(DisplayName = "Unreliable"),
	UnreliableNoDelay UMETA(DisplayName = "Unreliable No Delay"),
	Reliable          UMETA(DisplayName = "Reliable"),
	ReliableWithBuffering UMETA(DisplayName = "Reliable With Buffering"),
};
