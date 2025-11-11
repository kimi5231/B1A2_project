// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PlatformingGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePlatformingGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
TESTPROJECT_API UClass* Z_Construct_UClass_APlatformingGameMode();
TESTPROJECT_API UClass* Z_Construct_UClass_APlatformingGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APlatformingGameMode *****************************************************
void APlatformingGameMode::StaticRegisterNativesAPlatformingGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APlatformingGameMode;
UClass* APlatformingGameMode::GetPrivateStaticClass()
{
	using TClass = APlatformingGameMode;
	if (!Z_Registration_Info_UClass_APlatformingGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PlatformingGameMode"),
			Z_Registration_Info_UClass_APlatformingGameMode.InnerSingleton,
			StaticRegisterNativesAPlatformingGameMode,
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
	return Z_Registration_Info_UClass_APlatformingGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_APlatformingGameMode_NoRegister()
{
	return APlatformingGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APlatformingGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person platforming game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Variant_Platforming/PlatformingGameMode.h" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person platforming game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlatformingGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APlatformingGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlatformingGameMode_Statics::ClassParams = {
	&APlatformingGameMode::StaticClass,
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
	0x008003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_APlatformingGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlatformingGameMode()
{
	if (!Z_Registration_Info_UClass_APlatformingGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlatformingGameMode.OuterSingleton, Z_Construct_UClass_APlatformingGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlatformingGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlatformingGameMode);
APlatformingGameMode::~APlatformingGameMode() {}
// ********** End Class APlatformingGameMode *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingGameMode_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlatformingGameMode, APlatformingGameMode::StaticClass, TEXT("APlatformingGameMode"), &Z_Registration_Info_UClass_APlatformingGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlatformingGameMode), 407212301U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingGameMode_h__Script_TestProject_56294630(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingGameMode_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingGameMode_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
