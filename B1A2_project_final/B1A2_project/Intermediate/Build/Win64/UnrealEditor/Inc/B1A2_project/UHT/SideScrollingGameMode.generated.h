// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_SideScrolling/SideScrollingGameMode.h"

#ifdef B1A2_PROJECT_SideScrollingGameMode_generated_h
#error "SideScrollingGameMode.generated.h already included, missing '#pragma once' in SideScrollingGameMode.h"
#endif
#define B1A2_PROJECT_SideScrollingGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASideScrollingGameMode ***************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingGameMode_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASideScrollingGameMode(); \
	friend struct Z_Construct_UClass_ASideScrollingGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ASideScrollingGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_ASideScrollingGameMode_NoRegister) \
	DECLARE_SERIALIZER(ASideScrollingGameMode)


#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASideScrollingGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASideScrollingGameMode(ASideScrollingGameMode&&) = delete; \
	ASideScrollingGameMode(const ASideScrollingGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASideScrollingGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASideScrollingGameMode); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASideScrollingGameMode) \
	NO_API virtual ~ASideScrollingGameMode();


#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_16_PROLOG
#define FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_19_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASideScrollingGameMode;

// ********** End Class ASideScrollingGameMode *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
