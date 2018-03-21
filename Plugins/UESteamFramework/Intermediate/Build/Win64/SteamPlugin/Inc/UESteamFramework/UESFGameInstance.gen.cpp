// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/UESFGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUESFGameInstance() {}
// Cross Module References
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_UUESFGameInstance_NoRegister();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_UUESFGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_UESteamFramework();
	UESTEAMFRAMEWORK_API UClass* Z_Construct_UClass_USteamFrameworkMain_NoRegister();
// End Cross Module References
	void UUESFGameInstance::StaticRegisterNativesUUESFGameInstance()
	{
	}
	UClass* Z_Construct_UClass_UUESFGameInstance_NoRegister()
	{
		return UUESFGameInstance::StaticClass();
	}
	UClass* Z_Construct_UClass_UUESFGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UGameInstance,
				(UObject* (*)())Z_Construct_UPackage__Script_UESteamFramework,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "UESFGameInstance.h" },
				{ "ModuleRelativePath", "Public/UESFGameInstance.h" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamFramework_MetaData[] = {
				{ "ModuleRelativePath", "Public/UESFGameInstance.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SteamFramework = { UE4CodeGen_Private::EPropertyClass::Object, "SteamFramework", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000000, 1, nullptr, STRUCT_OFFSET(UUESFGameInstance, SteamFramework), Z_Construct_UClass_USteamFrameworkMain_NoRegister, METADATA_PARAMS(NewProp_SteamFramework_MetaData, ARRAY_COUNT(NewProp_SteamFramework_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_SteamFramework,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UUESFGameInstance>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UUESFGameInstance::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100088u,
				nullptr, 0,
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
	IMPLEMENT_CLASS(UUESFGameInstance, 493630258);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UUESFGameInstance(Z_Construct_UClass_UUESFGameInstance, &UUESFGameInstance::StaticClass, TEXT("/Script/UESteamFramework"), TEXT("UUESFGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UUESFGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
