// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_SideScrolling/AI/SideScrollingNPC.h"

#ifdef B1A2_UNREALPROJECT_SideScrollingNPC_generated_h
#error "SideScrollingNPC.generated.h already included, missing '#pragma once' in SideScrollingNPC.h"
#endif
#define B1A2_UNREALPROJECT_SideScrollingNPC_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASideScrollingNPC ********************************************************
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingNPC_NoRegister();

#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASideScrollingNPC(); \
	friend struct Z_Construct_UClass_ASideScrollingNPC_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingNPC_NoRegister(); \
public: \
	DECLARE_CLASS2(ASideScrollingNPC, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/B1A2_UnrealProject"), Z_Construct_UClass_ASideScrollingNPC_NoRegister) \
	DECLARE_SERIALIZER(ASideScrollingNPC) \
	virtual UObject* _getUObject() const override { return const_cast<ASideScrollingNPC*>(this); }


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASideScrollingNPC(ASideScrollingNPC&&) = delete; \
	ASideScrollingNPC(const ASideScrollingNPC&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASideScrollingNPC); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASideScrollingNPC); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ASideScrollingNPC) \
	NO_API virtual ~ASideScrollingNPC();


#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_15_PROLOG
#define FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_18_INCLASS_NO_PURE_DECLS \
	FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASideScrollingNPC;

// ********** End Class ASideScrollingNPC **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
