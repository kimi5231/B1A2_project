// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "B1A2_projectPlayerController.h"

#ifdef B1A2_PROJECT_B1A2_projectPlayerController_generated_h
#error "B1A2_projectPlayerController.generated.h already included, missing '#pragma once' in B1A2_projectPlayerController.h"
#endif
#define B1A2_PROJECT_B1A2_projectPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AB1A2_projectPlayerController ********************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectPlayerController_NoRegister();

#define FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAB1A2_projectPlayerController(); \
	friend struct Z_Construct_UClass_AB1A2_projectPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_PROJECT_API UClass* Z_Construct_UClass_AB1A2_projectPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AB1A2_projectPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_project"), Z_Construct_UClass_AB1A2_projectPlayerController_NoRegister) \
	DECLARE_SERIALIZER(AB1A2_projectPlayerController)


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AB1A2_projectPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AB1A2_projectPlayerController(AB1A2_projectPlayerController&&) = delete; \
	AB1A2_projectPlayerController(const AB1A2_projectPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AB1A2_projectPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AB1A2_projectPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AB1A2_projectPlayerController) \
	NO_API virtual ~AB1A2_projectPlayerController();


#define FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_16_PROLOG
#define FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_19_INCLASS_NO_PURE_DECLS \
	FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AB1A2_projectPlayerController;

// ********** End Class AB1A2_projectPlayerController **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_project_Source_B1A2_project_B1A2_projectPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
