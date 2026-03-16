# UE Steam Framework — Documentation

**Version:** 2.0 · **Engine:** Unreal Engine 5.6 · **Author:** Marc Fraedrich

---

## Overview

UE Steam Framework exposes the full Steamworks SDK through **Unreal Engine Game Instance Subsystems**.  Each domain of the Steam API is a separate subsystem you can query in Blueprint or C++ without needing a custom Game Instance class.

### Why Subsystems?

| Old approach (v1) | New approach (v2) |
|---|---|
| Custom `UUESFGameInstance` required | Any `UGameInstance` works |
| `USteamFrameworkMain` (plain UObject, `AddToRoot`) | `UGameInstanceSubsystem` — lifetime managed by UE |
| Lobby + friends mixed in one class | One subsystem per domain |
| Manual `NewObject` + null-checks in Blueprints | Auto-created, always valid |

---

## Architecture

```
UGameInstance
  ├── USteamCoreSubsystem       — init/shutdown, RunCallbacks tick, user info, rich presence
  ├── USteamFriendsSubsystem    — friends list, avatars, Steam overlay
  ├── USteamLobbySubsystem      — lobby CRUD, search, metadata, chat, invites
  ├── USteamAchievementsSubsystem — stats + achievements + leaderboards
  ├── USteamInventorySubsystem  — Steam Inventory / item economy
  ├── USteamRemoteStorageSubsystem — Steam Cloud saves
  ├── USteamUGCSubsystem        — Workshop / User-Generated Content
  └── USteamNetworkingSubsystem — P2P networking (ISteamNetworking)
```

All subsystems depend on `USteamCoreSubsystem`, which is guaranteed to initialize first.  `SteamAPI_RunCallbacks()` is called once per frame by `USteamCoreSubsystem`'s tick, so every other subsystem receives its callbacks automatically.

---

## Setup

### 1. Project Settings

Open **Edit → Project Settings → Plugins → Steam Framework** and set:

| Setting | Description |
|---|---|
| App ID | Your Steam App ID (480 = Spacewar for development) |
| Enforce App Ownership Check | Exits with a dialog if the running App ID doesn't match |
| Product Name / Game Description | Shown in the server browser |
| Server Version | Reported to Steam backend |

### 2. Engine Config (`DefaultEngine.ini`)

The plugin requires Steam to be the default Online Subsystem:

```ini
[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480
```

### 3. `steam_appid.txt`

Place a file called `steam_appid.txt` in the same folder as your `.exe` (or the project root during Play-In-Editor) containing just your App ID, e.g.:

```
480
```

Steam requires this to be present when launching outside of Steam.

### 4. No custom Game Instance needed

Unlike v1, you do **not** need to set a custom Game Instance class.  All subsystems are auto-created by Unreal's subsystem framework.

---

## Quick Start — Blueprint

### Getting a subsystem

```
Get Game Instance → Get Subsystem (class = Steam Core Subsystem)
```

Use the same pattern for any subsystem.

### Checking Steam is running

```
SteamCoreSubsystem → Is Steam Initialized
```

Always guard Steam calls behind this check in the Editor, where Steam may not be running.

---

## Subsystem Reference

### USteamCoreSubsystem

The entry point.  Drives the Steam callback pump.

| Function | Category | Description |
|---|---|---|
| `IsSteamInitialized` | Core | Returns true after `SteamAPI_Init()` succeeded |
| `GetAppID` | Core | Running App ID |
| `GetBuildID` | Core | Steam build counter |
| `GetCurrentGameLanguage` | Core | e.g. `"english"` |
| `GetAvailableGameLanguages` | Core | Comma-separated list |
| `IsSubscribed` | Core | User owns the app |
| `IsVACBanned` | Core | User has a VAC ban |
| `GetLocalUserSteamID` | User | Local player's FSteamID |
| `GetLocalPersonaName` | User | Local player's display name |
| `GetAvatar(SteamID, bLarge)` | User | Returns `UTexture2D*` (184×184 or 64×64) |
| `SetRichPresence(Key, Value)` | RichPresence | Set a rich-presence key |
| `ClearRichPresence` | RichPresence | Remove all keys |
| `GetFriendRichPresence(SteamID, Key)` | RichPresence | Read a friend's key |

**Delegates:**

| Delegate | Parameters | When fired |
|---|---|---|
| `OnSteamShutdown` | — | Steam requests the game to exit |
| `OnGameOverlayActivated` | `bool bActive` | Overlay opens / closes |

---

### USteamFriendsSubsystem

| Function | Description |
|---|---|
| `GetFriendsList(bOnlineOnly)` | `TArray<FSteamFriend>` — all or online-only friends |
| `GetFriendInfo(SteamID)` | Single `FSteamFriend` |
| `GetPersonaName(SteamID)` | Display name for any user |
| `GetPersonaState(SteamID)` | `ESteamPersonaState` |
| `HasFriend(SteamID)` | Is this person a friend? |
| `GetFriendAvatar(SteamID, bLarge)` | `UTexture2D*` |
| `ActivateOverlay(Dialog)` | Open overlay (`"friends"`, `"achievements"`, …) |
| `ActivateOverlayToUser(Dialog, SteamID)` | Open overlay focused on a user |
| `ActivateOverlayToWebPage(URL)` | Open overlay browser |
| `ActivateOverlayToStore(AppID)` | Open store page |
| `InviteFriendToGame(SteamID, ConnectString)` | Send a game invite |
| `RequestPersonaData(SteamID)` | Trigger async refresh |
| `GetFriendRichPresenceValue(SteamID, Key)` | Read a rich-presence value |

**Delegates:**

| Delegate | Parameters |
|---|---|
| `OnPersonaStateChanged` | `FSteamID` |
| `OnAvatarLoaded` | `FSteamID` |
| `OnGameInviteReceived` | `FSteamID InviterSteamID` |

---

### USteamLobbySubsystem

#### Lifecycle

```
CreateLobby(Params) → OnLobbyCreated(FLobbyCreateResult)
JoinLobby(LobbyID)  → OnLobbyEntered(FSteamID LobbyID)
LeaveLobby()        → OnLobbyLeft()
```

#### State

```
IsInLobby()         → bool
GetCurrentLobbyID() → FSteamID
IsOwner()           → bool
GetOwner()          → FSteamID
GetMemberCount()    → int32
GetMembers()        → TArray<FSteamFriend>
```

#### Metadata

```
GetLobbyData(Key)              → FString
SetLobbyData(Key, Value)       → bool   (owner only)
GetMemberData(SteamID, Key)    → FString
SetMemberData(Key, Value)      — local user only
```

#### Search

```
// Optional filters (call before RequestLobbyList):
AddStringFilter(Key, Value, Comparison)
AddNumericalFilter(Key, Value, Comparison)
AddSlotsAvailableFilter(MinOpenSlots)
SetDistanceFilter(Filter)
SetResultCountLimit(Max)

RequestLobbyList() → OnSearchComplete(TArray<FLobbySearchResult>)
```

#### Settings (owner only)

```
SetLobbyVisibility(ELobbyVisibility)
SetJoinable(bool)
SetMemberLimit(int32)
```

#### Chat & Invites

```
SendChatMessage(Message) → bool
InviteFriend(FriendSteamID) → bool
```

**All Delegates:**

`OnLobbyCreated`, `OnLobbyEntered`, `OnLobbyLeft`, `OnLobbyDataUpdated`,
`OnMemberJoined`, `OnMemberLeft`, `OnChatMessageReceived`, `OnInviteReceived`, `OnSearchComplete`

---

### USteamAchievementsSubsystem

Stats are automatically requested on subsystem startup.  Wait for `OnStatsReceived` before reading or writing stats.

| Function | Description |
|---|---|
| `RequestCurrentStats` | Async fetch from Steam |
| `StoreStats` | Upload accumulated changes |
| `ResetAllStats(bAchievementsToo)` | ⚠ Permanent — wipes player progress |
| `SetAchievement(APIName)` | Unlock an achievement |
| `GetAchievement(APIName)` | Is it unlocked? |
| `ClearAchievement(APIName)` | Re-lock an achievement |
| `GetAchievementByIndex(Index)` | `FSteamAchievement` (name, description, unlock time) |
| `GetNumAchievements` | Total achievements for this app |
| `IndicateAchievementProgress(Name, Current, Max)` | Show progress toast without unlocking |
| `GetAchievementGlobalUnlockPercent(Name)` | 0.0–100.0 |
| `GetStatInt(Name)` / `SetStatInt(Name, Value)` | Integer stat |
| `GetStatFloat(Name)` / `SetStatFloat(Name, Value)` | Float stat |

**Delegates:** `OnStatsReceived(bool)`, `OnStatsStored(bool)`, `OnAchievementUnlocked(FString APIName)`

---

### USteamInventorySubsystem

| Function | Description |
|---|---|
| `GetAllItems` | Async fetch of all owned items → `OnItemsUpdated` |
| `GetCachedItems` | Returns last-fetched `TArray<FSteamInventoryItem>` |
| `ConsumeItem(InstanceID, Quantity)` | Decrement item stack |
| `AddPromoItem(DefinitionID)` | Grant a promotional item |
| `TriggerItemDrop(DropListID)` | Request a random playtime drop |
| `GetItemDefinitionIDs` | All defined item IDs |
| `GetItemDefinitionProperty(DefID, PropertyName)` | e.g. `"name"`, `"description"`, `"icon_url"` |

**Delegates:** `OnItemsUpdated(TArray<FSteamInventoryItem>)`, `OnDefinitionsUpdated()`

---

### USteamRemoteStorageSubsystem

| Function | Description |
|---|---|
| `IsCloudEnabledForApp` / `IsCloudEnabledForAccount` | Cloud availability |
| `GetQuota(OutTotal, OutAvailable)` | Quota in bytes |
| `WriteFile(FileName, Data)` | Write raw bytes |
| `ReadFile(FileName, OutData)` | Read raw bytes |
| `DeleteFile(FileName)` | Delete |
| `FileExists(FileName)` | Exists? |
| `GetFileSize(FileName)` | Bytes, or -1 |
| `GetFileList` | `TArray<FSteamCloudFile>` |
| `WriteString(FileName, Content)` | UTF-8 string helper |
| `ReadString(FileName, OutContent)` | UTF-8 string helper |

---

### USteamUGCSubsystem

| Function | Description |
|---|---|
| `QueryAllItems(MatchingType, MaxResults)` | Browse Workshop → `OnQueryComplete` |
| `QuerySubscribedItems(MatchingType)` | Items the local user is subscribed to |
| `QueryItemByID(PublishedFileID)` | Fetch a single item's details |
| `SubscribeItem(PublishedFileID)` | Subscribe + auto-download |
| `UnsubscribeItem(PublishedFileID)` | Unsubscribe + remove |
| `IsItemInstalled(PublishedFileID, OutPath)` | Check install state |

**Delegates:** `OnQueryComplete(bool, TArray<FSteamUGCItem>)`, `OnDownloadComplete(int64, bool)`

---

### USteamNetworkingSubsystem

ISteamNetworking legacy P2P (channel-based, Steam relayed).

| Function | Description |
|---|---|
| `SendPacket(RemoteID, Channel, Data, SendType)` | Send raw bytes |
| `SendString(RemoteID, Channel, Message, SendType)` | UTF-8 string helper |
| `AcceptP2PSession(RemoteID)` | Accept a pending session |
| `CloseP2PSession(RemoteID)` | Close and flush |
| `CloseP2PChannel(RemoteID, Channel)` | Close one channel only |
| `GetP2PSessionState(...)` | Connection diagnostics |

Set `ActiveChannels` (default `{0}`) to control which channels are polled each tick.

**Delegates:** `OnSessionRequest(FSteamID, Channel)`, `OnSessionFailed(FSteamID, Channel, ErrorCode)`, `OnPacketReceived(FSteamID, Channel, TArray<uint8>)`

---

## Shared Types (`SteamTypes.h`)

| Type | Description |
|---|---|
| `FSteamID` | 64-bit Steam ID wrapper. `.Value` is `int64`; use `.AsUInt64()` for the raw value. |
| `FSteamFriend` | SteamID + PersonaName + PersonaState + bIsInGame |
| `FLobbyCreateParams` | LobbyName, MaxPlayers, Password (hashed), Visibility |
| `FLobbyCreateResult` | LobbyID + ELobbyCreateResult |
| `FLobbySearchResult` | LobbyID, LobbyName, MemberCount, MaxMembers, bHasPassword |
| `FSteamAchievement` | APIName, DisplayName, Description, bUnlocked, UnlockTime |
| `FSteamInventoryItem` | InstanceID, DefinitionID, Quantity |
| `FSteamItemDef` | DefinitionID, Name, Description, IconURL |
| `FSteamCloudFile` | FileName, FileSizeBytes, Timestamp |
| `FSteamUGCItem` | PublishedFileID, Title, Description, OwnerSteamID, Score, VotesUp, VotesDown, bIsSubscribed, bIsInstalled, InstallPath |
| `ESteamPersonaState` | Offline / Online / Busy / Away / Snooze / LookingToTrade / LookingToPlay |
| `ELobbyVisibility` | Private / FriendsOnly / Public / Invisible |
| `ELobbyCreateResult` | Success / Failed / Timeout / NoConnection |
| `ELobbyComparison` | Comparison operators for lobby search filters |
| `ELobbyDistanceFilter` | Close / Default / Far / Worldwide |
| `EUGCMatchingType` | Items, Collections, Artwork, Videos, Screenshots, … |
| `ESteamP2PSendType` | Unreliable / UnreliableNoDelay / Reliable / ReliableWithBuffering |

---

## C++ Usage Examples

### Getting the lobby subsystem

```cpp
#include "SteamLobbySubsystem.h"

if (UGameInstance* GI = GetGameInstance())
{
    USteamLobbySubsystem* Lobby = GI->GetSubsystem<USteamLobbySubsystem>();
    if (Lobby)
    {
        FLobbyCreateParams Params;
        Params.LobbyName  = TEXT("My Game");
        Params.MaxPlayers = 4;
        Params.Visibility = ELobbyVisibility::Public;
        Lobby->OnLobbyCreated.AddDynamic(this, &AMyGameMode::OnLobbyCreated);
        Lobby->CreateLobby(Params);
    }
}
```

### Unlocking an achievement

```cpp
#include "SteamAchievementsSubsystem.h"

USteamAchievementsSubsystem* Ach = GetGameInstance()->GetSubsystem<USteamAchievementsSubsystem>();
if (Ach)
{
    Ach->SetAchievement(TEXT("ACH_WIN_ONE_GAME"));
    Ach->StoreStats();
}
```

### Sending a P2P packet

```cpp
#include "SteamNetworkingSubsystem.h"

USteamNetworkingSubsystem* Net = GetGameInstance()->GetSubsystem<USteamNetworkingSubsystem>();
if (Net)
{
    TArray<uint8> Payload = { 0x01, 0x02, 0x03 };
    Net->SendPacket(RemoteSteamID, /*Channel=*/0, Payload, ESteamP2PSendType::Reliable);
}
```

---

## Migration from v1

| v1 | v2 |
|---|---|
| `UUESFGameInstance` | Delete — no longer needed |
| `USteamFrameworkMain` | `USteamLobbySubsystem` |
| `USteamFrameworkHelper::GetSteamInterface()` | `GetGameInstance()->GetSubsystem<USteamLobbySubsystem>()` |
| `USteamFrameworkHelper::GetFriendsList()` | `USteamFriendsSubsystem::GetFriendsList()` |
| `USteamFrameworkHelper::GetSteamAvatar()` | `USteamFriendsSubsystem::GetFriendAvatar()` |
| `USteamFrameworkHelper::GetUsername()` | `USteamFriendsSubsystem::GetPersonaName()` |
| `USteamFrameworkHelper::GetUserSteamID()` | `USteamCoreSubsystem::GetLocalUserSteamID()` |
| `FSteamID::SteamID` (uint64 field) | `FSteamID::Value` (int64) — use `.AsUInt64()` |
| `steamsdk_lambda_callresults.h` | Internal `TLambdaCallResult<P>` in `SteamLobbySubsystem.cpp` |
| `FrameworkDef.h` | `SteamTypes.h` |

---

## Build Notes

`UESteamFramework.Build.cs` uses `AddEngineThirdPartyPrivateStaticDependencies(Target, "Steamworks")` — the engine provides the correct Steamworks SDK version for the engine release automatically; no SDK version numbers need to be hard-coded.

The module type is **Runtime** (was `Developer` in v1), so the plugin loads in packaged builds.

---

## License

Copyright © Marc Fraedrich.
See the root `LICENSE` file for terms.
