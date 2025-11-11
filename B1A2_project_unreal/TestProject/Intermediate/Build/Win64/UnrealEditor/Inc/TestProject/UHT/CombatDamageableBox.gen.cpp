// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatDamageableBox.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatDamageableBox() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_ACombatDamageableBox();
TESTPROJECT_API UClass* Z_Construct_UClass_ACombatDamageableBox_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_UCombatDamageable_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatDamageableBox Function OnBoxDamaged *******************************
struct CombatDamageableBox_eventOnBoxDamaged_Parms
{
	FVector DamageLocation;
	FVector DamageImpulse;
};
static FName NAME_ACombatDamageableBox_OnBoxDamaged = FName(TEXT("OnBoxDamaged"));
void ACombatDamageableBox::OnBoxDamaged(FVector const& DamageLocation, FVector const& DamageImpulse)
{
	CombatDamageableBox_eventOnBoxDamaged_Parms Parms;
	Parms.DamageLocation=DamageLocation;
	Parms.DamageImpulse=DamageImpulse;
	UFunction* Func = FindFunctionChecked(NAME_ACombatDamageableBox_OnBoxDamaged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint damage handler for effect playback */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint damage handler for effect playback" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageImpulse_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageImpulse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::NewProp_DamageLocation = { "DamageLocation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDamageableBox_eventOnBoxDamaged_Parms, DamageLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageLocation_MetaData), NewProp_DamageLocation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::NewProp_DamageImpulse = { "DamageImpulse", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDamageableBox_eventOnBoxDamaged_Parms, DamageImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageImpulse_MetaData), NewProp_DamageImpulse_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::NewProp_DamageLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::NewProp_DamageImpulse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatDamageableBox, nullptr, "OnBoxDamaged", Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::PropPointers), sizeof(CombatDamageableBox_eventOnBoxDamaged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatDamageableBox_eventOnBoxDamaged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ACombatDamageableBox Function OnBoxDamaged *********************************

// ********** Begin Class ACombatDamageableBox Function OnBoxDestroyed *****************************
static FName NAME_ACombatDamageableBox_OnBoxDestroyed = FName(TEXT("OnBoxDestroyed"));
void ACombatDamageableBox::OnBoxDestroyed()
{
	UFunction* Func = FindFunctionChecked(NAME_ACombatDamageableBox_OnBoxDestroyed);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint destruction handler for effect playback */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint destruction handler for effect playback" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatDamageableBox, nullptr, "OnBoxDestroyed", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ACombatDamageableBox Function OnBoxDestroyed *******************************

// ********** Begin Class ACombatDamageableBox *****************************************************
void ACombatDamageableBox::StaticRegisterNativesACombatDamageableBox()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatDamageableBox;
UClass* ACombatDamageableBox::GetPrivateStaticClass()
{
	using TClass = ACombatDamageableBox;
	if (!Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatDamageableBox"),
			Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton,
			StaticRegisterNativesACombatDamageableBox,
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
	return Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatDamageableBox_NoRegister()
{
	return ACombatDamageableBox::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatDamageableBox_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple physics box that reacts to damage through the ICombatDamageable interface\n */" },
#endif
		{ "IncludePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple physics box that reacts to damage through the ICombatDamageable interface" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Damageable box mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Damageable box mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of HP this box starts with. */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of HP this box starts with." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathDelayTime_MetaData[] = {
		{ "Category", "Damage" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before we remove this box from the level. */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before we remove this box from the level." },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathDelayTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged, "OnBoxDamaged" }, // 3061810775
		{ &Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed, "OnBoxDestroyed" }, // 2020037146
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatDamageableBox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_DeathDelayTime = { "DeathDelayTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, DeathDelayTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathDelayTime_MetaData), NewProp_DeathDelayTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatDamageableBox_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatDamageableBox_Statics::NewProp_DeathDelayTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDamageableBox_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatDamageableBox_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDamageableBox_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ACombatDamageableBox_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatDamageable_NoRegister, (int32)VTABLE_OFFSET(ACombatDamageableBox, ICombatDamageable), false },  // 1098042197
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatDamageableBox_Statics::ClassParams = {
	&ACombatDamageableBox::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ACombatDamageableBox_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDamageableBox_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatDamageableBox_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatDamageableBox_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatDamageableBox()
{
	if (!Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton, Z_Construct_UClass_ACombatDamageableBox_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatDamageableBox);
ACombatDamageableBox::~ACombatDamageableBox() {}
// ********** End Class ACombatDamageableBox *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatDamageableBox, ACombatDamageableBox::StaticClass, TEXT("ACombatDamageableBox"), &Z_Registration_Info_UClass_ACombatDamageableBox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatDamageableBox), 2378883013U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_TestProject_150067202(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
