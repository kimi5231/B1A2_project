// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TestProjectPlayerController.h"

#ifdef TESTPROJECT_TestProjectPlayerController_generated_h
#error "TestProjectPlayerController.generated.h already included, missing '#pragma once' in TestProjectPlayerController.h"
#endif
#define TESTPROJECT_TestProjectPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATestProjectPlayerController *********************************************
TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectPlayerController_NoRegister();

#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATestProjectPlayerController(); \
	friend struct Z_Construct_UClass_ATestProjectPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ATestProjectPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestProject"), Z_Construct_UClass_ATestProjectPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ATestProjectPlayerController)


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATestProjectPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATestProjectPlayerController(ATestProjectPlayerController&&) = delete; \
	ATestProjectPlayerController(const ATestProjectPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATestProjectPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATestProjectPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATestProjectPlayerController) \
	NO_API virtual ~ATestProjectPlayerController();


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_16_PROLOG
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATestProjectPlayerController;

// ********** End Class ATestProjectPlayerController ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
