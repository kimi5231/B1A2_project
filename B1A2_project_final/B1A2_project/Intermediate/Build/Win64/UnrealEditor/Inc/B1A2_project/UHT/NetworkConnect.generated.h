// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkConnect.h"

#ifdef B1A2_PROJECT_NetworkConnect_generated_h
#error "NetworkConnect.generated.h already included, missing '#pragma once' in NetworkConnect.h"
#endif
#define B1A2_PROJECT_NetworkConnect_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNetworkConnect **********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_UNetworkConnect_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNetworkConnect(); \
	friend struct Z_Construct_UClass_UNetworkConnect_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_UNetworkConnect_NoRegister(); \
public: \
	DECLARE_CLASS2(UNetworkConnect, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_UNetworkConnect_NoRegister) \
	DECLARE_SERIALIZER(UNetworkConnect)


#define FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNetworkConnect(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNetworkConnect(UNetworkConnect&&) = delete; \
	UNetworkConnect(const UNetworkConnect&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNetworkConnect); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNetworkConnect); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNetworkConnect) \
	NO_API virtual ~UNetworkConnect();


#define FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_12_PROLOG
#define FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_15_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_NetworkConnect_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNetworkConnect;

// ********** End Class UNetworkConnect ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_NetworkConnect_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
