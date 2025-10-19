// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CryptRaiderCameraManager.h"

#ifdef CRYPTRAIDER_CryptRaiderCameraManager_generated_h
#error "CryptRaiderCameraManager.generated.h already included, missing '#pragma once' in CryptRaiderCameraManager.h"
#endif
#define CRYPTRAIDER_CryptRaiderCameraManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACryptRaiderCameraManager ************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderCameraManager_NoRegister();

#define FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACryptRaiderCameraManager(); \
	friend struct Z_Construct_UClass_ACryptRaiderCameraManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderCameraManager_NoRegister(); \
public: \
	DECLARE_CLASS2(ACryptRaiderCameraManager, APlayerCameraManager, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), Z_Construct_UClass_ACryptRaiderCameraManager_NoRegister) \
	DECLARE_SERIALIZER(ACryptRaiderCameraManager)


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACryptRaiderCameraManager(ACryptRaiderCameraManager&&) = delete; \
	ACryptRaiderCameraManager(const ACryptRaiderCameraManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACryptRaiderCameraManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACryptRaiderCameraManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ACryptRaiderCameraManager) \
	NO_API virtual ~ACryptRaiderCameraManager();


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_13_PROLOG
#define FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_16_INCLASS_NO_PURE_DECLS \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACryptRaiderCameraManager;

// ********** End Class ACryptRaiderCameraManager **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
