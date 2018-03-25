#pragma once

// Disable some warnings
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // Unsafe strcpy warning
#pragma warning(disable:4265) // CallBack destructor warning
#pragma warning(disable:4828) // Steam API char offset error
#endif

// Prevent array multi-definition warning
#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"
// Restore the original ARRAY_COUNT macro
#pragma pop_macro("ARRAY_COUNT")
#include <functional>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "Misc/SecureHash.h"
#include "FrameworkDef.generated.h"



/*
Structure for Steam ID
*/
USTRUCT(BlueprintType)
struct FSteamID {
	GENERATED_USTRUCT_BODY()

		uint64 SteamID;


	CSteamID ToNativeID() {
		return CSteamID(SteamID);
	}
	
	uint64 ToInt64() {
		return SteamID;
	}

	FString ToString()
	{
		return FString::Printf(TEXT("%llu"), SteamID);
	}
			


	void SetSteamID(uint64 ID)
	{
		SteamID = ID;
	}
	void SetSteamID(CSteamID ID)
	{
		SteamID = ID.ConvertToUint64();
	}

	FSteamID(uint64 StID)
	{
		if (StID != 0)
		{
			SteamID = StID;
		}
		else
		{
			SteamID = 0;
		}
	}


	FSteamID(CSteamID StID)
	{
		if (StID.ConvertToUint64() != 0)
		{
			SteamID = StID.ConvertToUint64();
		}
		else {
			SteamID = 0;
		}
	
	}

	FSteamID()
	{
		SteamID = 0;
	}
};


UENUM(BlueprintType)
enum class ELobbyCreation : uint8
{
	LC_Success UMETA(DisplayName = "Successful"),
	LC_Failed UMETA(DisplayName = "Fail"),
	LC_Timeout UMETA(DisplayName = "Timeout"),
	LC_NoConnection UMETA(DisplayName = "No Connection")

};

UENUM(BlueprintType)
enum class ELobbyPublicLevel : uint8
{
	PL_Private UMETA(DisplayName = "Private"),
	PL_FriendsOnly UMETA(DisplayName = "Friends Only"),
	PL_Public UMETA(DisplayName = "Public")
};
/*
Lobby Creation Structs and Enums
*/

USTRUCT(BlueprintType)
struct FLobbyData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		FName LobbyName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		int32 MaxPlayers;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		FString LobbyPassword;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		ELobbyPublicLevel LobbyPublicLevel;

	void SetLobbyName(FName Name)
	{
		LobbyName = Name;
	}

	void SetMaxPlayers (int32 Players)
	{
		MaxPlayers = Players;
	}

	void SetPassword(FString Pass)
	{
		LobbyPassword = FMD5::HashAnsiString(*Pass);
	}

	FLobbyData()
	{
		LobbyName = "Steam Lobby";
		MaxPlayers = 8;
		LobbyPassword = "";
		LobbyPublicLevel = ELobbyPublicLevel::PL_Public;
	}

};






USTRUCT(BlueprintType)
struct FLobbyResult {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		FSteamID SteamID;

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Lobby")
		ELobbyCreation Status;

		FLobbyResult()
		{
			SteamID = FSteamID();
			Status = ELobbyCreation::LC_NoConnection;
		}

};



USTRUCT(BlueprintType)
struct FSteamFriend {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Friends")
		FSteamID SteamID;

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Steam|Friends")
		FString Username;

};