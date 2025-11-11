// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatStateTreeUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeConditionCommonBase();
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase();
TESTPROJECT_API UClass* Z_Construct_UClass_ACombatEnemy_NoRegister();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeAttackInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeChargedAttackTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeComboAttackTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask();
TESTPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FStateTreeCharacterGroundedConditionInstanceData ******************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData;
class UScriptStruct* FStateTreeCharacterGroundedConditionInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeCharacterGroundedConditionInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the FStateTreeCharacterGroundedCondition condition\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the FStateTreeCharacterGroundedCondition condition" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character to check grounded status on */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character to check grounded status on" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMustBeOnAir_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the condition passes if the character is not grounded instead */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the condition passes if the character is not grounded instead" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static void NewProp_bMustBeOnAir_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMustBeOnAir;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeCharacterGroundedConditionInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeCharacterGroundedConditionInstanceData, Character), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
void Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_bMustBeOnAir_SetBit(void* Obj)
{
	((FStateTreeCharacterGroundedConditionInstanceData*)Obj)->bMustBeOnAir = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_bMustBeOnAir = { "bMustBeOnAir", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FStateTreeCharacterGroundedConditionInstanceData), &Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_bMustBeOnAir_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMustBeOnAir_MetaData), NewProp_bMustBeOnAir_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewProp_bMustBeOnAir,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeCharacterGroundedConditionInstanceData",
	Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::PropPointers),
	sizeof(FStateTreeCharacterGroundedConditionInstanceData),
	alignof(FStateTreeCharacterGroundedConditionInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeCharacterGroundedConditionInstanceData ********************

// ********** Begin ScriptStruct FStateTreeCharacterGroundedCondition ******************************
static_assert(std::is_polymorphic<FStateTreeCharacterGroundedCondition>() == std::is_polymorphic<FStateTreeConditionCommonBase>(), "USTRUCT FStateTreeCharacterGroundedCondition cannot be polymorphic unless super FStateTreeConditionCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition;
class UScriptStruct* FStateTreeCharacterGroundedCondition::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeCharacterGroundedCondition"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree condition to check if the character is grounded\n */" },
#endif
		{ "DisplayName", "Character is Grounded" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree condition to check if the character is grounded" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeCharacterGroundedCondition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeConditionCommonBase,
	&NewStructOps,
	"StateTreeCharacterGroundedCondition",
	nullptr,
	0,
	sizeof(FStateTreeCharacterGroundedCondition),
	alignof(FStateTreeCharacterGroundedCondition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeCharacterGroundedCondition ********************************

// ********** Begin ScriptStruct FStateTreeAttackInstanceData **************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData;
class UScriptStruct* FStateTreeAttackInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeAttackInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeAttackInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Combat StateTree tasks\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Combat StateTree tasks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that will perform the attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that will perform the attack" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeAttackInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeAttackInstanceData, Character), Z_Construct_UClass_ACombatEnemy_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::NewProp_Character,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeAttackInstanceData",
	Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::PropPointers),
	sizeof(FStateTreeAttackInstanceData),
	alignof(FStateTreeAttackInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeAttackInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeAttackInstanceData ****************************************

// ********** Begin ScriptStruct FStateTreeComboAttackTask *****************************************
static_assert(std::is_polymorphic<FStateTreeComboAttackTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeComboAttackTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask;
class UScriptStruct* FStateTreeComboAttackTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeComboAttackTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeComboAttackTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to perform a combo attack\n */" },
#endif
		{ "DisplayName", "Combo Attack" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to perform a combo attack" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeComboAttackTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeComboAttackTask",
	nullptr,
	0,
	sizeof(FStateTreeComboAttackTask),
	alignof(FStateTreeComboAttackTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeComboAttackTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeComboAttackTask *******************************************

// ********** Begin ScriptStruct FStateTreeChargedAttackTask ***************************************
static_assert(std::is_polymorphic<FStateTreeChargedAttackTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeChargedAttackTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask;
class UScriptStruct* FStateTreeChargedAttackTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeChargedAttackTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeChargedAttackTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to perform a charged attack\n */" },
#endif
		{ "DisplayName", "Charged Attack" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to perform a charged attack" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeChargedAttackTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeChargedAttackTask",
	nullptr,
	0,
	sizeof(FStateTreeChargedAttackTask),
	alignof(FStateTreeChargedAttackTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeChargedAttackTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeChargedAttackTask *****************************************

// ********** Begin ScriptStruct FStateTreeWaitForLandingTask **************************************
static_assert(std::is_polymorphic<FStateTreeWaitForLandingTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeWaitForLandingTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask;
class UScriptStruct* FStateTreeWaitForLandingTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeWaitForLandingTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to wait for the character to land\n */" },
#endif
		{ "DisplayName", "Wait for Landing" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to wait for the character to land" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeWaitForLandingTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeWaitForLandingTask",
	nullptr,
	0,
	sizeof(FStateTreeWaitForLandingTask),
	alignof(FStateTreeWaitForLandingTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeWaitForLandingTask ****************************************

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData ***********************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData;
class UScriptStruct* FStateTreeFaceActorInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeFaceActorInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Actor StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Actor StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorToFaceTowards_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actor that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor that will be faced towards" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorToFaceTowards;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, Controller), Z_Construct_UClass_AAIController_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewProp_ActorToFaceTowards = { "ActorToFaceTowards", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, ActorToFaceTowards), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorToFaceTowards_MetaData), NewProp_ActorToFaceTowards_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewProp_ActorToFaceTowards,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeFaceActorInstanceData",
	Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::PropPointers),
	sizeof(FStateTreeFaceActorInstanceData),
	alignof(FStateTreeFaceActorInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeFaceActorInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeFaceActorTask *******************************************
static_assert(std::is_polymorphic<FStateTreeFaceActorTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceActorTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask;
class UScriptStruct* FStateTreeFaceActorTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeFaceActorTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards an Actor\n */" },
#endif
		{ "DisplayName", "Face Towards Actor" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards an Actor" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceActorTask",
	nullptr,
	0,
	sizeof(FStateTreeFaceActorTask),
	alignof(FStateTreeFaceActorTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeFaceActorTask *********************************************

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData ********************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData;
class UScriptStruct* FStateTreeFaceLocationInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeFaceLocationInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Location StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Location StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused location */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused location" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceLocation_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Location that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Location that will be faced towards" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FaceLocation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, Controller), Z_Construct_UClass_AAIController_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewProp_FaceLocation = { "FaceLocation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, FaceLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceLocation_MetaData), NewProp_FaceLocation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewProp_FaceLocation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeFaceLocationInstanceData",
	Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::PropPointers),
	sizeof(FStateTreeFaceLocationInstanceData),
	alignof(FStateTreeFaceLocationInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData **********************************

// ********** Begin ScriptStruct FStateTreeFaceLocationTask ****************************************
static_assert(std::is_polymorphic<FStateTreeFaceLocationTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceLocationTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask;
class UScriptStruct* FStateTreeFaceLocationTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeFaceLocationTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards a world location\n */" },
#endif
		{ "DisplayName", "Face Towards Location" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards a world location" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceLocationTask",
	nullptr,
	0,
	sizeof(FStateTreeFaceLocationTask),
	alignof(FStateTreeFaceLocationTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeFaceLocationTask ******************************************

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedInstanceData ***************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData;
class UScriptStruct* FStateTreeSetCharacterSpeedInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeSetCharacterSpeedInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Set Character Speed StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Set Character Speed StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that will be affected */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that will be affected" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max ground speed to set for the character */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max ground speed to set for the character" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetCharacterSpeedInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetCharacterSpeedInstanceData, Character), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetCharacterSpeedInstanceData, Speed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Speed_MetaData), NewProp_Speed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewProp_Speed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeSetCharacterSpeedInstanceData",
	Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::PropPointers),
	sizeof(FStateTreeSetCharacterSpeedInstanceData),
	alignof(FStateTreeSetCharacterSpeedInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeSetCharacterSpeedInstanceData *****************************

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedTask ***********************************
static_assert(std::is_polymorphic<FStateTreeSetCharacterSpeedTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeSetCharacterSpeedTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask;
class UScriptStruct* FStateTreeSetCharacterSpeedTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeSetCharacterSpeedTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to change a Character's ground speed\n */" },
#endif
		{ "DisplayName", "Set Character Speed" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to change a Character's ground speed" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetCharacterSpeedTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeSetCharacterSpeedTask",
	nullptr,
	0,
	sizeof(FStateTreeSetCharacterSpeedTask),
	alignof(FStateTreeSetCharacterSpeedTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeSetCharacterSpeedTask *************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoInstanceData *******************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData;
class UScriptStruct* FStateTreeGetPlayerInfoInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeGetPlayerInfoInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Get Player Info task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Get Player Info task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayerCharacter_MetaData[] = {
		{ "Category", "StateTreeGetPlayerInfoInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayerLocation_MetaData[] = {
		{ "Category", "StateTreeGetPlayerInfoInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Last known location for the target */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Last known location for the target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistanceToTarget_MetaData[] = {
		{ "Category", "StateTreeGetPlayerInfoInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to the target */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to the target" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayerCharacter;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPlayerLocation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DistanceToTarget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInfoInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, Character), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_TargetPlayerCharacter = { "TargetPlayerCharacter", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, TargetPlayerCharacter), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayerCharacter_MetaData), NewProp_TargetPlayerCharacter_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_TargetPlayerLocation = { "TargetPlayerLocation", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, TargetPlayerLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayerLocation_MetaData), NewProp_TargetPlayerLocation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_DistanceToTarget = { "DistanceToTarget", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, DistanceToTarget), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistanceToTarget_MetaData), NewProp_DistanceToTarget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_TargetPlayerCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_TargetPlayerLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewProp_DistanceToTarget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	nullptr,
	&NewStructOps,
	"StateTreeGetPlayerInfoInstanceData",
	Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::PropPointers),
	sizeof(FStateTreeGetPlayerInfoInstanceData),
	alignof(FStateTreeGetPlayerInfoInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerInfoInstanceData *********************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoTask ***************************************
static_assert(std::is_polymorphic<FStateTreeGetPlayerInfoTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeGetPlayerInfoTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask;
class UScriptStruct* FStateTreeGetPlayerInfoTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask, (UObject*)Z_Construct_UPackage__Script_TestProject(), TEXT("StateTreeGetPlayerInfoTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to get information about the player character\n */" },
#endif
		{ "DisplayName", "GetPlayerInfo" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to get information about the player character" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInfoTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeGetPlayerInfoTask",
	nullptr,
	0,
	sizeof(FStateTreeGetPlayerInfoTask),
	alignof(FStateTreeGetPlayerInfoTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerInfoTask *****************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_AI_CombatStateTreeUtility_h__Script_TestProject_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FStateTreeCharacterGroundedConditionInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewStructOps, TEXT("StateTreeCharacterGroundedConditionInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeCharacterGroundedConditionInstanceData), 3676918800U) },
		{ FStateTreeCharacterGroundedCondition::StaticStruct, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::NewStructOps, TEXT("StateTreeCharacterGroundedCondition"), &Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeCharacterGroundedCondition), 3047200764U) },
		{ FStateTreeAttackInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::NewStructOps, TEXT("StateTreeAttackInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeAttackInstanceData), 2124690591U) },
		{ FStateTreeComboAttackTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::NewStructOps, TEXT("StateTreeComboAttackTask"), &Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeComboAttackTask), 1728066928U) },
		{ FStateTreeChargedAttackTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::NewStructOps, TEXT("StateTreeChargedAttackTask"), &Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeChargedAttackTask), 3170854639U) },
		{ FStateTreeWaitForLandingTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::NewStructOps, TEXT("StateTreeWaitForLandingTask"), &Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeWaitForLandingTask), 801479897U) },
		{ FStateTreeFaceActorInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceActorInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorInstanceData), 450845515U) },
		{ FStateTreeFaceActorTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::NewStructOps, TEXT("StateTreeFaceActorTask"), &Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorTask), 126556065U) },
		{ FStateTreeFaceLocationInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceLocationInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationInstanceData), 3886808221U) },
		{ FStateTreeFaceLocationTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::NewStructOps, TEXT("StateTreeFaceLocationTask"), &Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationTask), 2254461517U) },
		{ FStateTreeSetCharacterSpeedInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewStructOps, TEXT("StateTreeSetCharacterSpeedInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetCharacterSpeedInstanceData), 2396177469U) },
		{ FStateTreeSetCharacterSpeedTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::NewStructOps, TEXT("StateTreeSetCharacterSpeedTask"), &Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetCharacterSpeedTask), 1387009811U) },
		{ FStateTreeGetPlayerInfoInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewStructOps, TEXT("StateTreeGetPlayerInfoInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInfoInstanceData), 1533662660U) },
		{ FStateTreeGetPlayerInfoTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::NewStructOps, TEXT("StateTreeGetPlayerInfoTask"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInfoTask), 3031220697U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_AI_CombatStateTreeUtility_h__Script_TestProject_4097948509(TEXT("/Script/TestProject"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_AI_CombatStateTreeUtility_h__Script_TestProject_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Combat_AI_CombatStateTreeUtility_h__Script_TestProject_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
