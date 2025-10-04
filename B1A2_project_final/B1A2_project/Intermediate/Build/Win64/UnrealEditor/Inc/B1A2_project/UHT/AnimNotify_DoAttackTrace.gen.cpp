// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_DoAttackTrace.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAnimNotify_DoAttackTrace() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAnimNotify_DoAttackTrace ************************************************
void UAnimNotify_DoAttackTrace::StaticRegisterNativesUAnimNotify_DoAttackTrace()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace;
UClass* UAnimNotify_DoAttackTrace::GetPrivateStaticClass()
{
	using TClass = UAnimNotify_DoAttackTrace;
	if (!Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AnimNotify_DoAttackTrace"),
			Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton,
			StaticRegisterNativesUAnimNotify_DoAttackTrace,
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
	return Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton;
}
UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace_NoRegister()
{
	return UAnimNotify_DoAttackTrace::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  AnimNotify to tell the actor to perform an attack trace check to look for targets to damage.\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimNotify to tell the actor to perform an attack trace check to look for targets to damage." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackBoneName_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Source bone for the attack trace */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Source bone for the attack trace" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_AttackBoneName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_DoAttackTrace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::NewProp_AttackBoneName = { "AttackBoneName", nullptr, (EPropertyFlags)0x0020080000000011, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimNotify_DoAttackTrace, AttackBoneName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackBoneName_MetaData), NewProp_AttackBoneName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::NewProp_AttackBoneName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotify,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::ClassParams = {
	&UAnimNotify_DoAttackTrace::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::PropPointers),
	0,
	0x000120A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace()
{
	if (!Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton, Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton;
}
UAnimNotify_DoAttackTrace::UAnimNotify_DoAttackTrace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimNotify_DoAttackTrace);
UAnimNotify_DoAttackTrace::~UAnimNotify_DoAttackTrace() {}
// ********** End Class UAnimNotify_DoAttackTrace **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_DoAttackTrace, UAnimNotify_DoAttackTrace::StaticClass, TEXT("UAnimNotify_DoAttackTrace"), &Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_DoAttackTrace), 3408022384U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_B1A2_project_1501746462(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
