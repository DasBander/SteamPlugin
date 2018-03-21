// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SteamPluginGameMode.h"
#include "SteamPluginHUD.h"
#include "SteamPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteamPluginGameMode::ASteamPluginGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASteamPluginHUD::StaticClass();
}
