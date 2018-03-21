// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FrameworkDef.h"
#include "Engine/Texture2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UESFGameInstance.h"
#include "UESteamFramework.h"
#include "SteamFrameworkHelper.generated.h"

/**
 * 
 */
UCLASS()
class UESTEAMFRAMEWORK_API USteamFrameworkHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintPure, Category = "Steam|Helper")
		static FSteamID GetUserSteamID();
	

	UFUNCTION(BlueprintPure, Category = "Steam|Helper")
		static FString SteamIDToString(FSteamID SteamID);

	UFUNCTION(BlueprintPure, Category = "Steam|Helper")
		static FSteamID MakeSteamID(FString SteamID);

	UFUNCTION(BlueprintCallable, Category = "Steam|Helper")
		static UTexture2D * GetSteamAvatar(FSteamID SteamID);

	UFUNCTION(BlueprintPure, Category = "Steam|Helper")
		static FString GetUsername(FSteamID SteamID);

	UFUNCTION(BlueprintCallable, Category = "Steam|Helper")
		static TArray<FSteamFriend> GetFriendsList();

	UFUNCTION(BlueprintPure, Category = "Steam Framework|Main", meta = (WorldContext = "WorldContextObject"))
		static USteamFrameworkMain * GetSteamInterface(UObject* WorldContextObject);



};
