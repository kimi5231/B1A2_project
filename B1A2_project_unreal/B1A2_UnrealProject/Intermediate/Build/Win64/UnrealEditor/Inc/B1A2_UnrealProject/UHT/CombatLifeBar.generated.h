// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/UI/CombatLifeBar.h"

#ifdef B1A2_UNREALPROJECT_CombatLifeBar_generated_h
#error "CombatLifeBar.generated.h already included, missing '#pragma once' in CombatLifeBar.h"
#endif
#define B1A2_UNREALPROJECT_CombatLifeBar_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FLinearColor;

// ********** Begin Class UCombatLifeBar ***********************************************************
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_CALLBACK_WRAPPERS
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_UCombatLifeBar_NoRegister();

#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCombatLifeBar(); \
	friend struct Z_Construct_UClass_UCombatLifeBar_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_UCombatLifeBar_NoRegister(); \
public: \
	DECLARE_CLASS2(UCombatLifeBar, UUserWidget, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/B1A2_UnrealProject"), Z_Construct_UClass_UCombatLifeBar_NoRegister) \
	DECLARE_SERIALIZER(UCombatLifeBar)


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCombatLifeBar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UCombatLifeBar(UCombatLifeBar&&) = delete; \
	UCombatLifeBar(const UCombatLifeBar&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCombatLifeBar); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCombatLifeBar); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCombatLifeBar) \
	NO_API virtual ~UCombatLifeBar();


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_12_PROLOG
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_CALLBACK_WRAPPERS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_INCLASS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UCombatLifeBar;

// ********** End Class UCombatLifeBar *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
