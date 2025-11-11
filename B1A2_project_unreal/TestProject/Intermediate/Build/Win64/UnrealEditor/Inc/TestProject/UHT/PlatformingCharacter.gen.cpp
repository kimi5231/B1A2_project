// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PlatformingCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePlatformingCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_APlatformingCharacter();
TESTPROJECT_API UClass* Z_Construct_UClass_APlatformingCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APlatformingCharacter Function DoDash ************************************
struct Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles dash inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles dash inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "DoDash", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoDash()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execDoDash)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoDash();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoDash **************************************

// ********** Begin Class APlatformingCharacter Function DoJumpEnd *********************************
struct Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "DoJumpEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execDoJumpEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpEnd();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoJumpEnd ***********************************

// ********** Begin Class APlatformingCharacter Function DoJumpStart *******************************
struct Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "DoJumpStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoJumpStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execDoJumpStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpStart();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoJumpStart *********************************

// ********** Begin Class APlatformingCharacter Function DoLook ************************************
struct Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics
{
	struct PlatformingCharacter_eventDoLook_Parms
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
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
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
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "DoLook", Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PlatformingCharacter_eventDoLook_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::PlatformingCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoLook()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoLook **************************************

// ********** Begin Class APlatformingCharacter Function DoMove ************************************
struct Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics
{
	struct PlatformingCharacter_eventDoMove_Parms
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
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
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
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "DoMove", Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PlatformingCharacter_eventDoMove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::PlatformingCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoMove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoMove **************************************

// ********** Begin Class APlatformingCharacter Function HasDoubleJumped ***************************
struct Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics
{
	struct PlatformingCharacter_eventHasDoubleJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just double jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just double jumped" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((PlatformingCharacter_eventHasDoubleJumped_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventHasDoubleJumped_Parms), &Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "HasDoubleJumped", Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PlatformingCharacter_eventHasDoubleJumped_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::PlatformingCharacter_eventHasDoubleJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execHasDoubleJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasDoubleJumped();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function HasDoubleJumped *****************************

// ********** Begin Class APlatformingCharacter Function HasWallJumped *****************************
struct Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics
{
	struct PlatformingCharacter_eventHasWallJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just wall jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just wall jumped" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((PlatformingCharacter_eventHasWallJumped_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventHasWallJumped_Parms), &Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "HasWallJumped", Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PlatformingCharacter_eventHasWallJumped_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::PlatformingCharacter_eventHasWallJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_HasWallJumped()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlatformingCharacter::execHasWallJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasWallJumped();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function HasWallJumped *******************************

// ********** Begin Class APlatformingCharacter Function SetJumpTrailState *************************
struct PlatformingCharacter_eventSetJumpTrailState_Parms
{
	bool bEnabled;
};
static FName NAME_APlatformingCharacter_SetJumpTrailState = FName(TEXT("SetJumpTrailState"));
void APlatformingCharacter::SetJumpTrailState(bool bEnabled)
{
	PlatformingCharacter_eventSetJumpTrailState_Parms Parms;
	Parms.bEnabled=bEnabled ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_APlatformingCharacter_SetJumpTrailState);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to Blueprint to enable or disable jump trails */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to Blueprint to enable or disable jump trails" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::NewProp_bEnabled_SetBit(void* Obj)
{
	((PlatformingCharacter_eventSetJumpTrailState_Parms*)Obj)->bEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventSetJumpTrailState_Parms), &Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::NewProp_bEnabled_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::NewProp_bEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APlatformingCharacter, nullptr, "SetJumpTrailState", Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::PropPointers), sizeof(PlatformingCharacter_eventSetJumpTrailState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(PlatformingCharacter_eventSetJumpTrailState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class APlatformingCharacter Function SetJumpTrailState ***************************

// ********** Begin Class APlatformingCharacter ****************************************************
void APlatformingCharacter::StaticRegisterNativesAPlatformingCharacter()
{
	UClass* Class = APlatformingCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "DoDash", &APlatformingCharacter::execDoDash },
		{ "DoJumpEnd", &APlatformingCharacter::execDoJumpEnd },
		{ "DoJumpStart", &APlatformingCharacter::execDoJumpStart },
		{ "DoLook", &APlatformingCharacter::execDoLook },
		{ "DoMove", &APlatformingCharacter::execDoMove },
		{ "HasDoubleJumped", &APlatformingCharacter::execHasDoubleJumped },
		{ "HasWallJumped", &APlatformingCharacter::execHasWallJumped },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APlatformingCharacter;
UClass* APlatformingCharacter::GetPrivateStaticClass()
{
	using TClass = APlatformingCharacter;
	if (!Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PlatformingCharacter"),
			Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton,
			StaticRegisterNativesAPlatformingCharacter,
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
	return Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_APlatformingCharacter_NoRegister()
{
	return APlatformingCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APlatformingCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  An enhanced Third Person Character with the following functionality:\n *  - Platforming game character movement physics\n *  - Press and Hold Jump\n *  - Double Jump\n *  - Wall Jump\n *  - Dash\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Platforming/PlatformingCharacter.h" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An enhanced Third Person Character with the following functionality:\n- Platforming game character movement physics\n- Press and Hold Jump\n- Double Jump\n- Wall Jump\n- Dash" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Dash Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dash Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpTraceDistance_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to trace ahead of the character to look for walls to jump from */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to trace ahead of the character to look for walls to jump from" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpTraceRadius_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the wall jump sphere trace check */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the wall jump sphere trace check" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpBounceImpulse_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Impulse to apply away from the wall when wall jumping */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Impulse to apply away from the wall when wall jumping" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpVerticalImpulse_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Vertical impulse to apply when wall jumping */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical impulse to apply when wall jumping" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DelayBetweenWallJumps_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to ignore jump inputs after a wall jump */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to ignore jump inputs after a wall jump" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashMontage_MetaData[] = {
		{ "Category", "Dash" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage to use for the Dash action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage to use for the Dash action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxCoyoteTime_MetaData[] = {
		{ "Category", "Coyote Time" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that can pass since we started falling when we allow a regular jump */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that can pass since we started falling when we allow a regular jump" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DashAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpBounceImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpVerticalImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DelayBetweenWallJumps;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DashMontage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxCoyoteTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APlatformingCharacter_DoDash, "DoDash" }, // 4262667798
		{ &Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd, "DoJumpEnd" }, // 1885700105
		{ &Z_Construct_UFunction_APlatformingCharacter_DoJumpStart, "DoJumpStart" }, // 1765571907
		{ &Z_Construct_UFunction_APlatformingCharacter_DoLook, "DoLook" }, // 159118679
		{ &Z_Construct_UFunction_APlatformingCharacter_DoMove, "DoMove" }, // 2308693104
		{ &Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped, "HasDoubleJumped" }, // 2033798589
		{ &Z_Construct_UFunction_APlatformingCharacter_HasWallJumped, "HasWallJumped" }, // 2067616385
		{ &Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState, "SetJumpTrailState" }, // 2719099985
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlatformingCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MouseLookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DashAction = { "DashAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DashAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashAction_MetaData), NewProp_DashAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpTraceDistance = { "WallJumpTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpTraceDistance_MetaData), NewProp_WallJumpTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpTraceRadius = { "WallJumpTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpTraceRadius_MetaData), NewProp_WallJumpTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpBounceImpulse = { "WallJumpBounceImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpBounceImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpBounceImpulse_MetaData), NewProp_WallJumpBounceImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpVerticalImpulse = { "WallJumpVerticalImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpVerticalImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpVerticalImpulse_MetaData), NewProp_WallJumpVerticalImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DelayBetweenWallJumps = { "DelayBetweenWallJumps", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DelayBetweenWallJumps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DelayBetweenWallJumps_MetaData), NewProp_DelayBetweenWallJumps_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DashMontage = { "DashMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DashMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashMontage_MetaData), NewProp_DashMontage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MaxCoyoteTime = { "MaxCoyoteTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MaxCoyoteTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxCoyoteTime_MetaData), NewProp_MaxCoyoteTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlatformingCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MouseLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DashAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpBounceImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_WallJumpVerticalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DelayBetweenWallJumps,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_DashMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlatformingCharacter_Statics::NewProp_MaxCoyoteTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APlatformingCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlatformingCharacter_Statics::ClassParams = {
	&APlatformingCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APlatformingCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingCharacter_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlatformingCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_APlatformingCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlatformingCharacter()
{
	if (!Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton, Z_Construct_UClass_APlatformingCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlatformingCharacter);
APlatformingCharacter::~APlatformingCharacter() {}
// ********** End Class APlatformingCharacter ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingCharacter_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlatformingCharacter, APlatformingCharacter::StaticClass, TEXT("APlatformingCharacter"), &Z_Registration_Info_UClass_APlatformingCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlatformingCharacter), 581790991U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingCharacter_h__Script_TestProject_4160307825(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingCharacter_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_Platforming_PlatformingCharacter_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
