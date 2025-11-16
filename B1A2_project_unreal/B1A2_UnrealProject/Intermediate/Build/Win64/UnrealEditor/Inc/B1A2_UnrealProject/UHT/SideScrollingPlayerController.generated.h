// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_SideScrolling/SideScrollingPlayerController.h"

#ifdef B1A2_UNREALPROJECT_SideScrollingPlayerController_generated_h
#error "SideScrollingPlayerController.generated.h already included, missing '#pragma once' in SideScrollingPlayerController.h"
#endif
#define B1A2_UNREALPROJECT_SideScrollingPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin Class ASideScrollingPlayerController *******************************************
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnPawnDestroyed);


B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPlayerController_NoRegister();

#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASideScrollingPlayerController(); \
	friend struct Z_Construct_UClass_ASideScrollingPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ASideScrollingPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_UnrealProject"), Z_Construct_UClass_ASideScrollingPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ASideScrollingPlayerController)


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASideScrollingPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASideScrollingPlayerController(ASideScrollingPlayerController&&) = delete; \
	ASideScrollingPlayerController(const ASideScrollingPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASideScrollingPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASideScrollingPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASideScrollingPlayerController) \
	NO_API virtual ~ASideScrollingPlayerController();


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_18_PROLOG
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_INCLASS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASideScrollingPlayerController;

// ********** End Class ASideScrollingPlayerController *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
