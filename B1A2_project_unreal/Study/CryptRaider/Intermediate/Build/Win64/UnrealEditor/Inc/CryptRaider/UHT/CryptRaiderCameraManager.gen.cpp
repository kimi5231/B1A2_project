// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CryptRaiderCameraManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCryptRaiderCameraManager() {}

// ********** Begin Cross Module References ********************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderCameraManager();
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderCameraManager_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
UPackage* Z_Construct_UPackage__Script_CryptRaider();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACryptRaiderCameraManager ************************************************
void ACryptRaiderCameraManager::StaticRegisterNativesACryptRaiderCameraManager()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACryptRaiderCameraManager;
UClass* ACryptRaiderCameraManager::GetPrivateStaticClass()
{
	using TClass = ACryptRaiderCameraManager;
	if (!Z_Registration_Info_UClass_ACryptRaiderCameraManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CryptRaiderCameraManager"),
			Z_Registration_Info_UClass_ACryptRaiderCameraManager.InnerSingleton,
			StaticRegisterNativesACryptRaiderCameraManager,
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
	return Z_Registration_Info_UClass_ACryptRaiderCameraManager.InnerSingleton;
}
UClass* Z_Construct_UClass_ACryptRaiderCameraManager_NoRegister()
{
	return ACryptRaiderCameraManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACryptRaiderCameraManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Basic First Person camera manager.\n *  Limits min/max look pitch.\n */" },
#endif
		{ "IncludePath", "CryptRaiderCameraManager.h" },
		{ "ModuleRelativePath", "CryptRaiderCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Basic First Person camera manager.\nLimits min/max look pitch." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACryptRaiderCameraManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ACryptRaiderCameraManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerCameraManager,
	(UObject* (*)())Z_Construct_UPackage__Script_CryptRaider,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACryptRaiderCameraManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACryptRaiderCameraManager_Statics::ClassParams = {
	&ACryptRaiderCameraManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACryptRaiderCameraManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ACryptRaiderCameraManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACryptRaiderCameraManager()
{
	if (!Z_Registration_Info_UClass_ACryptRaiderCameraManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACryptRaiderCameraManager.OuterSingleton, Z_Construct_UClass_ACryptRaiderCameraManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACryptRaiderCameraManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACryptRaiderCameraManager);
ACryptRaiderCameraManager::~ACryptRaiderCameraManager() {}
// ********** End Class ACryptRaiderCameraManager **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h__Script_CryptRaider_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACryptRaiderCameraManager, ACryptRaiderCameraManager::StaticClass, TEXT("ACryptRaiderCameraManager"), &Z_Registration_Info_UClass_ACryptRaiderCameraManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACryptRaiderCameraManager), 2195652248U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h__Script_CryptRaider_586484202(TEXT("/Script/CryptRaider"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h__Script_CryptRaider_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_Study_CryptRaider_Source_CryptRaider_CryptRaiderCameraManager_h__Script_CryptRaider_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
