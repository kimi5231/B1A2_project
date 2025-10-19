// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CryptRaiderGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCryptRaiderGameMode() {}

// ********** Begin Cross Module References ********************************************************
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderGameMode();
CRYPTRAIDER_API UClass* Z_Construct_UClass_ACryptRaiderGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_CryptRaider();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACryptRaiderGameMode *****************************************************
void ACryptRaiderGameMode::StaticRegisterNativesACryptRaiderGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACryptRaiderGameMode;
UClass* ACryptRaiderGameMode::GetPrivateStaticClass()
{
	using TClass = ACryptRaiderGameMode;
	if (!Z_Registration_Info_UClass_ACryptRaiderGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CryptRaiderGameMode"),
			Z_Registration_Info_UClass_ACryptRaiderGameMode.InnerSingleton,
			StaticRegisterNativesACryptRaiderGameMode,
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
	return Z_Registration_Info_UClass_ACryptRaiderGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ACryptRaiderGameMode_NoRegister()
{
	return ACryptRaiderGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACryptRaiderGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a first person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CryptRaiderGameMode.h" },
		{ "ModuleRelativePath", "CryptRaiderGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a first person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACryptRaiderGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ACryptRaiderGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_CryptRaider,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACryptRaiderGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACryptRaiderGameMode_Statics::ClassParams = {
	&ACryptRaiderGameMode::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACryptRaiderGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ACryptRaiderGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACryptRaiderGameMode()
{
	if (!Z_Registration_Info_UClass_ACryptRaiderGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACryptRaiderGameMode.OuterSingleton, Z_Construct_UClass_ACryptRaiderGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACryptRaiderGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACryptRaiderGameMode);
ACryptRaiderGameMode::~ACryptRaiderGameMode() {}
// ********** End Class ACryptRaiderGameMode *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h__Script_CryptRaider_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACryptRaiderGameMode, ACryptRaiderGameMode::StaticClass, TEXT("ACryptRaiderGameMode"), &Z_Registration_Info_UClass_ACryptRaiderGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACryptRaiderGameMode), 470840880U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h__Script_CryptRaider_4133464790(TEXT("/Script/CryptRaider"),
	Z_CompiledInDeferFile_FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h__Script_CryptRaider_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CryptRaider_Source_CryptRaider_CryptRaiderGameMode_h__Script_CryptRaider_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
