/*
Copyright (c) 2018 FinalSpark Gamestudios
Coded by Marc Fraedrich with love.
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SteamFrameworkMain.h"
#include "UESFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UESTEAMFRAMEWORK_API UUESFGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()
	
	
public:

	UPROPERTY()
	 USteamFrameworkMain * SteamFramework;
	
	virtual void Init() override;
	virtual void Shutdown() override;

};
