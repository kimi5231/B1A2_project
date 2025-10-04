// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "B1A2_projectGameMode.h"

#ifdef B1A2_PROJECT_B1A2_projectGameMode_generated_h
#error "B1A2_projectGameMode.generated.h already included, missing '#pragma once' in B1A2_projectGameMode.h"
#endif
#define B1A2_PROJECT_B1A2_projectGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AB1A2_projectGameMode ****************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectGameMode_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAB1A2_projectGameMode(); \
	friend struct Z_Construct_UClass_AB1A2_projectGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(AB1A2_projectGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_AB1A2_projectGameMode_NoRegister) \
	DECLARE_SERIALIZER(AB1A2_projectGameMode)


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AB1A2_projectGameMode(AB1A2_projectGameMode&&) = delete; \
	AB1A2_projectGameMode(const AB1A2_projectGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AB1A2_projectGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AB1A2_projectGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AB1A2_projectGameMode) \
	NO_API virtual ~AB1A2_projectGameMode();


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_12_PROLOG
#define FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AB1A2_projectGameMode;

// ********** End Class AB1A2_projectGameMode ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_B1A2_projectGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
