// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingUI() {}

// ********** Begin Cross Module References ********************************************************
TESTPROJECT_API UClass* Z_Construct_UClass_USideScrollingUI();
TESTPROJECT_API UClass* Z_Construct_UClass_USideScrollingUI_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class USideScrollingUI Function UpdatePickups **********************************
struct SideScrollingUI_eventUpdatePickups_Parms
{
	int32 Amount;
};
static FName NAME_USideScrollingUI_UpdatePickups = FName(TEXT("UpdatePickups"));
void USideScrollingUI::UpdatePickups(int32 Amount)
{
	SideScrollingUI_eventUpdatePickups_Parms Parms;
	Parms.Amount=Amount;
	UFunction* Func = FindFunctionChecked(NAME_USideScrollingUI_UpdatePickups);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Update the widget's pickup counter */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Update the widget's pickup counter" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Amount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingUI_eventUpdatePickups_Parms, Amount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::NewProp_Amount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USideScrollingUI, nullptr, "UpdatePickups", Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::PropPointers), sizeof(SideScrollingUI_eventUpdatePickups_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::Function_MetaDataParams), Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(SideScrollingUI_eventUpdatePickups_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USideScrollingUI_UpdatePickups()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class USideScrollingUI Function UpdatePickups ************************************

// ********** Begin Class USideScrollingUI *********************************************************
void USideScrollingUI::StaticRegisterNativesUSideScrollingUI()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_USideScrollingUI;
UClass* USideScrollingUI::GetPrivateStaticClass()
{
	using TClass = USideScrollingUI;
	if (!Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingUI"),
			Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton,
			StaticRegisterNativesUSideScrollingUI,
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
	return Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton;
}
UClass* Z_Construct_UClass_USideScrollingUI_NoRegister()
{
	return USideScrollingUI::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USideScrollingUI_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple Side Scrolling game UI\n *  Displays and manages a pickup counter\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple Side Scrolling game UI\nDisplays and manages a pickup counter" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USideScrollingUI_UpdatePickups, "UpdatePickups" }, // 4202951461
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USideScrollingUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USideScrollingUI_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USideScrollingUI_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USideScrollingUI_Statics::ClassParams = {
	&USideScrollingUI::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USideScrollingUI_Statics::Class_MetaDataParams), Z_Construct_UClass_USideScrollingUI_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USideScrollingUI()
{
	if (!Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton, Z_Construct_UClass_USideScrollingUI_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton;
}
USideScrollingUI::USideScrollingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USideScrollingUI);
USideScrollingUI::~USideScrollingUI() {}
// ********** End Class USideScrollingUI ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_UI_SideScrollingUI_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USideScrollingUI, USideScrollingUI::StaticClass, TEXT("USideScrollingUI"), &Z_Registration_Info_UClass_USideScrollingUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USideScrollingUI), 116220713U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_UI_SideScrollingUI_h__Script_TestProject_1559504242(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_UI_SideScrollingUI_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_UI_SideScrollingUI_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
