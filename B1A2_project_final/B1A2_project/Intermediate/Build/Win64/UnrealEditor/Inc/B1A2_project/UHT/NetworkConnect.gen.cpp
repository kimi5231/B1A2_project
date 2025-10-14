// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NetworkConnect.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeNetworkConnect() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_UNetworkConnect();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UNetworkConnect_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNetworkConnect **********************************************************
void UNetworkConnect::StaticRegisterNativesUNetworkConnect()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNetworkConnect;
UClass* UNetworkConnect::GetPrivateStaticClass()
{
	using TClass = UNetworkConnect;
	if (!Z_Registration_Info_UClass_UNetworkConnect.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("NetworkConnect"),
			Z_Registration_Info_UClass_UNetworkConnect.InnerSingleton,
			StaticRegisterNativesUNetworkConnect,
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
	return Z_Registration_Info_UClass_UNetworkConnect.InnerSingleton;
}
UClass* Z_Construct_UClass_UNetworkConnect_NoRegister()
{
	return UNetworkConnect::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNetworkConnect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "NetworkConnect.h" },
		{ "ModuleRelativePath", "NetworkConnect.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNetworkConnect>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UNetworkConnect_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkConnect_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNetworkConnect_Statics::ClassParams = {
	&UNetworkConnect::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkConnect_Statics::Class_MetaDataParams), Z_Construct_UClass_UNetworkConnect_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNetworkConnect()
{
	if (!Z_Registration_Info_UClass_UNetworkConnect.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNetworkConnect.OuterSingleton, Z_Construct_UClass_UNetworkConnect_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNetworkConnect.OuterSingleton;
}
UNetworkConnect::UNetworkConnect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNetworkConnect);
UNetworkConnect::~UNetworkConnect() {}
// ********** End Class UNetworkConnect ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_NetworkConnect_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNetworkConnect, UNetworkConnect::StaticClass, TEXT("UNetworkConnect"), &Z_Registration_Info_UClass_UNetworkConnect, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNetworkConnect), 4285530909U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_NetworkConnect_h__Script_B1A2_project_2408356360(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_NetworkConnect_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_NetworkConnect_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
