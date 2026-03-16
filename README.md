# UE Steam Framework

A full Steamworks SDK integration for **Unreal Engine 5.6** built on **Game Instance Subsystems**.

---

## Features

- **Lobby system** — create, join, leave, search with filters, metadata, member management, chat, and friend invites
- **Friends** — friends list, avatars, persona state, Steam overlay control, game invites, rich presence
- **Stats & Achievements** — read/write integer and float stats, unlock/clear achievements, global unlock percentages
- **Inventory** — item instances, item definitions, consume, promo grants, playtime drops
- **Cloud Saves** — read/write files and strings to Steam Remote Storage with quota info
- **Workshop / UGC** — query, subscribe/unsubscribe, and check install state of Workshop items
- **P2P Networking** — send/receive packets over Steam's relay network on multiple channels
- **Project Settings panel** — App ID, ownership enforcement, and server config in Editor UI

---

## Requirements

| | |
|---|---|
| Engine | Unreal Engine 5.6 |
| Platform | Windows (tested), Linux/macOS should work with Steam SDK support |
| Steam | Steam must be running; `steam_appid.txt` required next to the executable |

---

## Installation

1. Copy the `Plugins/UESteamFramework` folder into your project's `Plugins/` directory.
2. Add the plugin to your `.uproject`:
   ```json
   { "Name": "UESteamFramework", "Enabled": true }
   ```
3. In **Edit → Project Settings → Plugins → Steam Framework** set your **App ID** (use `480` for development with Spacewar).
4. Ensure `DefaultEngine.ini` has:
   ```ini
   [OnlineSubsystem]
   DefaultPlatformService=Steam

   [OnlineSubsystemSteam]
   bEnabled=true
   SteamDevAppId=480
   ```
5. Place `steam_appid.txt` containing your App ID in the project root (for PIE) or next to the packaged executable.

No custom Game Instance class is required.

---

## Usage

Every subsystem is accessed the same way in Blueprint or C++:

**Blueprint:**
```
Get Game Instance → Get Subsystem (pick the subsystem class)
```

**C++:**
```cpp
#include "SteamLobbySubsystem.h"

USteamLobbySubsystem* Lobby = GetGameInstance()->GetSubsystem<USteamLobbySubsystem>();
```

### Example — create a lobby

```cpp
FLobbyCreateParams Params;
Params.LobbyName  = TEXT("My Lobby");
Params.MaxPlayers = 4;
Params.Visibility = ELobbyVisibility::Public;

Lobby->OnLobbyCreated.AddDynamic(this, &AMyClass::HandleLobbyCreated);
Lobby->CreateLobby(Params);
```

### Example — unlock an achievement

```cpp
USteamAchievementsSubsystem* Ach = GetGameInstance()->GetSubsystem<USteamAchievementsSubsystem>();
Ach->SetAchievement(TEXT("ACH_WIN_ONE_GAME"));
Ach->StoreStats();
```

---

## Subsystems

| Subsystem | Steam API | Highlights |
|---|---|---|
| `USteamCoreSubsystem` | `ISteamUser`, `ISteamUtils`, `ISteamApps` | Init/shutdown, RunCallbacks tick, avatars, rich presence |
| `USteamFriendsSubsystem` | `ISteamFriends` | Friends list, overlay, invites |
| `USteamLobbySubsystem` | `ISteamMatchmaking` | Full lobby lifecycle + search |
| `USteamAchievementsSubsystem` | `ISteamUserStats` | Stats, achievements, leaderboards |
| `USteamInventorySubsystem` | `ISteamInventory` | Items, definitions, drops |
| `USteamRemoteStorageSubsystem` | `ISteamRemoteStorage` | Cloud file I/O |
| `USteamUGCSubsystem` | `ISteamUGC` | Workshop query and subscriptions |
| `USteamNetworkingSubsystem` | `ISteamNetworking` | P2P packet send/receive |

Full API reference: [`Plugins/UESteamFramework/DOCUMENTATION.md`](Plugins/UESteamFramework/DOCUMENTATION.md)

---

## Project Structure

```
Plugins/UESteamFramework/
  Source/UESteamFramework/
    Public/
      SteamTypes.h                   — shared structs and enums
      SteamSettings.h                — Project Settings config object
      SteamCoreSubsystem.h
      SteamFriendsSubsystem.h
      SteamLobbySubsystem.h
      SteamAchievementsSubsystem.h
      SteamInventorySubsystem.h
      SteamRemoteStorageSubsystem.h
      SteamUGCSubsystem.h
      SteamNetworkingSubsystem.h
    Private/
      SteamSDK.h                     — internal Steam include + texture helper
      (implementations)
  DOCUMENTATION.md                   — full API reference
```

---

## License

```
Copyright 2017 - 2026 Marc Fraedrich

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
