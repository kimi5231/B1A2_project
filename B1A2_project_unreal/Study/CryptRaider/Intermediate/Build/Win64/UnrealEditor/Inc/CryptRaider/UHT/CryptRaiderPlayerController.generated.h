// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CryptRaiderPlayerController.h"

#ifdef CRYPTRAIDER_CryptRaiderPlayerController_generated_h
#error "CryptRaiderPlayerController.generated.h already included, missing '#pragma once' in CryptRaiderPlayerController.h"
#endif
#define CRYPTRAIDER_CryptRaiderPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACryptRaiderPlayerController *********************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderPlayerController_NoRegister();

#define FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACryptRaiderPlayerController(); \
	friend struct Z_Construct_UClass_ACryptRaiderPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ACryptRaiderPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), Z_Construct_UClass_ACryptRaiderPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ACryptRaiderPlayerController)


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACryptRaiderPlayerController(ACryptRaiderPlayerController&&) = delete; \
	ACryptRaiderPlayerController(const ACryptRaiderPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACryptRaiderPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACryptRaiderPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACryptRaiderPlayerController) \
	NO_API virtual ~ACryptRaiderPlayerController();


#define FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_17_PROLOG
#define FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACryptRaiderPlayerController;

// ********** End Class ACryptRaiderPlayerController ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_CryptRaider_Source_CryptRaider_CryptRaiderPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
