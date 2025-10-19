// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CryptRaiderGameMode.h"

#ifdef CRYPTRAIDER_CryptRaiderGameMode_generated_h
#error "CryptRaiderGameMode.generated.h already included, missing '#pragma once' in CryptRaiderGameMode.h"
#endif
#define CRYPTRAIDER_CryptRaiderGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACryptRaiderGameMode *****************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderGameMode_NoRegister();

#define FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACryptRaiderGameMode(); \
	friend struct Z_Construct_UClass_ACryptRaiderGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ACryptRaiderGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), Z_Construct_UClass_ACryptRaiderGameMode_NoRegister) \
	DECLARE_SERIALIZER(ACryptRaiderGameMode)


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACryptRaiderGameMode(ACryptRaiderGameMode&&) = delete; \
	ACryptRaiderGameMode(const ACryptRaiderGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACryptRaiderGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACryptRaiderGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACryptRaiderGameMode) \
	NO_API virtual ~ACryptRaiderGameMode();


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_12_PROLOG
#define FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACryptRaiderGameMode;

// ********** End Class ACryptRaiderGameMode *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
