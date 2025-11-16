// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingNPC.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingNPC() {}

// ********** Begin Cross Module References ********************************************************
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingNPC();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingNPC_NoRegister();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_USideScrollingInteractable_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingNPC ********************************************************
void ASideScrollingNPC::StaticRegisterNativesASideScrollingNPC()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingNPC;
UClass* ASideScrollingNPC::GetPrivateStaticClass()
{
	using TClass = ASideScrollingNPC;
	if (!Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingNPC"),
			Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton,
			StaticRegisterNativesASideScrollingNPC,
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
	return Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingNPC_NoRegister()
{
	return ASideScrollingNPC::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingNPC_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple platforming NPC\n *  Its behaviors will be dictated by a possessing AI Controller\n *  It can be temporarily deactivated through Actor interactions\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple platforming NPC\nIts behaviors will be dictated by a possessing AI Controller\nIt can be temporarily deactivated through Actor interactions" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LaunchImpulse_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Horizontal impulse to apply to the NPC when it's interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Horizontal impulse to apply to the NPC when it's interacted with" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LaunchVerticalImpulse_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Vertical impulse to apply to the NPC when it's interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical impulse to apply to the NPC when it's interacted with" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeactivationTime_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time that the NPC remains deactivated after being interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time that the NPC remains deactivated after being interacted with" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDeactivated_MetaData[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, this NPC is deactivated and will not be interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, this NPC is deactivated and will not be interacted with" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LaunchImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LaunchVerticalImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeactivationTime;
	static void NewProp_bDeactivated_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDeactivated;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingNPC>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_LaunchImpulse = { "LaunchImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, LaunchImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LaunchImpulse_MetaData), NewProp_LaunchImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_LaunchVerticalImpulse = { "LaunchVerticalImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, LaunchVerticalImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LaunchVerticalImpulse_MetaData), NewProp_LaunchVerticalImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_DeactivationTime = { "DeactivationTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, DeactivationTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeactivationTime_MetaData), NewProp_DeactivationTime_MetaData) };
void Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_bDeactivated_SetBit(void* Obj)
{
	((ASideScrollingNPC*)Obj)->bDeactivated = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_bDeactivated = { "bDeactivated", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASideScrollingNPC), &Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_bDeactivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDeactivated_MetaData), NewProp_bDeactivated_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingNPC_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_LaunchImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_LaunchVerticalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_DeactivationTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingNPC_Statics::NewProp_bDeactivated,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingNPC_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingNPC_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingNPC_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ASideScrollingNPC_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_USideScrollingInteractable_NoRegister, (int32)VTABLE_OFFSET(ASideScrollingNPC, ISideScrollingInteractable), false },  // 2964896161
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingNPC_Statics::ClassParams = {
	&ASideScrollingNPC::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASideScrollingNPC_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingNPC_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingNPC_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingNPC_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingNPC()
{
	if (!Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton, Z_Construct_UClass_ASideScrollingNPC_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingNPC);
ASideScrollingNPC::~ASideScrollingNPC() {}
// ********** End Class ASideScrollingNPC **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_B1A2_UnrealProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingNPC, ASideScrollingNPC::StaticClass, TEXT("ASideScrollingNPC"), &Z_Registration_Info_UClass_ASideScrollingNPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingNPC), 74963499U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_B1A2_UnrealProject_528781222(TEXT("/Script/B1A2_UnrealProject"),
	Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_B1A2_UnrealProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_B1A2_UnrealProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
