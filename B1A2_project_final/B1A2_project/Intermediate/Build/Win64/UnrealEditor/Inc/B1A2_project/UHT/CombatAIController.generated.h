// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/AI/CombatAIController.h"

#ifdef B1A2_PROJECT_CombatAIController_generated_h
#error "CombatAIController.generated.h already included, missing '#pragma once' in CombatAIController.h"
#endif
#define B1A2_PROJECT_CombatAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACombatAIController ******************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatAIController_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACombatAIController(); \
	friend struct Z_Construct_UClass_ACombatAIController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatAIController_NoRegister(); \
public: \
	DECLARE_CLASS2(ACombatAIController, AAIController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_ACombatAIController_NoRegister) \
	DECLARE_SERIALIZER(ACombatAIController)


#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatAIController(ACombatAIController&&) = delete; \
	ACombatAIController(const ACombatAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatAIController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACombatAIController) \
	NO_API virtual ~ACombatAIController();


#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_14_PROLOG
#define FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_17_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatAIController;

// ********** End Class ACombatAIController ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
