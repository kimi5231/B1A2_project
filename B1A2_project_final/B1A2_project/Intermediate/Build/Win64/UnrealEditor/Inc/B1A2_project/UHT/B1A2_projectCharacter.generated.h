// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "B1A2_projectCharacter.h"

#ifdef B1A2_PROJECT_B1A2_projectCharacter_generated_h
#error "B1A2_projectCharacter.generated.h already included, missing '#pragma once' in B1A2_projectCharacter.h"
#endif
#define B1A2_PROJECT_B1A2_projectCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AB1A2_projectCharacter ***************************************************
#define FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectCharacter_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAB1A2_projectCharacter(); \
	friend struct Z_Construct_UClass_AB1A2_projectCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AB1A2_projectCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_AB1A2_projectCharacter_NoRegister) \
	DECLARE_SERIALIZER(AB1A2_projectCharacter)


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AB1A2_projectCharacter(AB1A2_projectCharacter&&) = delete; \
	AB1A2_projectCharacter(const AB1A2_projectCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AB1A2_projectCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AB1A2_projectCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AB1A2_projectCharacter) \
	NO_API virtual ~AB1A2_projectCharacter();


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_21_PROLOG
#define FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AB1A2_projectCharacter;

// ********** End Class AB1A2_projectCharacter *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_B1A2_projectCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
