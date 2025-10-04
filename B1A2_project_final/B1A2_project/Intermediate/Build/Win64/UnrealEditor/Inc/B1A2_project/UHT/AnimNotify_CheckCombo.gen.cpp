// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_CheckCombo.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAnimNotify_CheckCombo() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_UAnimNotify_CheckCombo();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UAnimNotify_CheckCombo_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAnimNotify_CheckCombo ***************************************************
void UAnimNotify_CheckCombo::StaticRegisterNativesUAnimNotify_CheckCombo()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimNotify_CheckCombo;
UClass* UAnimNotify_CheckCombo::GetPrivateStaticClass()
{
	using TClass = UAnimNotify_CheckCombo;
	if (!Z_Registration_Info_UClass_UAnimNotify_CheckCombo.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AnimNotify_CheckCombo"),
			Z_Registration_Info_UClass_UAnimNotify_CheckCombo.InnerSingleton,
			StaticRegisterNativesUAnimNotify_CheckCombo,
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
	return Z_Registration_Info_UClass_UAnimNotify_CheckCombo.InnerSingleton;
}
UClass* Z_Construct_UClass_UAnimNotify_CheckCombo_NoRegister()
{
	return UAnimNotify_CheckCombo::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAnimNotify_CheckCombo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  AnimNotify to perform a combo string check.\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Variant_Combat/Animation/AnimNotify_CheckCombo.h" },
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_CheckCombo.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimNotify to perform a combo string check." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_CheckCombo>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotify,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::ClassParams = {
	&UAnimNotify_CheckCombo::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000120A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAnimNotify_CheckCombo()
{
	if (!Z_Registration_Info_UClass_UAnimNotify_CheckCombo.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_CheckCombo.OuterSingleton, Z_Construct_UClass_UAnimNotify_CheckCombo_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimNotify_CheckCombo.OuterSingleton;
}
UAnimNotify_CheckCombo::UAnimNotify_CheckCombo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimNotify_CheckCombo);
UAnimNotify_CheckCombo::~UAnimNotify_CheckCombo() {}
// ********** End Class UAnimNotify_CheckCombo *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_CheckCombo_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_CheckCombo, UAnimNotify_CheckCombo::StaticClass, TEXT("UAnimNotify_CheckCombo"), &Z_Registration_Info_UClass_UAnimNotify_CheckCombo, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_CheckCombo), 1713862167U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_CheckCombo_h__Script_B1A2_project_1516844221(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_CheckCombo_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_CheckCombo_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
