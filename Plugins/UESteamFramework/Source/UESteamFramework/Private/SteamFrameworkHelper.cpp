// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamFrameworkHelper.h"




FSteamID USteamFrameworkHelper::GetUserSteamID()
{
	FSteamID TempSteamID;
	TempSteamID.SetSteamID(SteamUser()->GetSteamID().ConvertToUint64());

	return TempSteamID;
}

FString USteamFrameworkHelper::SteamIDToString(FSteamID SteamID)
{
	return SteamID.ToString();
}

FSteamID USteamFrameworkHelper::MakeSteamID(FString SteamID)
{
	FSteamID TempSteamID;
	TempSteamID.SetSteamID(FCString::Strtoui64(*SteamID, NULL, SteamID.Len()));
	return TempSteamID;
}

UTexture2D * USteamFrameworkHelper::GetSteamAvatar(FSteamID SteamID)
{
	// Get the avatar of this user
	uint32 AvatarWidth;
	uint32 AvatarHeight;
	int AvatarID = SteamFriends()->GetLargeFriendAvatar(SteamID.SteamID);
	SteamUtils()->GetImageSize(AvatarID, &AvatarWidth, &AvatarHeight);

	if (AvatarWidth > 0 && AvatarHeight > 0)
	{
		TArray<uint8> AvatarBuffer = TArray<uint8>();
		AvatarBuffer.AddZeroed(4 * AvatarHeight * AvatarWidth);
		bool bWasSuccessful = SteamUtils()->GetImageRGBA(AvatarID, AvatarBuffer.GetData(), 4 * AvatarHeight * AvatarWidth * sizeof(char));
		if (bWasSuccessful)
		{
			UTexture2D * Avatar;
			Avatar = UTexture2D::CreateTransient(AvatarWidth, AvatarHeight, PF_R8G8B8A8);
			void* TextureData = Avatar->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, AvatarBuffer.GetData(), AvatarWidth * AvatarHeight * 4);
			Avatar->PlatformData->Mips[0].BulkData.Unlock();
			Avatar->UpdateResource();
			AvatarBuffer.Empty();
			return Avatar;
		}
		else {
			return nullptr;
		}
	
	}
	else {
		return nullptr;
	}

}


//Somehow doesn't print anything? But why?
FString USteamFrameworkHelper::GetUsername(FSteamID SteamID)
{
	if (SteamUser()->GetSteamID().ConvertToUint64() == SteamID.SteamID)
	{
		FString username(SteamFriends()->GetPersonaName());
		return username;
	}
	else {
		FString username(SteamFriends()->GetPlayerNickname(CSteamID(SteamID.SteamID)));
		return username;
	}
	

}


TArray<FSteamFriend> USteamFrameworkHelper::GetFriendsList()
{
	TArray<FSteamFriend> Friends;
	int nFriends = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
	for (int i = 0; i < nFriends; ++i)
	{
		CSteamID friendSteamID = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
		FString username = FString::Printf(TEXT("%s"), UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(friendSteamID)));
		FSteamFriend user;
		user.SteamID.SetSteamID(friendSteamID);
		user.Username = username;
		if (SteamFriends()->GetFriendPersonaState(friendSteamID) != k_EPersonaStateOffline)
		{
			Friends.Add(user);
		}
	}
	return Friends;
}

USteamFrameworkMain * USteamFrameworkHelper::GetSteamInterface(UObject* WorldContextObject)
{
	UWorld * NewWorld = Cast<UWorld>(GEngine->GetWorldFromContextObject(WorldContextObject));
	UUESFGameInstance * GameInst = Cast<UUESFGameInstance>(NewWorld->GetGameInstance());
	if (GameInst)
	{
		if (GameInst->SteamFramework)
		{
			return GameInst->SteamFramework;
		}
		else
		{
			GLog->Log("Could not get steam framework object. Invalid.");
			return nullptr;
		}
	}
	else
	{
		GLog->Log("Could not get game instance. Invalid.");
		return nullptr;
	}

}



