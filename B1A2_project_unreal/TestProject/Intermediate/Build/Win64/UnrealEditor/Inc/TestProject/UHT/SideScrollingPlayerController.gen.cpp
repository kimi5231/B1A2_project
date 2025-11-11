// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingPlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingCharacter_NoRegister();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPlayerController();
TESTPROJECT_API UClass* Z_Construct_UClass_ASideScrollingPlayerController_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingPlayerController Function OnPawnDestroyed ******************
struct Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics
{
	struct SideScrollingPlayerController_eventOnPawnDestroyed_Parms
	{
		AActor* DestroyedActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called if the possessed pawn is destroyed */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called if the possessed pawn is destroyed" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DestroyedActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::NewProp_DestroyedActor = { "DestroyedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPlayerController_eventOnPawnDestroyed_Parms, DestroyedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::NewProp_DestroyedActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASideScrollingPlayerController, nullptr, "OnPawnDestroyed", Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::SideScrollingPlayerController_eventOnPawnDestroyed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::SideScrollingPlayerController_eventOnPawnDestroyed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASideScrollingPlayerController::execOnPawnDestroyed)
{
	P_GET_OBJECT(AActor,Z_Param_DestroyedActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPawnDestroyed(Z_Param_DestroyedActor);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingPlayerController Function OnPawnDestroyed ********************

// ********** Begin Class ASideScrollingPlayerController *******************************************
void ASideScrollingPlayerController::StaticRegisterNativesASideScrollingPlayerController()
{
	UClass* Class = ASideScrollingPlayerController::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnPawnDestroyed", &ASideScrollingPlayerController::execOnPawnDestroyed },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingPlayerController;
UClass* ASideScrollingPlayerController::GetPrivateStaticClass()
{
	using TClass = ASideScrollingPlayerController;
	if (!Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingPlayerController"),
			Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton,
			StaticRegisterNativesASideScrollingPlayerController,
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
	return Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingPlayerController_NoRegister()
{
	return ASideScrollingPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple Side Scrolling Player Controller\n *  Manages input mappings\n *  Respawns the player pawn at the player start if it is destroyed\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple Side Scrolling Player Controller\nManages input mappings\nRespawns the player pawn at the player start if it is destroyed" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContexts_MetaData[] = {
		{ "Category", "Input|Input Mappings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mapping context for this player */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mapping context for this player" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MobileExcludedMappingContexts_MetaData[] = {
		{ "Category", "Input|Input Mappings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Mapping Contexts */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Mapping Contexts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MobileControlsWidgetClass_MetaData[] = {
		{ "Category", "Input|Touch Controls" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mobile controls widget to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mobile controls widget to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterClass_MetaData[] = {
		{ "Category", "Respawn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character class to respawn when the possessed pawn is destroyed */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character class to respawn when the possessed pawn is destroyed" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultMappingContexts;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MobileExcludedMappingContexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MobileExcludedMappingContexts;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MobileControlsWidgetClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_CharacterClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed, "OnPawnDestroyed" }, // 3365004626
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_DefaultMappingContexts_Inner = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_DefaultMappingContexts = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, DefaultMappingContexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContexts_MetaData), NewProp_DefaultMappingContexts_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileExcludedMappingContexts_Inner = { "MobileExcludedMappingContexts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileExcludedMappingContexts = { "MobileExcludedMappingContexts", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, MobileExcludedMappingContexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MobileExcludedMappingContexts_MetaData), NewProp_MobileExcludedMappingContexts_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileControlsWidgetClass = { "MobileControlsWidgetClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, MobileControlsWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MobileControlsWidgetClass_MetaData), NewProp_MobileControlsWidgetClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_CharacterClass = { "CharacterClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, CharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ASideScrollingCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterClass_MetaData), NewProp_CharacterClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_DefaultMappingContexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_DefaultMappingContexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileExcludedMappingContexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileExcludedMappingContexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_MobileControlsWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingPlayerController_Statics::NewProp_CharacterClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_TestProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingPlayerController_Statics::ClassParams = {
	&ASideScrollingPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASideScrollingPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPlayerController_Statics::PropPointers),
	0,
	0x008003A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingPlayerController()
{
	if (!Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton, Z_Construct_UClass_ASideScrollingPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton;
}
ASideScrollingPlayerController::ASideScrollingPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingPlayerController);
ASideScrollingPlayerController::~ASideScrollingPlayerController() {}
// ********** End Class ASideScrollingPlayerController *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_SideScrollingPlayerController_h__Script_TestProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingPlayerController, ASideScrollingPlayerController::StaticClass, TEXT("ASideScrollingPlayerController"), &Z_Registration_Info_UClass_ASideScrollingPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingPlayerController), 1735371259U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_SideScrollingPlayerController_h__Script_TestProject_67654192(TEXT("/Script/TestProject"),
	Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_SideScrollingPlayerController_h__Script_TestProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_GitHub_B1A2_project_B1A2_project_unreal_TestProject_Source_TestProject_Variant_SideScrolling_SideScrollingPlayerController_h__Script_TestProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
