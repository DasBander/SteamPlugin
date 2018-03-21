// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UESTEAMFRAMEWORK_SteamSettings_generated_h
#error "SteamSettings.generated.h already included, missing '#pragma once' in SteamSettings.h"
#endif
#define UESTEAMFRAMEWORK_SteamSettings_generated_h

#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_RPC_WRAPPERS
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_RPC_WRAPPERS_NO_PURE_DECLS
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSteamSettings(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamSettings(); \
public: \
	DECLARE_CLASS(USteamSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamSettings) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	static const TCHAR* StaticConfigName() {return TEXT("SteamFramework");} \



#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUSteamSettings(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamSettings(); \
public: \
	DECLARE_CLASS(USteamSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamSettings) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	static const TCHAR* StaticConfigName() {return TEXT("SteamFramework");} \



#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamSettings(USteamSettings&&); \
	NO_API USteamSettings(const USteamSettings&); \
public:


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamSettings(USteamSettings&&); \
	NO_API USteamSettings(const USteamSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamSettings)


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_PRIVATE_PROPERTY_OFFSET
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_23_PROLOG
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_RPC_WRAPPERS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_INCLASS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_INCLASS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h_26_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class SteamSettings."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamSettings_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
