// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUESteamFramework_init() {}
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyCreatedCallback__DelegateSignature();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyDataUpdateCallback__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyCreatedCallback__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyDataUpdateCallback__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/UESteamFramework",
				PKG_CompiledIn | 0x00000080,
				0x94CE945D,
				0x2AABBE63,
				SingletonFuncArray, ARRAY_COUNT(SingletonFuncArray),
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
