// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatActivatable.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatActivatable() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatActivatable();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatActivatable_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface UCombatActivatable Function ActivateInteraction **********************
struct Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics
{
	struct CombatActivatable_eventActivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Activates the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Activates the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventActivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatActivatable, nullptr, "ActivateInteraction", Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::CombatActivatable_eventActivateInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::CombatActivatable_eventActivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_ActivateInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatActivatable::execActivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function ActivateInteraction ************************

// ********** Begin Interface UCombatActivatable Function DeactivateInteraction ********************
struct Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics
{
	struct CombatActivatable_eventDeactivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deactivates the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deactivates the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventDeactivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatActivatable, nullptr, "DeactivateInteraction", Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::CombatActivatable_eventDeactivateInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::CombatActivatable_eventDeactivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatActivatable::execDeactivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DeactivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function DeactivateInteraction **********************

// ********** Begin Interface UCombatActivatable Function ToggleInteraction ************************
struct Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics
{
	struct CombatActivatable_eventToggleInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Toggles the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Toggles the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventToggleInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatActivatable, nullptr, "ToggleInteraction", Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::CombatActivatable_eventToggleInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::CombatActivatable_eventToggleInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_ToggleInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ICombatActivatable::execToggleInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function ToggleInteraction **************************

// ********** Begin Interface UCombatActivatable ***************************************************
void UCombatActivatable::StaticRegisterNativesUCombatActivatable()
{
	UClass* Class = UCombatActivatable::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ActivateInteraction", &ICombatActivatable::execActivateInteraction },
		{ "DeactivateInteraction", &ICombatActivatable::execDeactivateInteraction },
		{ "ToggleInteraction", &ICombatActivatable::execToggleInteraction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatActivatable;
UClass* UCombatActivatable::GetPrivateStaticClass()
{
	using TClass = UCombatActivatable;
	if (!Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatActivatable"),
			Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton,
			StaticRegisterNativesUCombatActivatable,
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
	return Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton;
}
UClass* Z_Construct_UClass_UCombatActivatable_NoRegister()
{
	return UCombatActivatable::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCombatActivatable_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatActivatable_ActivateInteraction, "ActivateInteraction" }, // 1405629491
		{ &Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction, "DeactivateInteraction" }, // 2646178977
		{ &Z_Construct_UFunction_UCombatActivatable_ToggleInteraction, "ToggleInteraction" }, // 235086024
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ICombatActivatable>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCombatActivatable_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatActivatable_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCombatActivatable_Statics::ClassParams = {
	&UCombatActivatable::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatActivatable_Statics::Class_MetaDataParams), Z_Construct_UClass_UCombatActivatable_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCombatActivatable()
{
	if (!Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton, Z_Construct_UClass_UCombatActivatable_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton;
}
UCombatActivatable::UCombatActivatable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCombatActivatable);
// ********** End Interface UCombatActivatable *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatActivatable_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatActivatable, UCombatActivatable::StaticClass, TEXT("UCombatActivatable"), &Z_Registration_Info_UClass_UCombatActivatable, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatActivatable), 329663446U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatActivatable_h__Script_TestProject_3020165018(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatActivatable_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Interfaces_CombatActivatable_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
