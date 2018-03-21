// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/FrameworkDef.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFrameworkDef() {}
// Cross Module References
	UESTEAMFRAMEWORK_API UEnum* Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework();
	UESTEAMFRAMEWORK_API UEnum* Z_Construct_UEnum_UESteamFramework_ELobbyCreation();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamFriend();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamID();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FLobbyResult();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FLobbyData();
// End Cross Module References
	static UEnum* ELobbyPublicLevel_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("ELobbyPublicLevel"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ELobbyPublicLevel(ELobbyPublicLevel_StaticEnum, TEXT("/Script/UESteamFramework"), TEXT("ELobbyPublicLevel"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel_CRC() { return 2416604868U; }
	UEnum* Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ELobbyPublicLevel"), 0, Get_Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ELobbyPublicLevel::PL_Private", (int64)ELobbyPublicLevel::PL_Private },
				{ "ELobbyPublicLevel::PL_FriendsOnly", (int64)ELobbyPublicLevel::PL_FriendsOnly },
				{ "ELobbyPublicLevel::PL_Public", (int64)ELobbyPublicLevel::PL_Public },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
				{ "PL_FriendsOnly.DisplayName", "Friends Only" },
				{ "PL_Private.DisplayName", "Private" },
				{ "PL_Public.DisplayName", "Public" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_UESteamFramework,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ELobbyPublicLevel",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ELobbyPublicLevel",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ELobbyCreation_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_UESteamFramework_ELobbyCreation, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("ELobbyCreation"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ELobbyCreation(ELobbyCreation_StaticEnum, TEXT("/Script/UESteamFramework"), TEXT("ELobbyCreation"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_UESteamFramework_ELobbyCreation_CRC() { return 38294548U; }
	UEnum* Z_Construct_UEnum_UESteamFramework_ELobbyCreation()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ELobbyCreation"), 0, Get_Z_Construct_UEnum_UESteamFramework_ELobbyCreation_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ELobbyCreation::LC_Success", (int64)ELobbyCreation::LC_Success },
				{ "ELobbyCreation::LC_Failed", (int64)ELobbyCreation::LC_Failed },
				{ "ELobbyCreation::LC_Timeout", (int64)ELobbyCreation::LC_Timeout },
				{ "ELobbyCreation::LC_NoConnection", (int64)ELobbyCreation::LC_NoConnection },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "LC_Failed.DisplayName", "Fail" },
				{ "LC_NoConnection.DisplayName", "No Connection" },
				{ "LC_Success.DisplayName", "Successful" },
				{ "LC_Timeout.DisplayName", "Timeout" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_UESteamFramework,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ELobbyCreation",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"ELobbyCreation",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FSteamFriend::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern UESTEAMFRAMEWORK_API uint32 Get_Z_Construct_UScriptStruct_FSteamFriend_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSteamFriend, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("SteamFriend"), sizeof(FSteamFriend), Get_Z_Construct_UScriptStruct_FSteamFriend_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSteamFriend(FSteamFriend::StaticStruct, TEXT("/Script/UESteamFramework"), TEXT("SteamFriend"), false, nullptr, nullptr);
static struct FScriptStruct_UESteamFramework_StaticRegisterNativesFSteamFriend
{
	FScriptStruct_UESteamFramework_StaticRegisterNativesFSteamFriend()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SteamFriend")),new UScriptStruct::TCppStructOps<FSteamFriend>);
	}
} ScriptStruct_UESteamFramework_StaticRegisterNativesFSteamFriend;
	UScriptStruct* Z_Construct_UScriptStruct_FSteamFriend()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSteamFriend_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SteamFriend"), sizeof(FSteamFriend), Get_Z_Construct_UScriptStruct_FSteamFriend_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSteamFriend>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[] = {
				{ "Category", "Steam|Friends" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_Username = { UE4CodeGen_Private::EPropertyClass::Str, "Username", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FSteamFriend, Username), METADATA_PARAMS(NewProp_Username_MetaData, ARRAY_COUNT(NewProp_Username_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamID_MetaData[] = {
				{ "Category", "Steam|Friends" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FSteamFriend, SteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(NewProp_SteamID_MetaData, ARRAY_COUNT(NewProp_SteamID_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Username,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"SteamFriend",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FSteamFriend),
				alignof(FSteamFriend),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSteamFriend_CRC() { return 2221199017U; }
class UScriptStruct* FLobbyResult::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern UESTEAMFRAMEWORK_API uint32 Get_Z_Construct_UScriptStruct_FLobbyResult_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLobbyResult, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("LobbyResult"), sizeof(FLobbyResult), Get_Z_Construct_UScriptStruct_FLobbyResult_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLobbyResult(FLobbyResult::StaticStruct, TEXT("/Script/UESteamFramework"), TEXT("LobbyResult"), false, nullptr, nullptr);
static struct FScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyResult
{
	FScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyResult()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LobbyResult")),new UScriptStruct::TCppStructOps<FLobbyResult>);
	}
} ScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyResult;
	UScriptStruct* Z_Construct_UScriptStruct_FLobbyResult()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLobbyResult_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LobbyResult"), sizeof(FLobbyResult), Get_Z_Construct_UScriptStruct_FLobbyResult_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLobbyResult>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Enum, "Status", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyResult, Status), Z_Construct_UEnum_UESteamFramework_ELobbyCreation, METADATA_PARAMS(NewProp_Status_MetaData, ARRAY_COUNT(NewProp_Status_MetaData)) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_Status_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamID_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyResult, SteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(NewProp_SteamID_MetaData, ARRAY_COUNT(NewProp_SteamID_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Status,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Status_Underlying,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"LobbyResult",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FLobbyResult),
				alignof(FLobbyResult),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLobbyResult_CRC() { return 1051838020U; }
class UScriptStruct* FLobbyData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern UESTEAMFRAMEWORK_API uint32 Get_Z_Construct_UScriptStruct_FLobbyData_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLobbyData, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("LobbyData"), sizeof(FLobbyData), Get_Z_Construct_UScriptStruct_FLobbyData_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLobbyData(FLobbyData::StaticStruct, TEXT("/Script/UESteamFramework"), TEXT("LobbyData"), false, nullptr, nullptr);
static struct FScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyData
{
	FScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LobbyData")),new UScriptStruct::TCppStructOps<FLobbyData>);
	}
} ScriptStruct_UESteamFramework_StaticRegisterNativesFLobbyData;
	UScriptStruct* Z_Construct_UScriptStruct_FLobbyData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLobbyData_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LobbyData"), sizeof(FLobbyData), Get_Z_Construct_UScriptStruct_FLobbyData_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
				{ "ToolTip", "Lobby Creation Structs and Enums" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLobbyData>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LobbyPublicLevel_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumPropertyParams NewProp_LobbyPublicLevel = { UE4CodeGen_Private::EPropertyClass::Enum, "LobbyPublicLevel", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyData, LobbyPublicLevel), Z_Construct_UEnum_UESteamFramework_ELobbyPublicLevel, METADATA_PARAMS(NewProp_LobbyPublicLevel_MetaData, ARRAY_COUNT(NewProp_LobbyPublicLevel_MetaData)) };
			static const UE4CodeGen_Private::FBytePropertyParams NewProp_LobbyPublicLevel_Underlying = { UE4CodeGen_Private::EPropertyClass::Byte, "UnderlyingType", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LobbyPassword_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_LobbyPassword = { UE4CodeGen_Private::EPropertyClass::Str, "LobbyPassword", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyData, LobbyPassword), METADATA_PARAMS(NewProp_LobbyPassword_MetaData, ARRAY_COUNT(NewProp_LobbyPassword_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxPlayers_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxPlayers = { UE4CodeGen_Private::EPropertyClass::Int, "MaxPlayers", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyData, MaxPlayers), METADATA_PARAMS(NewProp_MaxPlayers_MetaData, ARRAY_COUNT(NewProp_MaxPlayers_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LobbyName_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
			};
#endif
			static const UE4CodeGen_Private::FNamePropertyParams NewProp_LobbyName = { UE4CodeGen_Private::EPropertyClass::Name, "LobbyName", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020005, 1, nullptr, STRUCT_OFFSET(FLobbyData, LobbyName), METADATA_PARAMS(NewProp_LobbyName_MetaData, ARRAY_COUNT(NewProp_LobbyName_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyPublicLevel,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyPublicLevel_Underlying,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyPassword,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_MaxPlayers,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyName,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"LobbyData",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FLobbyData),
				alignof(FLobbyData),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLobbyData_CRC() { return 828750781U; }
class UScriptStruct* FSteamID::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern UESTEAMFRAMEWORK_API uint32 Get_Z_Construct_UScriptStruct_FSteamID_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSteamID, Z_Construct_UPackage__Script_UESteamFramework(), TEXT("SteamID"), sizeof(FSteamID), Get_Z_Construct_UScriptStruct_FSteamID_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSteamID(FSteamID::StaticStruct, TEXT("/Script/UESteamFramework"), TEXT("SteamID"), false, nullptr, nullptr);
static struct FScriptStruct_UESteamFramework_StaticRegisterNativesFSteamID
{
	FScriptStruct_UESteamFramework_StaticRegisterNativesFSteamID()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SteamID")),new UScriptStruct::TCppStructOps<FSteamID>);
	}
} ScriptStruct_UESteamFramework_StaticRegisterNativesFSteamID;
	UScriptStruct* Z_Construct_UScriptStruct_FSteamID()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSteamID_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_UESteamFramework();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SteamID"), sizeof(FSteamID), Get_Z_Construct_UScriptStruct_FSteamID_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FrameworkDef.h" },
				{ "ToolTip", "Structure for Steam ID" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSteamID>(); };
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"SteamID",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FSteamID),
				alignof(FSteamID),
				nullptr, 0,
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSteamID_CRC() { return 3121691627U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
