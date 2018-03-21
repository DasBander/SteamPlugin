// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class USteamFrameworkMain;
struct FSteamFriend;
struct FSteamID;
class UTexture2D;
#ifdef UESTEAMFRAMEWORK_SteamFrameworkHelper_generated_h
#error "SteamFrameworkHelper.generated.h already included, missing '#pragma once' in SteamFrameworkHelper.h"
#endif
#define UESTEAMFRAMEWORK_SteamFrameworkHelper_generated_h

#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSteamInterface) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(USteamFrameworkMain**)Z_Param__Result=USteamFrameworkHelper::GetSteamInterface(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFriendsList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FSteamFriend>*)Z_Param__Result=USteamFrameworkHelper::GetFriendsList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUsername) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USteamFrameworkHelper::GetUsername(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamAvatar) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTexture2D**)Z_Param__Result=USteamFrameworkHelper::GetSteamAvatar(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMakeSteamID) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=USteamFrameworkHelper::MakeSteamID(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSteamIDToString) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USteamFrameworkHelper::SteamIDToString(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserSteamID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=USteamFrameworkHelper::GetUserSteamID(); \
		P_NATIVE_END; \
	}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSteamInterface) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(USteamFrameworkMain**)Z_Param__Result=USteamFrameworkHelper::GetSteamInterface(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFriendsList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FSteamFriend>*)Z_Param__Result=USteamFrameworkHelper::GetFriendsList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUsername) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USteamFrameworkHelper::GetUsername(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamAvatar) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTexture2D**)Z_Param__Result=USteamFrameworkHelper::GetSteamAvatar(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMakeSteamID) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=USteamFrameworkHelper::MakeSteamID(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSteamIDToString) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_SteamID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=USteamFrameworkHelper::SteamIDToString(Z_Param_SteamID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserSteamID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=USteamFrameworkHelper::GetUserSteamID(); \
		P_NATIVE_END; \
	}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSteamFrameworkHelper(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamFrameworkHelper(); \
public: \
	DECLARE_CLASS(USteamFrameworkHelper, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamFrameworkHelper) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUSteamFrameworkHelper(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamFrameworkHelper(); \
public: \
	DECLARE_CLASS(USteamFrameworkHelper, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamFrameworkHelper) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamFrameworkHelper(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamFrameworkHelper) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamFrameworkHelper); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamFrameworkHelper); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamFrameworkHelper(USteamFrameworkHelper&&); \
	NO_API USteamFrameworkHelper(const USteamFrameworkHelper&); \
public:


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamFrameworkHelper(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamFrameworkHelper(USteamFrameworkHelper&&); \
	NO_API USteamFrameworkHelper(const USteamFrameworkHelper&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamFrameworkHelper); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamFrameworkHelper); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamFrameworkHelper)


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_PRIVATE_PROPERTY_OFFSET
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_16_PROLOG
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_RPC_WRAPPERS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_INCLASS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_INCLASS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkHelper_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
