// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Platforming/PlatformingCharacter.h"

#ifdef B1A2_PROJECT_PlatformingCharacter_generated_h
#error "PlatformingCharacter.generated.h already included, missing '#pragma once' in PlatformingCharacter.h"
#endif
#define B1A2_PROJECT_PlatformingCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APlatformingCharacter ****************************************************
#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHasWallJumped); \
	DECLARE_FUNCTION(execHasDoubleJumped); \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoDash); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_CALLBACK_WRAPPERS
B1A2_PROJECT_API UClass* Z_Construct_UClass_APlatformingCharacter_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlatformingCharacter(); \
	friend struct Z_Construct_UClass_APlatformingCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_APlatformingCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(APlatformingCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_APlatformingCharacter_NoRegister) \
	DECLARE_SERIALIZER(APlatformingCharacter)


#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APlatformingCharacter(APlatformingCharacter&&) = delete; \
	APlatformingCharacter(const APlatformingCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlatformingCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlatformingCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(APlatformingCharacter) \
	NO_API virtual ~APlatformingCharacter();


#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_25_PROLOG
#define FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_CALLBACK_WRAPPERS \
	FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APlatformingCharacter;

// ********** End Class APlatformingCharacter ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_Variant_Platforming_PlatformingCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
