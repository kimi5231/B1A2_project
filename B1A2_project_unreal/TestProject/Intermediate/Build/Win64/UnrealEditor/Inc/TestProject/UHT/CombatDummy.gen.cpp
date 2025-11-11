// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatDummy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatDummy() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_ACombatDummy();
TESTPROJECT_API UClass* Z_Construct_UClass_ACombatDummy_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatDamageable_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatDummy Function BP_OnDummyDamaged **********************************
struct CombatDummy_eventBP_OnDummyDamaged_Parms
{
	FVector Location;
	FVector Direction;
};
static FName NAME_ACombatDummy_BP_OnDummyDamaged = FName(TEXT("BP_OnDummyDamaged"));
void ACombatDummy::BP_OnDummyDamaged(FVector const& Location, FVector const& Direction)
{
	CombatDummy_eventBP_OnDummyDamaged_Parms Parms;
	Parms.Location=Location;
	Parms.Direction=Direction;
	UFunction* Func = FindFunctionChecked(NAME_ACombatDummy_BP_OnDummyDamaged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handle to apply damage effects */" },
#endif
		{ "DisplayName", "On Dummy Damaged" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handle to apply damage effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Direction_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDummy_eventBP_OnDummyDamaged_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDummy_eventBP_OnDummyDamaged_Parms, Direction), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Direction_MetaData), NewProp_Direction_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::NewProp_Direction,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatDummy, nullptr, "BP_OnDummyDamaged", Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::PropPointers), sizeof(CombatDummy_eventBP_OnDummyDamaged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatDummy_eventBP_OnDummyDamaged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ACombatDummy Function BP_OnDummyDamaged ************************************

// ********** Begin Class ACombatDummy *************************************************************
void ACombatDummy::StaticRegisterNativesACombatDummy()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatDummy;
UClass* ACombatDummy::GetPrivateStaticClass()
{
	using TClass = ACombatDummy;
	if (!Z_Registration_Info_UClass_ACombatDummy.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatDummy"),
			Z_Registration_Info_UClass_ACombatDummy.InnerSingleton,
			StaticRegisterNativesACombatDummy,
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
	return Z_Registration_Info_UClass_ACombatDummy.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatDummy_NoRegister()
{
	return ACombatDummy::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatDummy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple invincible combat training dummy\n */" },
#endif
		{ "IncludePath", "Variant_Combat/Gameplay/CombatDummy.h" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple invincible combat training dummy" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Root component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Root component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BasePlate_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Static base plate */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Static base plate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dummy_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics enabled dummy mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics enabled dummy mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsConstraint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics constraint holding the dummy and base plate together */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics constraint holding the dummy and base plate together" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BasePlate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Dummy;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PhysicsConstraint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged, "BP_OnDummyDamaged" }, // 3223153469
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatDummy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatDummy_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatDummy_Statics::NewProp_BasePlate = { "BasePlate", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, BasePlate), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BasePlate_MetaData), NewProp_BasePlate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatDummy_Statics::NewProp_Dummy = { "Dummy", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, Dummy), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dummy_MetaData), NewProp_Dummy_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatDummy_Statics::NewProp_PhysicsConstraint = { "PhysicsConstraint", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, PhysicsConstraint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsConstraint_MetaData), NewProp_PhysicsConstraint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatDummy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDummy_Statics::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDummy_Statics::NewProp_BasePlate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDummy_Statics::NewProp_Dummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDummy_Statics::NewProp_PhysicsConstraint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDummy_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatDummy_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDummy_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ACombatDummy_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatDamageable_NoRegister, (int32)VTABLE_OFFSET(ACombatDummy, ICombatDamageable), false },  // 1098042197
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatDummy_Statics::ClassParams = {
	&ACombatDummy::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ACombatDummy_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDummy_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDummy_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatDummy_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatDummy()
{
	if (!Z_Registration_Info_UClass_ACombatDummy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatDummy.OuterSingleton, Z_Construct_UClass_ACombatDummy_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatDummy.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatDummy);
ACombatDummy::~ACombatDummy() {}
// ********** End Class ACombatDummy ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDummy_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatDummy, ACombatDummy::StaticClass, TEXT("ACombatDummy"), &Z_Registration_Info_UClass_ACombatDummy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatDummy), 3691760213U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDummy_h__Script_TestProject_2962935121(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDummy_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDummy_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
