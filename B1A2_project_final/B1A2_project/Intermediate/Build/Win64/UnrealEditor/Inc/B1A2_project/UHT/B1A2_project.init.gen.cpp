// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeB1A2_project_init() {}
	B1A2_PROJECT_API UFunction* Z_Construct_UDelegateFunction_B1A2_project_OnEnemyDied__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_B1A2_project;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_B1A2_project()
	{
		if (!Z_Registration_Info_UPackage__Script_B1A2_project.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_B1A2_project_OnEnemyDied__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/B1A2_project",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x280A1C0F,
				0x7EF91865,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_B1A2_project.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_B1A2_project.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_B1A2_project(Z_Construct_UPackage__Script_B1A2_project, TEXT("/Script/B1A2_project"), Z_Registration_Info_UPackage__Script_B1A2_project, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x280A1C0F, 0x7EF91865));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
