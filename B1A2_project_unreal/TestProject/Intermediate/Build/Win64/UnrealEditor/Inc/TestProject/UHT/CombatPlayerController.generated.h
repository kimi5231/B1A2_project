// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/CombatPlayerController.h"

#ifdef TESTPROJECT_CombatPlayerController_generated_h
#error "CombatPlayerController.generated.h already included, missing '#pragma once' in CombatPlayerController.h"
#endif
#define TESTPROJECT_CombatPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin Class ACombatPlayerController **************************************************
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnPawnDestroyed);


TESTPROJECT_API UClass* Z_Construct_UClass_ACombatPlayerController_NoRegister();

#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACombatPlayerController(); \
	friend struct Z_Construct_UClass_ACombatPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend TESTPROJECT_API UClass* Z_Construct_UClass_ACombatPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ACombatPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestProject"), Z_Construct_UClass_ACombatPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ACombatPlayerController)


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACombatPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatPlayerController(ACombatPlayerController&&) = delete; \
	ACombatPlayerController(const ACombatPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACombatPlayerController) \
	NO_API virtual ~ACombatPlayerController();


#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_17_PROLOG
#define FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatPlayerController;

// ********** End Class ACombatPlayerController ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_CombatPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
