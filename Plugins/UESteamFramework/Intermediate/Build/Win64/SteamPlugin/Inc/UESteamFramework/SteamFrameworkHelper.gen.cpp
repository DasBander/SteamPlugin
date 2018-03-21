// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/SteamFrameworkHelper.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamFrameworkHelper() {}
// Cross Module References
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkHelper_NoRegister();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkHelper();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetFriendsList();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamFriend();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetSteamAvatar();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	UESTEAMFRAMEWORK_API UScriptStruct* Z_Construct_UScriptStruct_FSteamID();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetSteamInterface();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkMain_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetUsername();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetUserSteamID();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_MakeSteamID();
	UESTEAMFRAMEWORK_API UFunction* Z_Construct_UFunction_USteamFrameworkHelper_SteamIDToString();
// End Cross Module References
	void USteamFrameworkHelper::StaticRegisterNativesUSteamFrameworkHelper()
	{
		UClass* Class = USteamFrameworkHelper::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetFriendsList", (Native)&USteamFrameworkHelper::execGetFriendsList },
			{ "GetSteamAvatar", (Native)&USteamFrameworkHelper::execGetSteamAvatar },
			{ "GetSteamInterface", (Native)&USteamFrameworkHelper::execGetSteamInterface },
			{ "GetUsername", (Native)&USteamFrameworkHelper::execGetUsername },
			{ "GetUserSteamID", (Native)&USteamFrameworkHelper::execGetUserSteamID },
			{ "MakeSteamID", (Native)&USteamFrameworkHelper::execMakeSteamID },
			{ "SteamIDToString", (Native)&USteamFrameworkHelper::execSteamIDToString },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetFriendsList()
	{
		struct SteamFrameworkHelper_eventGetFriendsList_Parms
		{
			TArray<FSteamFriend> ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Array, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetFriendsList_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FSteamFriend, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue_Inner,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "GetFriendsList", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(SteamFrameworkHelper_eventGetFriendsList_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetSteamAvatar()
	{
		struct SteamFrameworkHelper_eventGetSteamAvatar_Parms
		{
			FSteamID SteamID;
			UTexture2D* ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Object, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetSteamAvatar_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetSteamAvatar_Parms, SteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "GetSteamAvatar", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(SteamFrameworkHelper_eventGetSteamAvatar_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetSteamInterface()
	{
		struct SteamFrameworkHelper_eventGetSteamInterface_Parms
		{
			UObject* WorldContextObject;
			USteamFrameworkMain* ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Object, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetSteamInterface_Parms, ReturnValue), Z_Construct_UClass_USteamFrameworkMain_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject = { UE4CodeGen_Private::EPropertyClass::Object, "WorldContextObject", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetSteamInterface_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_WorldContextObject,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam Framework|Main" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
				{ "WorldContext", "WorldContextObject" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "GetSteamInterface", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(SteamFrameworkHelper_eventGetSteamInterface_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetUsername()
	{
		struct SteamFrameworkHelper_eventGetUsername_Parms
		{
			FSteamID SteamID;
			FString ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Str, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetUsername_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetUsername_Parms, SteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "GetUsername", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(SteamFrameworkHelper_eventGetUsername_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_GetUserSteamID()
	{
		struct SteamFrameworkHelper_eventGetUserSteamID_Parms
		{
			FSteamID ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventGetUserSteamID_Parms, ReturnValue), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "GetUserSteamID", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(SteamFrameworkHelper_eventGetUserSteamID_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_MakeSteamID()
	{
		struct SteamFrameworkHelper_eventMakeSteamID_Parms
		{
			FString SteamID;
			FSteamID ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventMakeSteamID_Parms, ReturnValue), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Str, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventMakeSteamID_Parms, SteamID), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "MakeSteamID", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(SteamFrameworkHelper_eventMakeSteamID_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_USteamFrameworkHelper_SteamIDToString()
	{
		struct SteamFrameworkHelper_eventSteamIDToString_Parms
		{
			FSteamID SteamID;
			FString ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Str, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventSteamIDToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamID = { UE4CodeGen_Private::EPropertyClass::Struct, "SteamID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(SteamFrameworkHelper_eventSteamIDToString_Parms, SteamID), Z_Construct_UScriptStruct_FSteamID, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamID,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Steam|Helper" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamFrameworkHelper, "SteamIDToString", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x14022401, sizeof(SteamFrameworkHelper_eventSteamIDToString_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USteamFrameworkHelper_NoRegister()
	{
		return USteamFrameworkHelper::StaticClass();
	}
	UClass* Z_Construct_UClass_USteamFrameworkHelper()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_USteamFrameworkHelper_GetFriendsList, "GetFriendsList" }, // 3564976337
				{ &Z_Construct_UFunction_USteamFrameworkHelper_GetSteamAvatar, "GetSteamAvatar" }, // 275005052
				{ &Z_Construct_UFunction_USteamFrameworkHelper_GetSteamInterface, "GetSteamInterface" }, // 3454949189
				{ &Z_Construct_UFunction_USteamFrameworkHelper_GetUsername, "GetUsername" }, // 4126714395
				{ &Z_Construct_UFunction_USteamFrameworkHelper_GetUserSteamID, "GetUserSteamID" }, // 900125685
				{ &Z_Construct_UFunction_USteamFrameworkHelper_MakeSteamID, "MakeSteamID" }, // 4179771956
				{ &Z_Construct_UFunction_USteamFrameworkHelper_SteamIDToString, "SteamIDToString" }, // 1235149858
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "SteamFrameworkHelper.h" },
				{ "ModuleRelativePath", "Public/SteamFrameworkHelper.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<USteamFrameworkHelper>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&USteamFrameworkHelper::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamFrameworkHelper, 3964375359);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamFrameworkHelper(Z_Construct_UClass_USteamFrameworkHelper, &USteamFrameworkHelper::StaticClass, TEXT("/Script/UESteamFramework"), TEXT("USteamFrameworkHelper"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamFrameworkHelper);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
