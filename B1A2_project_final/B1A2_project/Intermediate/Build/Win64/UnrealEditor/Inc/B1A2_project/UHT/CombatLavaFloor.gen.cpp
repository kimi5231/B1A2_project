// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatLavaFloor.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatLavaFloor() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatLavaFloor();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatLavaFloor_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatLavaFloor Function OnFloorHit *************************************
struct Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics
{
	struct CombatLavaFloor_eventOnFloorHit_Parms
	{
		UPrimitiveComponent* HitComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		FVector NormalImpulse;
		FHitResult Hit;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blocking hit handler */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatLavaFloor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blocking hit handler" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HitComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NormalImpulse;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Hit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_HitComponent = { "HitComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLavaFloor_eventOnFloorHit_Parms, HitComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitComponent_MetaData), NewProp_HitComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLavaFloor_eventOnFloorHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLavaFloor_eventOnFloorHit_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_NormalImpulse = { "NormalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLavaFloor_eventOnFloorHit_Parms, NormalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLavaFloor_eventOnFloorHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hit_MetaData), NewProp_Hit_MetaData) }; // 267591329
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_HitComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_NormalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::NewProp_Hit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatLavaFloor, nullptr, "OnFloorHit", Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::CombatLavaFloor_eventOnFloorHit_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::CombatLavaFloor_eventOnFloorHit_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatLavaFloor::execOnFloorHit)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_STRUCT(FVector,Z_Param_NormalImpulse);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnFloorHit(Z_Param_HitComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit);
	P_NATIVE_END;
}
// ********** End Class ACombatLavaFloor Function OnFloorHit ***************************************

// ********** Begin Class ACombatLavaFloor *********************************************************
void ACombatLavaFloor::StaticRegisterNativesACombatLavaFloor()
{
	UClass* Class = ACombatLavaFloor::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnFloorHit", &ACombatLavaFloor::execOnFloorHit },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatLavaFloor;
UClass* ACombatLavaFloor::GetPrivateStaticClass()
{
	using TClass = ACombatLavaFloor;
	if (!Z_Registration_Info_UClass_ACombatLavaFloor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatLavaFloor"),
			Z_Registration_Info_UClass_ACombatLavaFloor.InnerSingleton,
			StaticRegisterNativesACombatLavaFloor,
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
	return Z_Registration_Info_UClass_ACombatLavaFloor.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatLavaFloor_NoRegister()
{
	return ACombatLavaFloor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatLavaFloor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic actor that applies damage on contact through the ICombatDamageable interface. \n */" },
#endif
		{ "IncludePath", "Variant_Combat/Gameplay/CombatLavaFloor.h" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatLavaFloor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic actor that applies damage on contact through the ICombatDamageable interface." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Floor mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatLavaFloor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Floor mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of damage to deal on contact */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatLavaFloor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of damage to deal on contact" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatLavaFloor_OnFloorHit, "OnFloorHit" }, // 1030873333
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatLavaFloor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatLavaFloor_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatLavaFloor, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatLavaFloor_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatLavaFloor, Damage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Damage_MetaData), NewProp_Damage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatLavaFloor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatLavaFloor_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatLavaFloor_Statics::NewProp_Damage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatLavaFloor_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatLavaFloor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatLavaFloor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatLavaFloor_Statics::ClassParams = {
	&ACombatLavaFloor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ACombatLavaFloor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatLavaFloor_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatLavaFloor_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatLavaFloor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatLavaFloor()
{
	if (!Z_Registration_Info_UClass_ACombatLavaFloor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatLavaFloor.OuterSingleton, Z_Construct_UClass_ACombatLavaFloor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatLavaFloor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatLavaFloor);
ACombatLavaFloor::~ACombatLavaFloor() {}
// ********** End Class ACombatLavaFloor ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Gameplay_CombatLavaFloor_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatLavaFloor, ACombatLavaFloor::StaticClass, TEXT("ACombatLavaFloor"), &Z_Registration_Info_UClass_ACombatLavaFloor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatLavaFloor), 988139625U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Gameplay_CombatLavaFloor_h__Script_B1A2_project_2771011848(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Gameplay_CombatLavaFloor_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_Gameplay_CombatLavaFloor_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
