/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/

#include "UESFGameInstance.h"


UUESFGameInstance::UUESFGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UUESFGameInstance::Init()
{
	Super::Init();
	// For older UE versions (Pre 4.9) you may use `ConstructObject` instead

	SteamFramework = NewObject<USteamFrameworkMain>(USteamFrameworkMain::StaticClass());
	SteamFramework->AddToRoot();
	if (SteamFramework != NULL)
	{

		SteamFramework->Init_Steam();
		
	}
	else
	{
		GLog->Log("Could not init steam.");
	}
}


/*
Returns Steam Framework Main Object so we can work in Blueprints with it.
*/

void UUESFGameInstance::Shutdown()
{
	if (SteamFramework)
	{
		if (SteamFramework->IsInLobby)
		{
			SteamFramework->LeaveLobby();
		}
	}

}


