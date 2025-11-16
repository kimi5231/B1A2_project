// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "B1A2_UnrealProjectGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeB1A2_UnrealProjectGameMode() {}

// ********** Begin Cross Module References ********************************************************
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_AB1A2_UnrealProjectGameMode();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_AB1A2_UnrealProjectGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AB1A2_UnrealProjectGameMode **********************************************
void AB1A2_UnrealProjectGameMode::StaticRegisterNativesAB1A2_UnrealProjectGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode;
UClass* AB1A2_UnrealProjectGameMode::GetPrivateStaticClass()
{
	using TClass = AB1A2_UnrealProjectGameMode;
	if (!Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("B1A2_UnrealProjectGameMode"),
			Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.InnerSingleton,
			StaticRegisterNativesAB1A2_UnrealProjectGameMode,
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
	return Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AB1A2_UnrealProjectGameMode_NoRegister()
{
	return AB1A2_UnrealProjectGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "B1A2_UnrealProjectGameMode.h" },
		{ "ModuleRelativePath", "B1A2_UnrealProjectGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AB1A2_UnrealProjectGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::ClassParams = {
	&AB1A2_UnrealProjectGameMode::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AB1A2_UnrealProjectGameMode()
{
	if (!Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.OuterSingleton, Z_Construct_UClass_AB1A2_UnrealProjectGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AB1A2_UnrealProjectGameMode);
AB1A2_UnrealProjectGameMode::~AB1A2_UnrealProjectGameMode() {}
// ********** End Class AB1A2_UnrealProjectGameMode ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectGameMode_h__Script_B1A2_UnrealProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AB1A2_UnrealProjectGameMode, AB1A2_UnrealProjectGameMode::StaticClass, TEXT("AB1A2_UnrealProjectGameMode"), &Z_Registration_Info_UClass_AB1A2_UnrealProjectGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AB1A2_UnrealProjectGameMode), 743548620U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectGameMode_h__Script_B1A2_UnrealProject_1498165804(TEXT("/Script/B1A2_UnrealProject"),
	Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectGameMode_h__Script_B1A2_UnrealProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_B1A2_UnrealProjectGameMode_h__Script_B1A2_UnrealProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
