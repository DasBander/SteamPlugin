// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLobbyResult;
struct FSteamFriend;
struct FSteamID;
struct FLobbyData;
#ifdef UESTEAMFRAMEWORK_SteamFrameworkMain_generated_h
#error "SteamFrameworkMain.generated.h already included, missing '#pragma once' in SteamFrameworkMain.h"
#endif
#define UESTEAMFRAMEWORK_SteamFrameworkMain_generated_h

#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_18_DELEGATE \
static inline void FOnLobbyDataUpdateCallback_DelegateWrapper(const FMulticastScriptDelegate& OnLobbyDataUpdateCallback) \
{ \
	OnLobbyDataUpdateCallback.ProcessMulticastDelegate<UObject>(NULL); \
}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_17_DELEGATE \
struct _Script_UESteamFramework_eventOnLobbyCreatedCallback_Parms \
{ \
	FLobbyResult Result; \
}; \
static inline void FOnLobbyCreatedCallback_DelegateWrapper(const FMulticastScriptDelegate& OnLobbyCreatedCallback, FLobbyResult Result) \
{ \
	_Script_UESteamFramework_eventOnLobbyCreatedCallback_Parms Parms; \
	Parms.Result=Result; \
	OnLobbyCreatedCallback.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetLobbyMembers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FSteamFriend>*)Z_Param__Result=this->GetLobbyMembers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetLobbyOwner) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=this->GetLobbyOwner(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsLobbyOwner) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->IsLobbyOwner(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execJoinLobby) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_LobbyID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->JoinLobby(Z_Param_LobbyID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateLobby) \
	{ \
		P_GET_STRUCT(FLobbyData,Z_Param_LobbyData); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CreateLobby(Z_Param_LobbyData); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLeaveLobby) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LeaveLobby(); \
		P_NATIVE_END; \
	}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetLobbyMembers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FSteamFriend>*)Z_Param__Result=this->GetLobbyMembers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetLobbyOwner) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FSteamID*)Z_Param__Result=this->GetLobbyOwner(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsLobbyOwner) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->IsLobbyOwner(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execJoinLobby) \
	{ \
		P_GET_STRUCT(FSteamID,Z_Param_LobbyID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->JoinLobby(Z_Param_LobbyID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateLobby) \
	{ \
		P_GET_STRUCT(FLobbyData,Z_Param_LobbyData); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CreateLobby(Z_Param_LobbyData); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLeaveLobby) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LeaveLobby(); \
		P_NATIVE_END; \
	}


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSteamFrameworkMain(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamFrameworkMain(); \
public: \
	DECLARE_CLASS(USteamFrameworkMain, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamFrameworkMain) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUSteamFrameworkMain(); \
	friend UESTEAMFRAMEWORK_API class UClass* Z_Construct_UClass_USteamFrameworkMain(); \
public: \
	DECLARE_CLASS(USteamFrameworkMain, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UESteamFramework"), NO_API) \
	DECLARE_SERIALIZER(USteamFrameworkMain) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamFrameworkMain(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamFrameworkMain) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamFrameworkMain); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamFrameworkMain); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamFrameworkMain(USteamFrameworkMain&&); \
	NO_API USteamFrameworkMain(const USteamFrameworkMain&); \
public:


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamFrameworkMain(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamFrameworkMain(USteamFrameworkMain&&); \
	NO_API USteamFrameworkMain(const USteamFrameworkMain&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamFrameworkMain); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamFrameworkMain); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamFrameworkMain)


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_PRIVATE_PROPERTY_OFFSET
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_25_PROLOG
#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_RPC_WRAPPERS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_INCLASS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_PRIVATE_PROPERTY_OFFSET \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_INCLASS_NO_PURE_DECLS \
	SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h_28_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class SteamFrameworkMain."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SteamPlugin_Plugins_UESteamFramework_Source_UESteamFramework_Public_SteamFrameworkMain_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
