// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatAIController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatAIController();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatAIController_NoRegister();
GAMEPLAYSTATETREEMODULE_API UClass* Z_Construct_UClass_UStateTreeAIComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatAIController ******************************************************
void ACombatAIController::StaticRegisterNativesACombatAIController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatAIController;
UClass* ACombatAIController::GetPrivateStaticClass()
{
	using TClass = ACombatAIController;
	if (!Z_Registration_Info_UClass_ACombatAIController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatAIController"),
			Z_Registration_Info_UClass_ACombatAIController.InnerSingleton,
			StaticRegisterNativesACombatAIController,
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
	return Z_Registration_Info_UClass_ACombatAIController.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatAIController_NoRegister()
{
	return ACombatAIController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatAIController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\x09""A basic AI Controller capable of running StateTree\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_Combat/AI/CombatAIController.h" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic AI Controller capable of running StateTree" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateTreeAI_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree Component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree Component" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StateTreeAI;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatAIController_Statics::NewProp_StateTreeAI = { "StateTreeAI", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatAIController, StateTreeAI), Z_Construct_UClass_UStateTreeAIComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateTreeAI_MetaData), NewProp_StateTreeAI_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatAIController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatAIController_Statics::NewProp_StateTreeAI,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatAIController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatAIController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatAIController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatAIController_Statics::ClassParams = {
	&ACombatAIController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ACombatAIController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatAIController_Statics::PropPointers),
	0,
	0x008003A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatAIController_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatAIController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatAIController()
{
	if (!Z_Registration_Info_UClass_ACombatAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatAIController.OuterSingleton, Z_Construct_UClass_ACombatAIController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatAIController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatAIController);
ACombatAIController::~ACombatAIController() {}
// ********** End Class ACombatAIController ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatAIController, ACombatAIController::StaticClass, TEXT("ACombatAIController"), &Z_Registration_Info_UClass_ACombatAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatAIController), 411683032U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h__Script_B1A2_project_2997350139(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatAIController_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
