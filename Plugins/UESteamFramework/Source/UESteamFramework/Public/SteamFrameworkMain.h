/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UESteamFramework.h"
#include "Online.h"
#include "UnrealNetwork.h"
#include "Misc/SecureHash.h"
#include "FrameworkDef.h"
#include "SteamFrameworkMain.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyCreatedCallback, FLobbyResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyDataUpdateCallback);


class IOnlineSubsystem;
/**
 * 
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamFrameworkMain : public UObject
{
	GENERATED_UCLASS_BODY()
		
	

public:


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
		bool IsInLobby = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Steam|Lobby")
		FSteamID CurrentLobbySteamID;



	FString GetStringConfigValue(FString param);

	void Init_Steam();
	


	//Helper
	ELobbyType GetLobbyType(ELobbyPublicLevel LobbyPublicLevel);

	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
		void LeaveLobby();

	UFUNCTION(BlueprintCallable, Category="Steam|Lobby")
	void CreateLobby(FLobbyData LobbyData);

	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
		void JoinLobby(FSteamID LobbyID);

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
	FOnLobbyCreatedCallback LobbyCreated;


	UFUNCTION(BlueprintPure, Category = "Steam|Lobby")
		bool IsLobbyOwner();

	UFUNCTION(BlueprintPure, Category = "Steam|Lobby")
		FSteamID GetLobbyOwner();

	UFUNCTION(BlueprintCallable, Category = "Steam|Lobby")
		TArray<FSteamFriend> GetLobbyMembers();

	UPROPERTY(BlueprintAssignable, Category = "Steam|Lobby|Callbacks")
		FOnLobbyDataUpdateCallback  OnLobbyDataUpdate;


	//Steam Lambda Callbacks
	CLambdaCallResult<LobbyCreated_t> CallResult_LobbyCreated;
	CLambdaCallResult<LobbyEnter_t> CallResult_LobbyEntered;

private:
	IOnlineSubsystem* OnlineInterface = IOnlineSubsystem::Get();

	STEAM_CALLBACK(USteamFrameworkMain, OnLobbyDataUpdate_Steam, LobbyDataUpdate_t);
	STEAM_CALLBACK(USteamFrameworkMain, OnSteamLobbyJoinRequest, GameLobbyJoinRequested_t);
	STEAM_CALLBACK(USteamFrameworkMain, OnSteamLobbyChatUpdate, LobbyChatUpdate_t);
};
