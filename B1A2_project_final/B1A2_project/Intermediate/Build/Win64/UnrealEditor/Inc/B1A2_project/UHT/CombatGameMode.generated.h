// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/CombatGameMode.h"

#ifdef B1A2_PROJECT_CombatGameMode_generated_h
#error "CombatGameMode.generated.h already included, missing '#pragma once' in CombatGameMode.h"
#endif
#define B1A2_PROJECT_CombatGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACombatGameMode **********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatGameMode_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACombatGameMode(); \
	friend struct Z_Construct_UClass_ACombatGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ACombatGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_ACombatGameMode_NoRegister) \
	DECLARE_SERIALIZER(ACombatGameMode)


#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatGameMode(ACombatGameMode&&) = delete; \
	ACombatGameMode(const ACombatGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACombatGameMode) \
	NO_API virtual ~ACombatGameMode();


#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_12_PROLOG
#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatGameMode;

// ********** End Class ACombatGameMode ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
