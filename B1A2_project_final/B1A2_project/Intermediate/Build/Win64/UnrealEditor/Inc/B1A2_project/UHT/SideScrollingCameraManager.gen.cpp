// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingCameraManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingCameraManager() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingCameraManager();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ASideScrollingCameraManager_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingCameraManager **********************************************
void ASideScrollingCameraManager::StaticRegisterNativesASideScrollingCameraManager()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingCameraManager;
UClass* ASideScrollingCameraManager::GetPrivateStaticClass()
{
	using TClass = ASideScrollingCameraManager;
	if (!Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingCameraManager"),
			Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton,
			StaticRegisterNativesASideScrollingCameraManager,
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
	return Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingCameraManager_NoRegister()
{
	return ASideScrollingCameraManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingCameraManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple side scrolling camera with smooth scrolling and horizontal bounds\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple side scrolling camera with smooth scrolling and horizontal bounds" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentZoom_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How close we want to stay to the view target */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How close we want to stay to the view target" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraZOffset_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How far above the target do we want the camera to focus */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How far above the target do we want the camera to focus" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraXMinBounds_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "-100000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum camera scrolling bounds in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum camera scrolling bounds in world space" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraXMaxBounds_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "-100000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum camera scrolling bounds in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum camera scrolling bounds in world space" },
#endif
		{ "Units", "cm" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentZoom;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraZOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraXMinBounds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraXMaxBounds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingCameraManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CurrentZoom = { "CurrentZoom", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CurrentZoom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentZoom_MetaData), NewProp_CurrentZoom_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraZOffset = { "CameraZOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraZOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraZOffset_MetaData), NewProp_CameraZOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraXMinBounds = { "CameraXMinBounds", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraXMinBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraXMinBounds_MetaData), NewProp_CameraXMinBounds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraXMaxBounds = { "CameraXMaxBounds", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraXMaxBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraXMaxBounds_MetaData), NewProp_CameraXMaxBounds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingCameraManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CurrentZoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraZOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraXMinBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingCameraManager_Statics::NewProp_CameraXMaxBounds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingCameraManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingCameraManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerCameraManager,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingCameraManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingCameraManager_Statics::ClassParams = {
	&ASideScrollingCameraManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASideScrollingCameraManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingCameraManager_Statics::PropPointers),
	0,
	0x008003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingCameraManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingCameraManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingCameraManager()
{
	if (!Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton, Z_Construct_UClass_ASideScrollingCameraManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton;
}
ASideScrollingCameraManager::ASideScrollingCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingCameraManager);
ASideScrollingCameraManager::~ASideScrollingCameraManager() {}
// ********** End Class ASideScrollingCameraManager ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCameraManager_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingCameraManager, ASideScrollingCameraManager::StaticClass, TEXT("ASideScrollingCameraManager"), &Z_Registration_Info_UClass_ASideScrollingCameraManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingCameraManager), 154790758U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCameraManager_h__Script_B1A2_project_2534484269(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCameraManager_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_SideScrolling_SideScrollingCameraManager_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
