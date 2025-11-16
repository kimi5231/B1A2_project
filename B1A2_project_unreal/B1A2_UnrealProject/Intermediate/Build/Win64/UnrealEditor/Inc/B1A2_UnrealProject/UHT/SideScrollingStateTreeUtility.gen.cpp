// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingStateTreeUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController_NoRegister();
B1A2_UNREALPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData();
B1A2_UNREALPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask();
ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase();
UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInstanceData ***********************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData;
class UScriptStruct* FStateTreeGetPlayerInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData, (UObject*)Z_Construct_UPackage__Script_B1A2_UnrealProject(), TEXT("StateTreeGetPlayerInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data for the FStateTreeGetPlayerTask task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data for the FStateTreeGetPlayerTask task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPC_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** NPC owning this task */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC owning this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Holds the found player pawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Holds the found player pawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayer_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Holds the found player pawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Holds the found player pawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bValidTarget_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Is the pawn close enough to be considered a valid target? */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Is the pawn close enough to be considered a valid target?" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RangeMax_MetaData[] = {
		{ "Category", "Parameter" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance to be considered a valid target */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance to be considered a valid target" },
#endif
		{ "Units", "cm" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NPC;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayer;
	static void NewProp_bValidTarget_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bValidTarget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RangeMax;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_NPC = { "NPC", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, NPC), Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPC_MetaData), NewProp_NPC_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, Controller), Z_Construct_UClass_AAIController_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_TargetPlayer = { "TargetPlayer", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, TargetPlayer), Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayer_MetaData), NewProp_TargetPlayer_MetaData) };
void Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_bValidTarget_SetBit(void* Obj)
{
	((FStateTreeGetPlayerInstanceData*)Obj)->bValidTarget = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_bValidTarget = { "bValidTarget", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FStateTreeGetPlayerInstanceData), &Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_bValidTarget_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bValidTarget_MetaData), NewProp_bValidTarget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_RangeMax = { "RangeMax", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, RangeMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RangeMax_MetaData), NewProp_RangeMax_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_NPC,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_TargetPlayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_bValidTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_RangeMax,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
	nullptr,
	&NewStructOps,
	"StateTreeGetPlayerInstanceData",
	Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers),
	sizeof(FStateTreeGetPlayerInstanceData),
	alignof(FStateTreeGetPlayerInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerTask *******************************************
static_assert(std::is_polymorphic<FStateTreeGetPlayerTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeGetPlayerTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask;
class UScriptStruct* FStateTreeGetPlayerTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerTask, (UObject*)Z_Construct_UPackage__Script_B1A2_UnrealProject(), TEXT("StateTreeGetPlayerTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Side Scrolling" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to get the player-controlled character\n */" },
#endif
		{ "DisplayName", "Get Player" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to get the player-controlled character" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeGetPlayerTask",
	nullptr,
	0,
	sizeof(FStateTreeGetPlayerTask),
	alignof(FStateTreeGetPlayerTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerTask *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_B1A2_UnrealProject_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FStateTreeGetPlayerInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewStructOps, TEXT("StateTreeGetPlayerInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInstanceData), 675833031U) },
		{ FStateTreeGetPlayerTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::NewStructOps, TEXT("StateTreeGetPlayerTask"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerTask), 2824927568U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_B1A2_UnrealProject_1884039545(TEXT("/Script/B1A2_UnrealProject"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_B1A2_UnrealProject_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_B1A2_UnrealProject_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
