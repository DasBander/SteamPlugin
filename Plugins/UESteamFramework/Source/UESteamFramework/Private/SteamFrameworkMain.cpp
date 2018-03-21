/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/
#pragma warning(disable:4265) // CallBack destructor warning


#include "SteamFrameworkMain.h"
#include "Runtime/Core/Public/Misc/MessageDialog.h"
#include "SteamFrameworkHelper.h"


USteamFrameworkMain::USteamFrameworkMain(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FString USteamFrameworkMain::GetStringConfigValue(FString param)
{

	FString configreturn = "null";
	if (GConfig->GetString(TEXT("/Script/UESteamFramework.SteamSettings"), *param, configreturn, FPaths::ProjectConfigDir() / "DefaultSteamFramework.ini"))
	{
		return configreturn;
	}
	else
	{
		return "error";
	}
	
}

void USteamFrameworkMain::Init_Steam()
{
	if (OnlineInterface->IsLoaded())
 	{
		bool SteamInit = SteamAPI_Init();
		UE_LOG(LogSteamFramework, Log, TEXT("Steam Framework Initialized."));
		if (FString::FromInt(SteamUtils()->GetAppID()) != GetStringConfigValue("AppID") & SteamInit)
		{

			const FText MessageText = NSLOCTEXT("SteamFramework","AppOwnershipCheckFailed","You must own the game before you start it.\n");
			const FText MessageTitle = NSLOCTEXT("SteamFramework", "AppOwnershipCheckFailedTitle", "App Ownership Check Failed");
			// Kill the app. AppID is not the same as the appid the game got started with.
			FMessageDialog::Open(EAppMsgType::Ok, MessageText, &MessageTitle);
			FPlatformMisc::RequestExit(1);
		}
		if (!SteamInit)
		{
			const FText MessageText = NSLOCTEXT("SteamFramework", "SteamNotStarted", "This game requires Steam to start.\n");
			const FText MessageTitle = NSLOCTEXT("SteamFramework", "SteamNotStartedTitle", "Steam not running.");
			// Kill the app. Steam is not running or at least we couldn't init steam.
			FMessageDialog::Open(EAppMsgType::Ok, MessageText, &MessageTitle);
			FPlatformMisc::RequestExit(1);
		}
		//GLog->Log(OnlineInterface->GetIdentityInterface()->GetAuthToken(0));
		
	}

	/*
	If Online Subsystem is not loaded then we have a big big problem.
	*/
}

ELobbyType USteamFrameworkMain::GetLobbyType(ELobbyPublicLevel LobbyPublicLevel)
{
	switch (LobbyPublicLevel) {
	case ELobbyPublicLevel::PL_Public:
		return ELobbyType::k_ELobbyTypePublic;
		break;
	case ELobbyPublicLevel::PL_Private:
		return ELobbyType::k_ELobbyTypePrivate;
		break;
	case ELobbyPublicLevel::PL_FriendsOnly:
		return ELobbyType::k_ELobbyTypeFriendsOnly;
		break;
	default:
		return ELobbyType::k_ELobbyTypePublic;
		break;
	}
}



void USteamFrameworkMain::CreateLobby(FLobbyData LobbyInfo)
{
	SteamAPICall_t ApiCall = SteamMatchmaking()->CreateLobby(GetLobbyType(LobbyInfo.LobbyPublicLevel), LobbyInfo.MaxPlayers);
	
	CallResult_LobbyCreated.Set(ApiCall, [=](LobbyCreated_t* Result, bool bFailure) {
		if (!bFailure)
		{
			FLobbyResult LobbyData;
			switch (Result->m_eResult) {
			case k_EResultOK:
				LobbyData.Status = ELobbyCreation::LC_Success;
				IsInLobby = true;
				CurrentLobbySteamID.SetSteamID(Result->m_ulSteamIDLobby);
				break;
			case k_EResultFail:
				LobbyData.Status = ELobbyCreation::LC_Failed;
				break;
			case k_EResultTimeout:
				LobbyData.Status = ELobbyCreation::LC_Timeout;
				break;
			case k_EResultNoConnection:
				LobbyData.Status = ELobbyCreation::LC_NoConnection;
				break;
			default:
				LobbyData.Status = ELobbyCreation::LC_Timeout;
				break;
			}
			LobbyData.SteamID.SetSteamID(Result->m_ulSteamIDLobby);
			SteamMatchmaking()->SetLobbyData(CSteamID(LobbyData.SteamID.SteamID), TCHAR_TO_UTF8("LobbyName"), TCHAR_TO_UTF8(*LobbyInfo.LobbyName.ToString()));
			SteamMatchmaking()->SetLobbyData(CSteamID(LobbyData.SteamID.SteamID), TCHAR_TO_UTF8("LobbyOwner"), TCHAR_TO_UTF8(*USteamFrameworkHelper::SteamIDToString(USteamFrameworkHelper::GetUserSteamID())));
			FLobbyData LobbyPublicInfo;
			LobbyPublicInfo.SetPassword(LobbyInfo.LobbyPassword);
			SteamMatchmaking()->SetLobbyData(CSteamID(LobbyData.SteamID.SteamID), TCHAR_TO_UTF8("LobbyPassword"), TCHAR_TO_UTF8(*LobbyPublicInfo.LobbyPassword));
			LobbyCreated.Broadcast(LobbyData);
		}
	});


}

void USteamFrameworkMain::LeaveLobby()
{
	SteamMatchmaking()->LeaveLobby(CSteamID(CurrentLobbySteamID.SteamID));
	IsInLobby = false;
}


void USteamFrameworkMain::OnLobbyDataUpdate_Steam(LobbyDataUpdate_t* LData)
{
	if (LData->m_bSuccess)
	{
		OnLobbyDataUpdate.Broadcast();
	}
}

bool USteamFrameworkMain::IsLobbyOwner()
{
	if (IsInLobby)
	{
		CSteamID lobbyowner = SteamMatchmaking()->GetLobbyOwner(CSteamID(CurrentLobbySteamID.SteamID));
		if (lobbyowner.ConvertToUint64() == SteamUser()->GetSteamID().ConvertToUint64())
		{
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	
}

FSteamID USteamFrameworkMain::GetLobbyOwner()
{
	FSteamID TempID;
	if (IsInLobby)
	{
		CSteamID lobbyowner = SteamMatchmaking()->GetLobbyOwner(CSteamID(CurrentLobbySteamID.SteamID));
		TempID.SetSteamID(lobbyowner.ConvertToUint64());
		return TempID;
	}
	else {
		return TempID;
	}
}

TArray<FSteamFriend> USteamFrameworkMain::GetLobbyMembers()
{
	TArray<FSteamFriend> PlayersInLobby;
	if (IsInLobby)
	{

	int LobbyPlayerCount = SteamMatchmaking()->GetNumLobbyMembers(CSteamID(CurrentLobbySteamID.SteamID));
 	if (LobbyPlayerCount > 0)
	{
 			for (int i = 0; i < LobbyPlayerCount; i++)
  			{
 				CSteamID LocalPlayer = SteamMatchmaking()->GetLobbyMemberByIndex(CSteamID(CurrentLobbySteamID.SteamID), i);
 				FSteamFriend tempLobbyMember;
  				tempLobbyMember.SteamID.SetSteamID(LocalPlayer.ConvertToUint64());
  				tempLobbyMember.Username = USteamFrameworkHelper::GetUsername(tempLobbyMember.SteamID);
  				PlayersInLobby.Add(tempLobbyMember);
 			}
  	}


		return PlayersInLobby;
	}
	else
	{
		return PlayersInLobby;
	}
}

