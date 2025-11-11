// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingPickup.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingPickup() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPickup();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPickup_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingPickup Function BeginOverlap *******************************
struct Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics
{
	struct SideScrollingPickup_eventBeginOverlap_Parms
	{
		AActor* OverlappedActor;
		AActor* OtherActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles pickup collision */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles pickup collision" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::NewProp_OverlappedActor = { "OverlappedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPickup_eventBeginOverlap_Parms, OverlappedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPickup_eventBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::NewProp_OverlappedActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::NewProp_OtherActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASideScrollingPickup, nullptr, "BeginOverlap", Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::SideScrollingPickup_eventBeginOverlap_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::SideScrollingPickup_eventBeginOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASideScrollingPickup::execBeginOverlap)
{
	P_GET_OBJECT(AActor,Z_Param_OverlappedActor);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BeginOverlap(Z_Param_OverlappedActor,Z_Param_OtherActor);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingPickup Function BeginOverlap *********************************

// ********** Begin Class ASideScrollingPickup Function BP_OnPickedUp ******************************
static FName NAME_ASideScrollingPickup_BP_OnPickedUp = FName(TEXT("BP_OnPickedUp"));
void ASideScrollingPickup::BP_OnPickedUp()
{
	UFunction* Func = FindFunctionChecked(NAME_ASideScrollingPickup_BP_OnPickedUp);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to BP to play effects on pickup */" },
#endif
		{ "DisplayName", "On Picked Up" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to BP to play effects on pickup" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASideScrollingPickup, nullptr, "BP_OnPickedUp", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ASideScrollingPickup Function BP_OnPickedUp ********************************

// ********** Begin Class ASideScrollingPickup *****************************************************
void ASideScrollingPickup::StaticRegisterNativesASideScrollingPickup()
{
	UClass* Class = ASideScrollingPickup::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "BeginOverlap", &ASideScrollingPickup::execBeginOverlap },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingPickup;
UClass* ASideScrollingPickup::GetPrivateStaticClass()
{
	using TClass = ASideScrollingPickup;
	if (!Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingPickup"),
			Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton,
			StaticRegisterNativesASideScrollingPickup,
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
	return Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingPickup_NoRegister()
{
	return ASideScrollingPickup::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingPickup_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple side scrolling game pickup\n *  Increments a counter on the GameMode\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple side scrolling game pickup\nIncrements a counter on the GameMode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pickup bounding sphere */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pickup bounding sphere" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sphere;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap, "BeginOverlap" }, // 4005062053
		{ &Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp, "BP_OnPickedUp" }, // 2671513322
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingPickup>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASideScrollingPickup_Statics::NewProp_Sphere = { "Sphere", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPickup, Sphere), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sphere_MetaData), NewProp_Sphere_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingPickup_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPickup_Statics::NewProp_Sphere,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPickup_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingPickup_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPickup_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingPickup_Statics::ClassParams = {
	&ASideScrollingPickup::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASideScrollingPickup_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPickup_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPickup_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingPickup_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingPickup()
{
	if (!Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton, Z_Construct_UClass_ASideScrollingPickup_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingPickup);
ASideScrollingPickup::~ASideScrollingPickup() {}
// ********** End Class ASideScrollingPickup *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingPickup, ASideScrollingPickup::StaticClass, TEXT("ASideScrollingPickup"), &Z_Registration_Info_UClass_ASideScrollingPickup, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingPickup), 1485094788U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_TestProject_918769125(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
