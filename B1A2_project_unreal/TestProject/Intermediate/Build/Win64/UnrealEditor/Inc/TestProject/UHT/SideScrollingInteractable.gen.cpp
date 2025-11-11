// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingInteractable.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingInteractable() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_USideScrollingInteractable();
TESTPROJECT_API UClass* Z_Construct_UClass_USideScrollingInteractable_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface USideScrollingInteractable Function Interaction **********************
struct Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics
{
	struct SideScrollingInteractable_eventInteraction_Parms
	{
		AActor* Interactor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Interactable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Triggers an interaction by the provided Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Interfaces/SideScrollingInteractable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Triggers an interaction by the provided Actor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Interactor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::NewProp_Interactor = { "Interactor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingInteractable_eventInteraction_Parms, Interactor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::NewProp_Interactor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USideScrollingInteractable, nullptr, "Interaction", Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::PropPointers), sizeof(Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::SideScrollingInteractable_eventInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::Function_MetaDataParams), Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::SideScrollingInteractable_eventInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USideScrollingInteractable_Interaction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISideScrollingInteractable::execInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_Interactor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Interaction(Z_Param_Interactor);
	P_NATIVE_END;
}
// ********** End Interface USideScrollingInteractable Function Interaction ************************

// ********** Begin Interface USideScrollingInteractable *******************************************
void USideScrollingInteractable::StaticRegisterNativesUSideScrollingInteractable()
{
	UClass* Class = USideScrollingInteractable::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Interaction", &ISideScrollingInteractable::execInteraction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USideScrollingInteractable;
UClass* USideScrollingInteractable::GetPrivateStaticClass()
{
	using TClass = USideScrollingInteractable;
	if (!Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingInteractable"),
			Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton,
			StaticRegisterNativesUSideScrollingInteractable,
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
	return Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton;
}
UClass* Z_Construct_UClass_USideScrollingInteractable_NoRegister()
{
	return USideScrollingInteractable::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USideScrollingInteractable_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Interfaces/SideScrollingInteractable.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USideScrollingInteractable_Interaction, "Interaction" }, // 2044009075
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ISideScrollingInteractable>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USideScrollingInteractable_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USideScrollingInteractable_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USideScrollingInteractable_Statics::ClassParams = {
	&USideScrollingInteractable::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USideScrollingInteractable_Statics::Class_MetaDataParams), Z_Construct_UClass_USideScrollingInteractable_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USideScrollingInteractable()
{
	if (!Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton, Z_Construct_UClass_USideScrollingInteractable_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton;
}
USideScrollingInteractable::USideScrollingInteractable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USideScrollingInteractable);
// ********** End Interface USideScrollingInteractable *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USideScrollingInteractable, USideScrollingInteractable::StaticClass, TEXT("USideScrollingInteractable"), &Z_Registration_Info_UClass_USideScrollingInteractable, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USideScrollingInteractable), 3868912052U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_TestProject_2304892731(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
