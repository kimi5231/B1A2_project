// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TestProjectCharacter.h"

#ifdef TESTPROJECT_TestProjectCharacter_generated_h
#error "TestProjectCharacter.generated.h already included, missing '#pragma once' in TestProjectCharacter.h"
#endif
#define TESTPROJECT_TestProjectCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATestProjectCharacter ****************************************************
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectCharacter_NoRegister();

#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATestProjectCharacter(); \
	friend struct Z_Construct_UClass_ATestProjectCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ATestProjectCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestProject"), Z_Construct_UClass_ATestProjectCharacter_NoRegister) \
	DECLARE_SERIALIZER(ATestProjectCharacter)


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATestProjectCharacter(ATestProjectCharacter&&) = delete; \
	ATestProjectCharacter(const ATestProjectCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestProjectCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestProjectCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATestProjectCharacter) \
	NO_API virtual ~ATestProjectCharacter();


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_21_PROLOG
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATestProjectCharacter;

// ********** End Class ATestProjectCharacter ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
