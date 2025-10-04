// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_SideScrolling/SideScrollingCharacter.h"

#ifdef B1A2_PROJECT_SideScrollingCharacter_generated_h
#error "SideScrollingCharacter.generated.h already included, missing '#pragma once' in SideScrollingCharacter.h"
#endif
#define B1A2_PROJECT_SideScrollingCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASideScrollingCharacter **************************************************
#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHasWallJumped); \
	DECLARE_FUNCTION(execHasDoubleJumped); \
	DECLARE_FUNCTION(execDoInteract); \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoDrop); \
	DECLARE_FUNCTION(execDoMove);


B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingCharacter_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASideScrollingCharacter(); \
	friend struct Z_Construct_UClass_ASideScrollingCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ASideScrollingCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_ASideScrollingCharacter_NoRegister) \
	DECLARE_SERIALIZER(ASideScrollingCharacter)


#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASideScrollingCharacter(ASideScrollingCharacter&&) = delete; \
	ASideScrollingCharacter(const ASideScrollingCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASideScrollingCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASideScrollingCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ASideScrollingCharacter) \
	NO_API virtual ~ASideScrollingCharacter();


#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_16_PROLOG
#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASideScrollingCharacter;

// ********** End Class ASideScrollingCharacter ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
