// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatEnemySpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCombatEnemySpawner() {}

// ********** Begin Cross Module References ********************************************************
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatEnemy_NoRegister();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatEnemySpawner();
B1A2_PROJECT_API UClass* Z_Construct_UClass_ACombatEnemySpawner_NoRegister();
B1A2_PROJECT_API UClass* Z_Construct_UClass_UCombatActivatable_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_B1A2_project();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACombatEnemySpawner Function ActivateInteraction *************************
struct Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics
{
	struct CombatEnemySpawner_eventActivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Activates the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Activates the Spawner" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventActivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatEnemySpawner, nullptr, "ActivateInteraction", Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::CombatEnemySpawner_eventActivateInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::CombatEnemySpawner_eventActivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatEnemySpawner::execActivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function ActivateInteraction ***************************

// ********** Begin Class ACombatEnemySpawner Function DeactivateInteraction ***********************
struct Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics
{
	struct CombatEnemySpawner_eventDeactivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deactivates the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deactivates the Spawner" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventDeactivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatEnemySpawner, nullptr, "DeactivateInteraction", Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::CombatEnemySpawner_eventDeactivateInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::CombatEnemySpawner_eventDeactivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatEnemySpawner::execDeactivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DeactivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function DeactivateInteraction *************************

// ********** Begin Class ACombatEnemySpawner Function OnEnemyDied *********************************
struct Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the spawned enemy has died */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the spawned enemy has died" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatEnemySpawner, nullptr, "OnEnemyDied", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatEnemySpawner::execOnEnemyDied)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnEnemyDied();
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function OnEnemyDied ***********************************

// ********** Begin Class ACombatEnemySpawner Function ToggleInteraction ***************************
struct Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics
{
	struct CombatEnemySpawner_eventToggleInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Toggles the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Toggles the Spawner" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventToggleInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ACombatEnemySpawner, nullptr, "ToggleInteraction", Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::PropPointers), sizeof(Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::CombatEnemySpawner_eventToggleInteraction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::Function_MetaDataParams), Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::CombatEnemySpawner_eventToggleInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ACombatEnemySpawner::execToggleInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function ToggleInteraction *****************************

// ********** Begin Class ACombatEnemySpawner ******************************************************
void ACombatEnemySpawner::StaticRegisterNativesACombatEnemySpawner()
{
	UClass* Class = ACombatEnemySpawner::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ActivateInteraction", &ACombatEnemySpawner::execActivateInteraction },
		{ "DeactivateInteraction", &ACombatEnemySpawner::execDeactivateInteraction },
		{ "OnEnemyDied", &ACombatEnemySpawner::execOnEnemyDied },
		{ "ToggleInteraction", &ACombatEnemySpawner::execToggleInteraction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatEnemySpawner;
UClass* ACombatEnemySpawner::GetPrivateStaticClass()
{
	using TClass = ACombatEnemySpawner;
	if (!Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CombatEnemySpawner"),
			Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton,
			StaticRegisterNativesACombatEnemySpawner,
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
	return Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton;
}
UClass* Z_Construct_UClass_ACombatEnemySpawner_NoRegister()
{
	return ACombatEnemySpawner::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACombatEnemySpawner_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.\n *  Enemies will be spawned one by one, and the spawner will wait until the enemy dies before spawning a new one.\n *  The spawner can be remotely activated through the ICombatActivatable interface\n *  When the last spawned enemy dies, the spawner can also activate other ICombatActivatables\n */" },
#endif
		{ "IncludePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.\nEnemies will be spawned one by one, and the spawner will wait until the enemy dies before spawning a new one.\nThe spawner can be remotely activated through the ICombatActivatable interface\nWhen the last spawned enemy dies, the spawner can also activate other ICombatActivatables" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCapsule_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnDirection_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyClass_MetaData[] = {
		{ "Category", "Enemy Spawner" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of enemy to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of enemy to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShouldSpawnEnemiesImmediately_MetaData[] = {
		{ "Category", "Enemy Spawner" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the first enemy will be spawned as soon as the game starts */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the first enemy will be spawned as soon as the game starts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialSpawnDelay_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the first enemy on game start */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the first enemy on game start" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCount_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of enemies to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of enemies to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnDelay_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the next enemy after the current one dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the next enemy after the current one dies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActivationDelay_MetaData[] = {
		{ "Category", "Activation" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait after this spawner is depleted before activating the actor list */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait after this spawner is depleted before activating the actor list" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorsToActivateWhenDepleted_MetaData[] = {
		{ "Category", "Activation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** List of actors to activate after the last enemy dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "List of actors to activate after the last enemy dies" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnCapsule;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnDirection;
	static const UECodeGen_Private::FClassPropertyParams NewProp_EnemyClass;
	static void NewProp_bShouldSpawnEnemiesImmediately_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldSpawnEnemiesImmediately;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialSpawnDelay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SpawnCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnDelay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ActivationDelay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorsToActivateWhenDepleted_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActorsToActivateWhenDepleted;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction, "ActivateInteraction" }, // 1972102105
		{ &Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction, "DeactivateInteraction" }, // 2906056636
		{ &Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied, "OnEnemyDied" }, // 259106207
		{ &Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction, "ToggleInteraction" }, // 59750146
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatEnemySpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnCapsule = { "SpawnCapsule", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnCapsule), Z_Construct_UClass_UCapsuleComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCapsule_MetaData), NewProp_SpawnCapsule_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnDirection = { "SpawnDirection", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnDirection), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnDirection_MetaData), NewProp_SpawnDirection_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_EnemyClass = { "EnemyClass", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, EnemyClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ACombatEnemy_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyClass_MetaData), NewProp_EnemyClass_MetaData) };
void Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_bShouldSpawnEnemiesImmediately_SetBit(void* Obj)
{
	((ACombatEnemySpawner*)Obj)->bShouldSpawnEnemiesImmediately = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_bShouldSpawnEnemiesImmediately = { "bShouldSpawnEnemiesImmediately", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ACombatEnemySpawner), &Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_bShouldSpawnEnemiesImmediately_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShouldSpawnEnemiesImmediately_MetaData), NewProp_bShouldSpawnEnemiesImmediately_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_InitialSpawnDelay = { "InitialSpawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, InitialSpawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialSpawnDelay_MetaData), NewProp_InitialSpawnDelay_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnCount = { "SpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCount_MetaData), NewProp_SpawnCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_RespawnDelay = { "RespawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, RespawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnDelay_MetaData), NewProp_RespawnDelay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActivationDelay = { "ActivationDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, ActivationDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActivationDelay_MetaData), NewProp_ActivationDelay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActorsToActivateWhenDepleted_Inner = { "ActorsToActivateWhenDepleted", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActorsToActivateWhenDepleted = { "ActorsToActivateWhenDepleted", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, ActorsToActivateWhenDepleted), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorsToActivateWhenDepleted_MetaData), NewProp_ActorsToActivateWhenDepleted_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACombatEnemySpawner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnCapsule,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_EnemyClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_bShouldSpawnEnemiesImmediately,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_InitialSpawnDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_SpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_RespawnDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActivationDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActorsToActivateWhenDepleted_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACombatEnemySpawner_Statics::NewProp_ActorsToActivateWhenDepleted,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatEnemySpawner_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACombatEnemySpawner_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_project,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatEnemySpawner_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ACombatEnemySpawner_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatActivatable_NoRegister, (int32)VTABLE_OFFSET(ACombatEnemySpawner, ICombatActivatable), false },  // 2713258972
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACombatEnemySpawner_Statics::ClassParams = {
	&ACombatEnemySpawner::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ACombatEnemySpawner_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ACombatEnemySpawner_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACombatEnemySpawner_Statics::Class_MetaDataParams), Z_Construct_UClass_ACombatEnemySpawner_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACombatEnemySpawner()
{
	if (!Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton, Z_Construct_UClass_ACombatEnemySpawner_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACombatEnemySpawner);
ACombatEnemySpawner::~ACombatEnemySpawner() {}
// ********** End Class ACombatEnemySpawner ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatEnemySpawner_h__Script_B1A2_project_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatEnemySpawner, ACombatEnemySpawner::StaticClass, TEXT("ACombatEnemySpawner"), &Z_Registration_Info_UClass_ACombatEnemySpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatEnemySpawner), 982335186U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatEnemySpawner_h__Script_B1A2_project_1147646186(TEXT("/Script/B1A2_project"),
	Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatEnemySpawner_h__Script_B1A2_project_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_project_Source_B1A2_project_Variant_Combat_AI_CombatEnemySpawner_h__Script_B1A2_project_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
