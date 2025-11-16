// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeB1A2_UnrealProject_init() {}
	B1A2_UNREALPROJECT_API UFunction* Z_Construct_UDelegateFunction_B1A2_UnrealProject_OnEnemyDied__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_B1A2_UnrealProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject()
	{
		if (!Z_Registration_Info_UPackage__Script_B1A2_UnrealProject.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_B1A2_UnrealProject_OnEnemyDied__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/B1A2_UnrealProject",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xC406D8C8,
				0x7FB27E2A,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_B1A2_UnrealProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_B1A2_UnrealProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_B1A2_UnrealProject(Z_Construct_UPackage__Script_B1A2_UnrealProject, TEXT("/Script/B1A2_UnrealProject"), Z_Registration_Info_UPackage__Script_B1A2_UnrealProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xC406D8C8, 0x7FB27E2A));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
