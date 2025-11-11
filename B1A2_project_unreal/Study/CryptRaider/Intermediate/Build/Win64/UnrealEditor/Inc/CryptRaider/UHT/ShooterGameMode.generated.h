// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Shooter/ShooterGameMode.h"

#ifdef CRYPTRAIDER_ShooterGameMode_generated_h
#error "ShooterGameMode.generated.h already included, missing '#pragma once' in ShooterGameMode.h"
#endif
#define CRYPTRAIDER_ShooterGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AShooterGameMode *********************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_AShooterGameMode_NoRegister();

#define FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAShooterGameMode(); \
	friend struct Z_Construct_UClass_AShooterGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CRYPTRAIDER_API UClass* Z_Construct_UClass_AShooterGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(AShooterGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), Z_Construct_UClass_AShooterGameMode_NoRegister) \
	DECLARE_SERIALIZER(AShooterGameMode)


#define FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AShooterGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AShooterGameMode(AShooterGameMode&&) = delete; \
	AShooterGameMode(const AShooterGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterGameMode); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AShooterGameMode) \
	NO_API virtual ~AShooterGameMode();


#define FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_16_PROLOG
#define FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_19_INCLASS_NO_PURE_DECLS \
	FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AShooterGameMode;

// ********** End Class AShooterGameMode ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_Variant_Shooter_ShooterGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
