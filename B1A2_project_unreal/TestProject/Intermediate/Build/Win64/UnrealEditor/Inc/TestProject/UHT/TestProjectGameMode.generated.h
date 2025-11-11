// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TestProjectGameMode.h"

#ifdef TESTPROJECT_TestProjectGameMode_generated_h
#error "TestProjectGameMode.generated.h already included, missing '#pragma once' in TestProjectGameMode.h"
#endif
#define TESTPROJECT_TestProjectGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATestProjectGameMode *****************************************************
TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectGameMode_NoRegister();

#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATestProjectGameMode(); \
	friend struct Z_Construct_UClass_ATestProjectGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ATestProjectGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestProject"), Z_Construct_UClass_ATestProjectGameMode_NoRegister) \
	DECLARE_SERIALIZER(ATestProjectGameMode)


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATestProjectGameMode(ATestProjectGameMode&&) = delete; \
	ATestProjectGameMode(const ATestProjectGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestProjectGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestProjectGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATestProjectGameMode) \
	NO_API virtual ~ATestProjectGameMode();


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_12_PROLOG
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATestProjectGameMode;

// ********** End Class ATestProjectGameMode *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
