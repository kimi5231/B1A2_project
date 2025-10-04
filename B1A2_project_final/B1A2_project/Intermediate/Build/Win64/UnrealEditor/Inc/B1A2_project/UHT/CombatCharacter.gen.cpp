// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatCharacter() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatCharacter();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatCharacter_NoRegister();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UCombatAttacker_NoRegister();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UCombatDamageable_NoRegister();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UCombatLifeBar_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
UMG_API UClass* Z_Construct_UClass_UWidgetComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatCharacter Function DealtDamage ************************************
struct CombatCharacter_eventDealtDamage_Parms
{
	float Damage;
	FVector ImpactPoint;
};
static FName NAME_ACombatCharacter_DealtDamage = FName(TEXT("DealtDamage"));
void ACombatCharacter::DealtDamage(float Damage, FVector const& ImpactPoint)
{
	CombatCharacter_eventDealtDamage_Parms Parms;
	Parms.Damage=Damage;
	Parms.ImpactPoint=ImpactPoint;
	UFunction* Func = FindFunctionChecked(NAME_ACombatCharacter_DealtDamage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to play damage dealt effects */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to play damage dealt effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactPoint_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ImpactPoint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDealtDamage_Parms, Damage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::NewProp_ImpactPoint = { "ImpactPoint", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDealtDamage_Parms, ImpactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactPoint_MetaData), NewProp_ImpactPoint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::NewProp_ImpactPoint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DealtDamage", Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::PropPointers), sizeof(CombatCharacter_eventDealtDamage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatCharacter_eventDealtDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DealtDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ACombatCharacter Function DealtDamage **************************************

// ********** Begin Class ACombatCharacter Function DoChargedAttackEnd *****************************
struct Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles charged attack released from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles charged attack released from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoChargedAttackEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoChargedAttackEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoChargedAttackEnd();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoChargedAttackEnd *******************************

// ********** Begin Class ACombatCharacter Function DoChargedAttackStart ***************************
struct Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles charged attack pressed from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles charged attack pressed from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoChargedAttackStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoChargedAttackStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoChargedAttackStart();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoChargedAttackStart *****************************

// ********** Begin Class ACombatCharacter Function DoComboAttackEnd *******************************
struct Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles combo attack released from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles combo attack released from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoComboAttackEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoComboAttackEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoComboAttackEnd();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoComboAttackEnd *********************************

// ********** Begin Class ACombatCharacter Function DoComboAttackStart *****************************
struct Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles combo attack pressed from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles combo attack pressed from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoComboAttackStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoComboAttackStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoComboAttackStart();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoComboAttackStart *******************************

// ********** Begin Class ACombatCharacter Function DoLook *****************************************
struct Z_Construct_UFunction_ACombatCharacter_DoLook_Statics
{
	struct CombatCharacter_eventDoLook_Parms
	{
		float Yaw;
		float Pitch;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles look inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles look inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Yaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Pitch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoLook", Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::CombatCharacter_eventDoLook_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::CombatCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DoLook()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoLook_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoLook *******************************************

// ********** Begin Class ACombatCharacter Function DoMove *****************************************
struct Z_Construct_UFunction_ACombatCharacter_DoMove_Statics
{
	struct CombatCharacter_eventDoMove_Parms
	{
		float Right;
		float Forward;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles move inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles move inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Right;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Forward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "DoMove", Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::CombatCharacter_eventDoMove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::CombatCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DoMove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_DoMove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoMove *******************************************

// ********** Begin Class ACombatCharacter Function ReceivedDamage *********************************
struct CombatCharacter_eventReceivedDamage_Parms
{
	float Damage;
	FVector ImpactPoint;
	FVector DamageDirection;
};
static FName NAME_ACombatCharacter_ReceivedDamage = FName(TEXT("ReceivedDamage"));
void ACombatCharacter::ReceivedDamage(float Damage, FVector const& ImpactPoint, FVector const& DamageDirection)
{
	CombatCharacter_eventReceivedDamage_Parms Parms;
	Parms.Damage=Damage;
	Parms.ImpactPoint=ImpactPoint;
	Parms.DamageDirection=DamageDirection;
	UFunction* Func = FindFunctionChecked(NAME_ACombatCharacter_ReceivedDamage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to play damage received effects */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to play damage received effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactPoint_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageDirection_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ImpactPoint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageDirection;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, Damage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_ImpactPoint = { "ImpactPoint", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, ImpactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactPoint_MetaData), NewProp_ImpactPoint_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_DamageDirection = { "DamageDirection", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, DamageDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageDirection_MetaData), NewProp_DamageDirection_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_ImpactPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::NewProp_DamageDirection,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatCharacter, nullptr, "ReceivedDamage", Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::PropPointers), sizeof(CombatCharacter_eventReceivedDamage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(CombatCharacter_eventReceivedDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_ReceivedDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ACombatCharacter Function ReceivedDamage ***********************************

// ********** Begin Class ACombatCharacter *********************************************************
void ACombatCharacter::StaticRegisterNativesACombatCharacter()
{
	UClass* Class = ACombatCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "DoChargedAttackEnd", &ACombatCharacter::execDoChargedAttackEnd },
		{ "DoChargedAttackStart", &ACombatCharacter::execDoChargedAttackStart },
		{ "DoComboAttackEnd", &ACombatCharacter::execDoComboAttackEnd },
		{ "DoComboAttackStart", &ACombatCharacter::execDoComboAttackStart },
		{ "DoLook", &ACombatCharacter::execDoLook },
		{ "DoMove", &ACombatCharacter::execDoMove },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatCharacter;
UClass* ACombatCharacter::GetPrivateStaticClass()
{
	using TClass = ACombatCharacter;
	if (!Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatCharacter"),
			Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton,
			StaticRegisterNativesACombatCharacter,
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
	return Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatCharacter_NoRegister()
{
	return ACombatCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  An enhanced Third Person Character with melee combat capabilities:\n *  - Combo attack string\n *  - Press and hold charged attack\n *  - Damage dealing and reaction\n *  - Death\n *  - Respawning\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Combat/CombatCharacter.h" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An enhanced Third Person Character with melee combat capabilities:\n- Combo attack string\n- Press and hold charged attack\n- Damage dealing and reaction\n- Death\n- Respawning" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBar_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Life bar widget component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Life bar widget component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboAttackAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Combo Attack Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Combo Attack Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargedAttackAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Charged Attack Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Charged Attack Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "Damage" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of HP the character will have on respawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of HP the character will have on respawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current amount of HP the character has */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current amount of HP the character has" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBarColor_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Life bar widget fill color */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Life bar widget fill color" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PelvisBoneName_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the pelvis bone, for damage ragdoll physics */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the pelvis bone, for damage ragdoll physics" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBarWidget_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pointer to the life bar widget */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pointer to the life bar widget" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackInputCacheTimeTolerance_MetaData[] = {
		{ "Category", "Melee Attack" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that may elapse for a non-combo attack input to not be considered stale */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that may elapse for a non-combo attack input to not be considered stale" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceDistance_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "500" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance ahead of the character that melee attack sphere collision traces will extend */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance ahead of the character that melee attack sphere collision traces will extend" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceRadius_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "200" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the sphere trace for melee attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the sphere trace for melee attacks" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeDamage_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of damage a melee attack will deal */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of damage a melee attack will deal" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeKnockbackImpulse_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of knockback impulse a melee attack will apply */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of knockback impulse a melee attack will apply" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeLaunchImpulse_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of upwards impulse a melee attack will apply */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of upwards impulse a melee attack will apply" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboAttackMontage_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage that will play for combo attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for combo attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboSectionNames_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Names of the AnimMontage sections that correspond to each stage of the combo attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Names of the AnimMontage sections that correspond to each stage of the combo attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboInputCacheTimeTolerance_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that may elapse for a combo attack input to not be considered stale */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that may elapse for a combo attack input to not be considered stale" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargedAttackMontage_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage that will play for charged attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for charged attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeLoopSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the charge loop */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the charge loop" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeAttackSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathCameraDistance_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom length while the character is dead */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom length while the character is dead" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultCameraDistance_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom length when the character respawns */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom length when the character respawns" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnTime_MetaData[] = {
		{ "Category", "Respawn" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before respawning the character */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before respawning the character" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ComboAttackAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChargedAttackAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LifeBarColor;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PelvisBoneName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBarWidget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackInputCacheTimeTolerance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeDamage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeKnockbackImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeLaunchImpulse;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ComboAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ComboSectionNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ComboSectionNames;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ComboInputCacheTimeTolerance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChargedAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeLoopSection;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeAttackSection;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathCameraDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultCameraDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatCharacter_DealtDamage, "DealtDamage" }, // 2328499719
		{ &Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd, "DoChargedAttackEnd" }, // 3236475773
		{ &Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart, "DoChargedAttackStart" }, // 3239429126
		{ &Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd, "DoComboAttackEnd" }, // 111620762
		{ &Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart, "DoComboAttackStart" }, // 4275206610
		{ &Z_Construct_UFunction_ACombatCharacter_DoLook, "DoLook" }, // 2872170816
		{ &Z_Construct_UFunction_ACombatCharacter_DoMove, "DoMove" }, // 2611015871
		{ &Z_Construct_UFunction_ACombatCharacter_ReceivedDamage, "ReceivedDamage" }, // 1850734294
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBar = { "LifeBar", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBar), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBar_MetaData), NewProp_LifeBar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MouseLookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboAttackAction = { "ComboAttackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboAttackAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboAttackAction_MetaData), NewProp_ComboAttackAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargedAttackAction = { "ChargedAttackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargedAttackAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargedAttackAction_MetaData), NewProp_ChargedAttackAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBarColor = { "LifeBarColor", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBarColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBarColor_MetaData), NewProp_LifeBarColor_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_PelvisBoneName = { "PelvisBoneName", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, PelvisBoneName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PelvisBoneName_MetaData), NewProp_PelvisBoneName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBarWidget = { "LifeBarWidget", nullptr, (EPropertyFlags)0x0124080000080009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBarWidget), Z_Construct_UClass_UCombatLifeBar_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBarWidget_MetaData), NewProp_LifeBarWidget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_AttackInputCacheTimeTolerance = { "AttackInputCacheTimeTolerance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, AttackInputCacheTimeTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackInputCacheTimeTolerance_MetaData), NewProp_AttackInputCacheTimeTolerance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeTraceDistance = { "MeleeTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceDistance_MetaData), NewProp_MeleeTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeTraceRadius = { "MeleeTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceRadius_MetaData), NewProp_MeleeTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeDamage = { "MeleeDamage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeDamage_MetaData), NewProp_MeleeDamage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeKnockbackImpulse = { "MeleeKnockbackImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeKnockbackImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeKnockbackImpulse_MetaData), NewProp_MeleeKnockbackImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeLaunchImpulse = { "MeleeLaunchImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeLaunchImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeLaunchImpulse_MetaData), NewProp_MeleeLaunchImpulse_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboAttackMontage = { "ComboAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboAttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboAttackMontage_MetaData), NewProp_ComboAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboSectionNames_Inner = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboSectionNames = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboSectionNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboSectionNames_MetaData), NewProp_ComboSectionNames_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboInputCacheTimeTolerance = { "ComboInputCacheTimeTolerance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboInputCacheTimeTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboInputCacheTimeTolerance_MetaData), NewProp_ComboInputCacheTimeTolerance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargedAttackMontage = { "ChargedAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargedAttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargedAttackMontage_MetaData), NewProp_ChargedAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargeLoopSection = { "ChargeLoopSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargeLoopSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeLoopSection_MetaData), NewProp_ChargeLoopSection_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargeAttackSection = { "ChargeAttackSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargeAttackSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeAttackSection_MetaData), NewProp_ChargeAttackSection_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_DeathCameraDistance = { "DeathCameraDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DeathCameraDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathCameraDistance_MetaData), NewProp_DeathCameraDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_DefaultCameraDistance = { "DefaultCameraDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DefaultCameraDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCameraDistance_MetaData), NewProp_DefaultCameraDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatCharacter_Statics::NewProp_RespawnTime = { "RespawnTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, RespawnTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnTime_MetaData), NewProp_RespawnTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MouseLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboAttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargedAttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBarColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_PelvisBoneName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_LifeBarWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_AttackInputCacheTimeTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeKnockbackImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_MeleeLaunchImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboSectionNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboSectionNames,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ComboInputCacheTimeTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargedAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargeLoopSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_ChargeAttackSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_DeathCameraDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_DefaultCameraDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatCharacter_Statics::NewProp_RespawnTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ACombatCharacter_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatAttacker_NoRegister, (int32)VTABLE_OFFSET(ACombatCharacter, ICombatAttacker), false },  // 3488813768
	{ Z_Construct_UClass_UCombatDamageable_NoRegister, (int32)VTABLE_OFFSET(ACombatCharacter, ICombatDamageable), false },  // 2718696512
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatCharacter_Statics::ClassParams = {
	&ACombatCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ACombatCharacter_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatCharacter_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatCharacter()
{
	if (!Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton, Z_Construct_UClass_ACombatCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatCharacter);
ACombatCharacter::~ACombatCharacter() {}
// ********** End Class ACombatCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatCharacter_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatCharacter, ACombatCharacter::StaticClass, TEXT("ACombatCharacter"), &Z_Registration_Info_UClass_ACombatCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatCharacter), 352605170U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatCharacter_h__Script_B1A2_project_3132362406(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatCharacter_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_CombatCharacter_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
