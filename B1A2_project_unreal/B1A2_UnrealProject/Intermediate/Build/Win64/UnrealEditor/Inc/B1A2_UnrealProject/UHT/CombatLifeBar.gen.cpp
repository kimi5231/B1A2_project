// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatLifeBar.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatLifeBar() {}

// ********** Begin Cross Module References ********************************************************
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_UCombatLifeBar();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_UCombatLifeBar_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UCombatLifeBar Function SetBarColor **************************************
struct CombatLifeBar_eventSetBarColor_Parms
{
	FLinearColor Color;
};
static FName NAME_UCombatLifeBar_SetBarColor = FName(TEXT("SetBarColor"));
void UCombatLifeBar::SetBarColor(FLinearColor Color)
{
	CombatLifeBar_eventSetBarColor_Parms Parms;
	Parms.Color=Color;
	UFunction* Func = FindFunctionChecked(NAME_UCombatLifeBar_SetBarColor);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Life Bar" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Sets the life bar fill color\n" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the life bar fill color" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLifeBar_eventSetBarColor_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatLifeBar, nullptr, "SetBarColor", Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::PropPointers), sizeof(CombatLifeBar_eventSetBarColor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08820800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatLifeBar_eventSetBarColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatLifeBar_SetBarColor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UCombatLifeBar Function SetBarColor ****************************************

// ********** Begin Class UCombatLifeBar Function SetLifePercentage ********************************
struct CombatLifeBar_eventSetLifePercentage_Parms
{
	float Percent;
};
static FName NAME_UCombatLifeBar_SetLifePercentage = FName(TEXT("SetLifePercentage"));
void UCombatLifeBar::SetLifePercentage(float Percent)
{
	CombatLifeBar_eventSetLifePercentage_Parms Parms;
	Parms.Percent=Percent;
	UFunction* Func = FindFunctionChecked(NAME_UCombatLifeBar_SetLifePercentage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Life Bar" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sets the life bar to the provided 0-1 percentage value*/" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the life bar to the provided 0-1 percentage value" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Percent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::NewProp_Percent = { "Percent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLifeBar_eventSetLifePercentage_Parms, Percent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::NewProp_Percent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UCombatLifeBar, nullptr, "SetLifePercentage", Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::PropPointers), sizeof(CombatLifeBar_eventSetLifePercentage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatLifeBar_eventSetLifePercentage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UCombatLifeBar Function SetLifePercentage **********************************

// ********** Begin Class UCombatLifeBar ***********************************************************
void UCombatLifeBar::StaticRegisterNativesUCombatLifeBar()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatLifeBar;
UClass* UCombatLifeBar::GetPrivateStaticClass()
{
	using TClass = UCombatLifeBar;
	if (!Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatLifeBar"),
			Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton,
			StaticRegisterNativesUCombatLifeBar,
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
	return Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton;
}
UClass* Z_Construct_UClass_UCombatLifeBar_NoRegister()
{
	return UCombatLifeBar::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UCombatLifeBar_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic life bar user widget.\n */" },
#endif
		{ "IncludePath", "Variant_Combat/UI/CombatLifeBar.h" },
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic life bar user widget." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatLifeBar_SetBarColor, "SetBarColor" }, // 2597840391
		{ &Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage, "SetLifePercentage" }, // 2620603760
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCombatLifeBar>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCombatLifeBar_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatLifeBar_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCombatLifeBar_Statics::ClassParams = {
	&UCombatLifeBar::StaticClass,
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
	0x00A010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatLifeBar_Statics::Class_MetaDataParams), Z_Construct_UClass_UCombatLifeBar_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCombatLifeBar()
{
	if (!Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton, Z_Construct_UClass_UCombatLifeBar_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton;
}
UCombatLifeBar::UCombatLifeBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCombatLifeBar);
UCombatLifeBar::~UCombatLifeBar() {}
// ********** End Class UCombatLifeBar *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h__Script_B1A2_UnrealProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatLifeBar, UCombatLifeBar::StaticClass, TEXT("UCombatLifeBar"), &Z_Registration_Info_UClass_UCombatLifeBar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatLifeBar), 1337157406U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h__Script_B1A2_UnrealProject_142912860(TEXT("/Script/B1A2_UnrealProject"),
	Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h__Script_B1A2_UnrealProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_Combat_UI_CombatLifeBar_h__Script_B1A2_UnrealProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
