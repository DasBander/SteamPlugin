// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/SteamSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamSettings() {}
// Cross Module References
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamSettings_NoRegister();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework();
// End Cross Module References
	void USteamSettings::StaticRegisterNativesUSteamSettings()
	{
	}
	UClass* Z_Construct_UClass_USteamSettings_NoRegister()
	{
		return USteamSettings::StaticClass();
	}
	UClass* Z_Construct_UClass_USteamSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UObject,
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "DisplayName", "Steam Framework" },
				{ "IncludePath", "SteamSettings.h" },
				{ "ModuleRelativePath", "Public/SteamSettings.h" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableProductProtection_MetaData[] = {
				{ "Category", "Steam | Product Protection" },
				{ "ModuleRelativePath", "Public/SteamSettings.h" },
			};
#endif
			auto NewProp_EnableProductProtection_SetBit = [](void* Obj){ ((USteamSettings*)Obj)->EnableProductProtection = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_EnableProductProtection = { UE4CodeGen_Private::EPropertyClass::Bool, "EnableProductProtection", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000004001, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(USteamSettings), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_EnableProductProtection_SetBit)>::SetBit, METADATA_PARAMS(NewProp_EnableProductProtection_MetaData, ARRAY_COUNT(NewProp_EnableProductProtection_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamVersion_MetaData[] = {
				{ "Category", "Steam | Dedicated Server" },
				{ "ModuleRelativePath", "Public/SteamSettings.h" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_SteamVersion = { UE4CodeGen_Private::EPropertyClass::Str, "SteamVersion", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000004001, 1, nullptr, STRUCT_OFFSET(USteamSettings, SteamVersion), METADATA_PARAMS(NewProp_SteamVersion_MetaData, ARRAY_COUNT(NewProp_SteamVersion_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ProductID_MetaData[] = {
				{ "Category", "Steam | Dedicated Server" },
				{ "ModuleRelativePath", "Public/SteamSettings.h" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_ProductID = { UE4CodeGen_Private::EPropertyClass::Str, "ProductID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000004001, 1, nullptr, STRUCT_OFFSET(USteamSettings, ProductID), METADATA_PARAMS(NewProp_ProductID_MetaData, ARRAY_COUNT(NewProp_ProductID_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AppID_MetaData[] = {
				{ "Category", "Steam | Core" },
				{ "ModuleRelativePath", "Public/SteamSettings.h" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_AppID = { UE4CodeGen_Private::EPropertyClass::Str, "AppID", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000004001, 1, nullptr, STRUCT_OFFSET(USteamSettings, AppID), METADATA_PARAMS(NewProp_AppID_MetaData, ARRAY_COUNT(NewProp_AppID_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_EnableProductProtection,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamVersion,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ProductID,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_AppID,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<USteamSettings>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&USteamSettings::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100086u,
				nullptr, 0,
				PropPointers, ARRAY_COUNT(PropPointers),
				"SteamFramework",
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamSettings, 3903961508);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamSettings(Z_Construct_UClass_USteamSettings, &USteamSettings::StaticClass, TEXT("/Script/UESteamFramework"), TEXT("USteamSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
