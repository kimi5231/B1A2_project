// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Mover.h"

#ifdef CRYPTRAIDER_Mover_generated_h
#error "Mover.generated.h already included, missing '#pragma once' in Mover.h"
#endif
#define CRYPTRAIDER_Mover_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UMover *******************************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_UMover_NoRegister();

#define FID_CryptRaider_Source_CryptRaider_Mover_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMover(); \
	friend struct Z_Construct_UClass_UMover_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend CRYPTRAIDER_API UClass* Z_Construct_UClass_UMover_NoRegister(); \
public: \
	DECLARE_CLASS2(UMover, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CryptRaider"), Z_Construct_UClass_UMover_NoRegister) \
	DECLARE_SERIALIZER(UMover)


#define FID_CryptRaider_Source_CryptRaider_Mover_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMover(UMover&&) = delete; \
	UMover(const UMover&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMover); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMover); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMover) \
	NO_API virtual ~UMover();


#define FID_CryptRaider_Source_CryptRaider_Mover_h_10_PROLOG
#define FID_CryptRaider_Source_CryptRaider_Mover_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_CryptRaider_Source_CryptRaider_Mover_h_13_INCLASS_NO_PURE_DECLS \
	FID_CryptRaider_Source_CryptRaider_Mover_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMover;

// ********** End Class UMover *********************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_CryptRaider_Source_CryptRaider_Mover_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
