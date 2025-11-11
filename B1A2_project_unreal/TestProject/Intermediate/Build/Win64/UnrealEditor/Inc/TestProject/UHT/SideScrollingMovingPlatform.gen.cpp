// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingMovingPlatform.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingMovingPlatform() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingMovingPlatform();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingMovingPlatform_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_USideScrollingInteractable_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingMovingPlatform Function BP_MoveToTarget ********************
static FName NAME_ASideScrollingMovingPlatform_BP_MoveToTarget = FName(TEXT("BP_MoveToTarget"));
void ASideScrollingMovingPlatform::BP_MoveToTarget()
{
	UFunction* Func = FindFunctionChecked(NAME_ASideScrollingMovingPlatform_BP_MoveToTarget);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint code to do the actual platform movement */" },
#endif
		{ "DisplayName", "Move to Target" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint code to do the actual platform movement" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASideScrollingMovingPlatform, nullptr, "BP_MoveToTarget", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ASideScrollingMovingPlatform Function BP_MoveToTarget **********************

// ********** Begin Class ASideScrollingMovingPlatform Function ResetInteraction *******************
struct Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Resets the interaction state. Must be called from BP code to reset the platform */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Resets the interaction state. Must be called from BP code to reset the platform" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASideScrollingMovingPlatform, nullptr, "ResetInteraction", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASideScrollingMovingPlatform::execResetInteraction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetInteraction();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingMovingPlatform Function ResetInteraction *********************

// ********** Begin Class ASideScrollingMovingPlatform *********************************************
void ASideScrollingMovingPlatform::StaticRegisterNativesASideScrollingMovingPlatform()
{
	UClass* Class = ASideScrollingMovingPlatform::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ResetInteraction", &ASideScrollingMovingPlatform::execResetInteraction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingMovingPlatform;
UClass* ASideScrollingMovingPlatform::GetPrivateStaticClass()
{
	using TClass = ASideScrollingMovingPlatform;
	if (!Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingMovingPlatform"),
			Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton,
			StaticRegisterNativesASideScrollingMovingPlatform,
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
	return Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingMovingPlatform_NoRegister()
{
	return ASideScrollingMovingPlatform::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingMovingPlatform_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple moving platform that can be triggered through interactions by other actors.\n *  The actual movement is performed by Blueprint code through latent execution nodes.\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple moving platform that can be triggered through interactions by other actors.\nThe actual movement is performed by Blueprint code through latent execution nodes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlatformTarget_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Destination of the platform in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Destination of the platform in world space" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveDuration_MetaData[] = {
		{ "Category", "Moving Platform" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time for the platform to move to the destination */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time for the platform to move to the destination" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOneShot_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If this is true, the platform will only move once. */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If this is true, the platform will only move once." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlatformTarget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveDuration;
	static void NewProp_bOneShot_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOneShot;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget, "BP_MoveToTarget" }, // 4215560712
		{ &Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction, "ResetInteraction" }, // 938179635
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingMovingPlatform>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_PlatformTarget = { "PlatformTarget", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingMovingPlatform, PlatformTarget), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlatformTarget_MetaData), NewProp_PlatformTarget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_MoveDuration = { "MoveDuration", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingMovingPlatform, MoveDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveDuration_MetaData), NewProp_MoveDuration_MetaData) };
void Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_bOneShot_SetBit(void* Obj)
{
	((ASideScrollingMovingPlatform*)Obj)->bOneShot = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_bOneShot = { "bOneShot", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASideScrollingMovingPlatform), &Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_bOneShot_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOneShot_MetaData), NewProp_bOneShot_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_PlatformTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_MoveDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::NewProp_bOneShot,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_USideScrollingInteractable_NoRegister, (int32)VTABLE_OFFSET(ASideScrollingMovingPlatform, ISideScrollingInteractable), false },  // 3868912052
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::ClassParams = {
	&ASideScrollingMovingPlatform::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingMovingPlatform()
{
	if (!Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton, Z_Construct_UClass_ASideScrollingMovingPlatform_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingMovingPlatform);
ASideScrollingMovingPlatform::~ASideScrollingMovingPlatform() {}
// ********** End Class ASideScrollingMovingPlatform ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingMovingPlatform, ASideScrollingMovingPlatform::StaticClass, TEXT("ASideScrollingMovingPlatform"), &Z_Registration_Info_UClass_ASideScrollingMovingPlatform, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingMovingPlatform), 4054234382U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_TestProject_2598861235(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
