// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatAttacker.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatAttacker() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatAttacker();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatAttacker_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface UCombatAttacker Function CheckChargedAttack **************************
struct Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a charged attack's check to loop the charge animation. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a charged attack's check to loop the charge animation. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatAttacker, nullptr, "CheckChargedAttack", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatAttacker::execCheckChargedAttack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckChargedAttack();
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function CheckChargedAttack ****************************

// ********** Begin Interface UCombatAttacker Function CheckCombo **********************************
struct Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a combo attack's check to continue the string. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a combo attack's check to continue the string. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatAttacker, nullptr, "CheckCombo", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UCombatAttacker_CheckCombo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatAttacker::execCheckCombo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckCombo();
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function CheckCombo ************************************

// ********** Begin Interface UCombatAttacker Function DoAttackTrace *******************************
struct Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics
{
	struct CombatAttacker_eventDoAttackTrace_Parms
	{
		FName DamageSourceBone;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs an attack's collision check. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs an attack's collision check. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_DamageSourceBone;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::NewProp_DamageSourceBone = { "DamageSourceBone", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatAttacker_eventDoAttackTrace_Parms, DamageSourceBone), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::NewProp_DamageSourceBone,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatAttacker, nullptr, "DoAttackTrace", Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::CombatAttacker_eventDoAttackTrace_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::CombatAttacker_eventDoAttackTrace_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatAttacker_DoAttackTrace()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatAttacker::execDoAttackTrace)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_DamageSourceBone);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoAttackTrace(Z_Param_DamageSourceBone);
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function DoAttackTrace *********************************

// ********** Begin Interface UCombatAttacker ******************************************************
void UCombatAttacker::StaticRegisterNativesUCombatAttacker()
{
	UClass* Class = UCombatAttacker::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "CheckChargedAttack", &ICombatAttacker::execCheckChargedAttack },
		{ "CheckCombo", &ICombatAttacker::execCheckCombo },
		{ "DoAttackTrace", &ICombatAttacker::execDoAttackTrace },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatAttacker;
UClass* UCombatAttacker::GetPrivateStaticClass()
{
	using TClass = UCombatAttacker;
	if (!Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatAttacker"),
			Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton,
			StaticRegisterNativesUCombatAttacker,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton;
}
UClass* Z_Construct_UClass_UCombatAttacker_NoRegister()
{
	return UCombatAttacker::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCombatAttacker_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack, "CheckChargedAttack" }, // 440216487
		{ &Z_Construct_UFunction_UCombatAttacker_CheckCombo, "CheckCombo" }, // 3038173153
		{ &Z_Construct_UFunction_UCombatAttacker_DoAttackTrace, "DoAttackTrace" }, // 343399441
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ICombatAttacker>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCombatAttacker_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatAttacker_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCombatAttacker_Statics::ClassParams = {
	&UCombatAttacker::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatAttacker_Statics::Class_MetaDataParams), Z_Construct_UClass_UCombatAttacker_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCombatAttacker()
{
	if (!Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton, Z_Construct_UClass_UCombatAttacker_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton;
}
UCombatAttacker::UCombatAttacker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCombatAttacker);
// ********** End Interface UCombatAttacker ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatAttacker_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatAttacker, UCombatAttacker::StaticClass, TEXT("UCombatAttacker"), &Z_Registration_Info_UClass_UCombatAttacker, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatAttacker), 16140234U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatAttacker_h__Script_TestProject_3514709307(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatAttacker_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatAttacker_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
