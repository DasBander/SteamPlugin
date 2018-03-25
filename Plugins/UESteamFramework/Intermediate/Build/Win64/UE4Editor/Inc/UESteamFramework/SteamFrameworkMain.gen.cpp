// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/SteamFrameworkMain.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamFrameworkMain() {}
// Cross Module References
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyDataUpdateCallback__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyCreatedCallback__DelegateSignature();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FLobbyResult();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkMain_NoRegister();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkMain();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_CreateLobby();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FLobbyData();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_GetLobbyMembers();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamFriend();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_GetLobbyOwner();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamID();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_IsLobbyOwner();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_JoinLobby();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkMain_LeaveLobby();
// End Cross Module References
	UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyDataUpdateCallback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_UESteamFramework, "OnLobbyDataUpdateCallback__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, 0, nullptr, 0, 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyCreatedCallback__DelegateSignature()
	{
		struct _Script_UESteamFramework_eventOnLobbyCreatedCallback_Parms
		{
			FLobbyResult Result;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Result = { UE4CodeGen_Private::EPropertyClass::Struct, "Result", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(_Script_UESteamFramework_eventOnLobbyCreatedCallback_Parms, Result), Z_Construct_UScriptStruct_FLobbyResult, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Result,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_UESteamFramework, "OnLobbyCreatedCallback__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00130000, sizeof(_Script_UESteamFramework_eventOnLobbyCreatedCallback_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	void USteamFrameworkMain::StaticRegisterNativesUSteamFrameworkMain()
	{
		UClass* Class = USteamFrameworkMain::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateLobby", (Native)&USteamFrameworkMain::execCreateLobby },
			{ "GetLobbyMembers", (Native)&USteamFrameworkMain::execGetLobbyMembers },
			{ "GetLobbyOwner", (Native)&USteamFrameworkMain::execGetLobbyOwner },
			{ "IsLobbyOwner", (Native)&USteamFrameworkMain::execIsLobbyOwner },
			{ "JoinLobby", (Native)&USteamFrameworkMain::execJoinLobby },
			{ "LeaveLobby", (Native)&USteamFrameworkMain::execLeaveLobby },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_CreateLobby()
	{
		struct SteamFrameworkMain_eventCreateLobby_Parms
		{
			FLobbyData LobbyData;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_LobbyData = { UE4CodeGen_Private::EPropertyClass::Struct, "LobbyData", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkMain_eventCreateLobby_Parms, LobbyData), Z_Construct_UScriptStruct_FLobbyData, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyData,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "CreateLobby", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(SteamFrameworkMain_eventCreateLobby_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_GetLobbyMembers()
	{
		struct SteamFrameworkMain_eventGetLobbyMembers_Parms
		{
			TArray<FSteamFriend> ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Array, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkMain_eventGetLobbyMembers_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FSteamFriend, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue_Inner,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "GetLobbyMembers", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(SteamFrameworkMain_eventGetLobbyMembers_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_GetLobbyOwner()
	{
		struct SteamFrameworkMain_eventGetLobbyOwner_Parms
		{
			FSteamID ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkMain_eventGetLobbyOwner_Parms, ReturnValue), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "GetLobbyOwner", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14020401, sizeof(SteamFrameworkMain_eventGetLobbyOwner_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_IsLobbyOwner()
	{
		struct SteamFrameworkMain_eventIsLobbyOwner_Parms
		{
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((SteamFrameworkMain_eventIsLobbyOwner_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(SteamFrameworkMain_eventIsLobbyOwner_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "IsLobbyOwner", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14020401, sizeof(SteamFrameworkMain_eventIsLobbyOwner_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_JoinLobby()
	{
		struct SteamFrameworkMain_eventJoinLobby_Parms
		{
			FSteamID LobbyID;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_LobbyID = { UE4CodeGen_Private::EPropertyClass::Struct, "LobbyID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkMain_eventJoinLobby_Parms, LobbyID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyID,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "JoinLobby", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(SteamFrameworkMain_eventJoinLobby_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkMain_LeaveLobby()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkMain, "LeaveLobby", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, 0, nullptr, 0, 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USteamFrameworkMain_NoRegister()
	{
		return USteamFrameworkMain::StaticClass();
	}
	UClass* Z_Construct_UClass_USteamFrameworkMain()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UObject,
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_USteamFrameworkMain_CreateLobby, "CreateLobby" }, // 622019220
				{ &Z_Construct_UFunction_USteamFrameworkMain_GetLobbyMembers, "GetLobbyMembers" }, // 2529587318
				{ &Z_Construct_UFunction_USteamFrameworkMain_GetLobbyOwner, "GetLobbyOwner" }, // 897958258
				{ &Z_Construct_UFunction_USteamFrameworkMain_IsLobbyOwner, "IsLobbyOwner" }, // 1937441836
				{ &Z_Construct_UFunction_USteamFrameworkMain_JoinLobby, "JoinLobby" }, // 3202610227
				{ &Z_Construct_UFunction_USteamFrameworkMain_LeaveLobby, "LeaveLobby" }, // 1584699629
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "SteamFrameworkMain.h" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnLobbyDataUpdate_MetaData[] = {
				{ "Category", "Steam|Lobby|Callbacks" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnLobbyDataUpdate = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "OnLobbyDataUpdate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USteamFrameworkMain, OnLobbyDataUpdate), Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyDataUpdateCallback__DelegateSignature, METADATA_PARAMS(NewProp_OnLobbyDataUpdate_MetaData, ARRAY_COUNT(NewProp_OnLobbyDataUpdate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LobbyCreated_MetaData[] = {
				{ "Category", "Steam|Lobby|Callbacks" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_LobbyCreated = { UE4CodeGen_Private::EPropertyClass::MulticastDelegate, "LobbyCreated", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000010080000, 1, nullptr, STRUCT_OFFSET(USteamFrameworkMain, LobbyCreated), Z_Construct_UDelegateFunction_UESteamFramework_OnLobbyCreatedCallback__DelegateSignature, METADATA_PARAMS(NewProp_LobbyCreated_MetaData, ARRAY_COUNT(NewProp_LobbyCreated_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentLobbySteamID_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_CurrentLobbySteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "CurrentLobbySteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020015, 1, nullptr, STRUCT_OFFSET(USteamFrameworkMain, CurrentLobbySteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(NewProp_CurrentLobbySteamID_MetaData, ARRAY_COUNT(NewProp_CurrentLobbySteamID_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsInLobby_MetaData[] = {
				{ "Category", "Steam|Lobby" },
				{ "ModuleRelativePath", "Public/SteamFrameworkMain.h" },
			};
#endif
			auto NewProp_IsInLobby_SetBit = [](void* Obj){ ((USteamFrameworkMain*)Obj)->IsInLobby = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsInLobby = { UE4CodeGen_Private::EPropertyClass::Bool, "IsInLobby", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000020015, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(USteamFrameworkMain), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_IsInLobby_SetBit)>::SetBit, METADATA_PARAMS(NewProp_IsInLobby_MetaData, ARRAY_COUNT(NewProp_IsInLobby_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_OnLobbyDataUpdate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_LobbyCreated,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_CurrentLobbySteamID,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_IsInLobby,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<USteamFrameworkMain>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&USteamFrameworkMain::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamFrameworkMain, 2402846986);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamFrameworkMain(Z_Construct_UClass_USteamFrameworkMain, &USteamFrameworkMain::StaticClass, TEXT("/Script/UESteamFramework"), TEXT("USteamFrameworkMain"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamFrameworkMain);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
