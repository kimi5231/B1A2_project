// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestProjectGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTestProjectGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectGameMode();
TESTPROJECT_API UClass* Z_Construct_UClass_ATestProjectGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATestProjectGameMode *****************************************************
void ATestProjectGameMode::StaticRegisterNativesATestProjectGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATestProjectGameMode;
UClass* ATestProjectGameMode::GetPrivateStaticClass()
{
	using TClass = ATestProjectGameMode;
	if (!Z_Registration_Info_UClass_ATestProjectGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TestProjectGameMode"),
			Z_Registration_Info_UClass_ATestProjectGameMode.InnerSingleton,
			StaticRegisterNativesATestProjectGameMode,
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
	return Z_Registration_Info_UClass_ATestProjectGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ATestProjectGameMode_NoRegister()
{
	return ATestProjectGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATestProjectGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TestProjectGameMode.h" },
		{ "ModuleRelativePath", "TestProjectGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATestProjectGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ATestProjectGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATestProjectGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATestProjectGameMode_Statics::ClassParams = {
	&ATestProjectGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATestProjectGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ATestProjectGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATestProjectGameMode()
{
	if (!Z_Registration_Info_UClass_ATestProjectGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATestProjectGameMode.OuterSingleton, Z_Construct_UClass_ATestProjectGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATestProjectGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATestProjectGameMode);
ATestProjectGameMode::~ATestProjectGameMode() {}
// ********** End Class ATestProjectGameMode *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATestProjectGameMode, ATestProjectGameMode::StaticClass, TEXT("ATestProjectGameMode"), &Z_Registration_Info_UClass_ATestProjectGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATestProjectGameMode), 2507269315U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h__Script_TestProject_3431626961(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_TestProjectGameMode_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
