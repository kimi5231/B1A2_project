// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "B1A2_UnrealProjectCharacter.h"

#ifdef B1A2_UNREALPROJECT_B1A2_UnrealProjectCharacter_generated_h
#error "B1A2_UnrealProjectCharacter.generated.h already included, missing '#pragma once' in B1A2_UnrealProjectCharacter.h"
#endif
#define B1A2_UNREALPROJECT_B1A2_UnrealProjectCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AB1A2_UnrealProjectCharacter *********************************************
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_AB1A2_UnrealProjectCharacter_NoRegister();

#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAB1A2_UnrealProjectCharacter(); \
	friend struct Z_Construct_UClass_AB1A2_UnrealProjectCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_AB1A2_UnrealProjectCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AB1A2_UnrealProjectCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_UnrealProject"), Z_Construct_UClass_AB1A2_UnrealProjectCharacter_NoRegister) \
	DECLARE_SERIALIZER(AB1A2_UnrealProjectCharacter)


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AB1A2_UnrealProjectCharacter(AB1A2_UnrealProjectCharacter&&) = delete; \
	AB1A2_UnrealProjectCharacter(const AB1A2_UnrealProjectCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AB1A2_UnrealProjectCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AB1A2_UnrealProjectCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AB1A2_UnrealProjectCharacter) \
	NO_API virtual ~AB1A2_UnrealProjectCharacter();


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_21_PROLOG
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AB1A2_UnrealProjectCharacter;

// ********** End Class AB1A2_UnrealProjectCharacter ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
