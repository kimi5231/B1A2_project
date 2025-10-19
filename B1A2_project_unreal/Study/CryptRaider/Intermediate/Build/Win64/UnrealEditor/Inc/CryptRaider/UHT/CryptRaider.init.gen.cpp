// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCryptRaider_init() {}
	CRYPTRAIDER_API UFunction* Z_Construct_UDelegateFunction_CryptRaider_BulletCountUpdatedDelegate__DelegateSignature();
	CRYPTRAIDER_API UFunction* Z_Construct_UDelegateFunction_CryptRaider_DamagedDelegate__DelegateSignature();
	CRYPTRAIDER_API UFunction* Z_Construct_UDelegateFunction_CryptRaider_PawnDeathDelegate__DelegateSignature();
	CRYPTRAIDER_API UFunction* Z_Construct_UDelegateFunction_CryptRaider_SprintStateChangedDelegate__DelegateSignature();
	CRYPTRAIDER_API UFunction* Z_Construct_UDelegateFunction_CryptRaider_UpdateSprintMeterDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_CryptRaider;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_CryptRaider()
	{
		if (!Z_Registration_Info_UPackage__Script_CryptRaider.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_CryptRaider_BulletCountUpdatedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CryptRaider_DamagedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CryptRaider_PawnDeathDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CryptRaider_SprintStateChangedDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CryptRaider_UpdateSprintMeterDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/CryptRaider",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x9044E4F4,
				0xDAE9CA3F,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_CryptRaider.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_CryptRaider.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_CryptRaider(Z_Construct_UPackage__Script_CryptRaider, TEXT("/Script/CryptRaider"), Z_Registration_Info_UPackage__Script_CryptRaider, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x9044E4F4, 0xDAE9CA3F));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
