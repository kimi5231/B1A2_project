// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSideScrollingGameMode() {}

// ********** Begin Cross Module References ********************************************************
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingGameMode();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_ASideScrollingGameMode_NoRegister();
B1A2_UNREALPROJECT_API UClass* Z_Construct_UClass_USideScrollingUI_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_B1A2_UnrealProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASideScrollingGameMode ***************************************************
void ASideScrollingGameMode::StaticRegisterNativesASideScrollingGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingGameMode;
UClass* ASideScrollingGameMode::GetPrivateStaticClass()
{
	using TClass = ASideScrollingGameMode;
	if (!Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SideScrollingGameMode"),
			Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton,
			StaticRegisterNativesASideScrollingGameMode,
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
	return Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ASideScrollingGameMode_NoRegister()
{
	return ASideScrollingGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASideScrollingGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple Side Scrolling Game Mode\n *  Spawns and manages the game UI\n *  Counts pickups collected by the player\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple Side Scrolling Game Mode\nSpawns and manages the game UI\nCounts pickups collected by the player" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserInterfaceClass_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Class of UI widget to spawn when the game starts */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Class of UI widget to spawn when the game starts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserInterface_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** User interface widget for the game */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "User interface widget for the game" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupsCollected_MetaData[] = {
		{ "Category", "Pickups" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of pickups collected by the player */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of pickups collected by the player" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_UserInterfaceClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UserInterface;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PickupsCollected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_UserInterfaceClass = { "UserInterfaceClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, UserInterfaceClass), Z_Construct_UClass_UClass, Z_Construct_UClass_USideScrollingUI_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserInterfaceClass_MetaData), NewProp_UserInterfaceClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_UserInterface = { "UserInterface", nullptr, (EPropertyFlags)0x012408000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, UserInterface), Z_Construct_UClass_USideScrollingUI_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserInterface_MetaData), NewProp_UserInterface_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_PickupsCollected = { "PickupsCollected", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, PickupsCollected), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupsCollected_MetaData), NewProp_PickupsCollected_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASideScrollingGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_UserInterfaceClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_UserInterface,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASideScrollingGameMode_Statics::NewProp_PickupsCollected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASideScrollingGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_B1A2_UnrealProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASideScrollingGameMode_Statics::ClassParams = {
	&ASideScrollingGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASideScrollingGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingGameMode_Statics::PropPointers),
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASideScrollingGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASideScrollingGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASideScrollingGameMode()
{
	if (!Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton, Z_Construct_UClass_ASideScrollingGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton;
}
ASideScrollingGameMode::ASideScrollingGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASideScrollingGameMode);
ASideScrollingGameMode::~ASideScrollingGameMode() {}
// ********** End Class ASideScrollingGameMode *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingGameMode_h__Script_B1A2_UnrealProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingGameMode, ASideScrollingGameMode::StaticClass, TEXT("ASideScrollingGameMode"), &Z_Registration_Info_UClass_ASideScrollingGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingGameMode), 23241528U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingGameMode_h__Script_B1A2_UnrealProject_1383911518(TEXT("/Script/B1A2_UnrealProject"),
	Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingGameMode_h__Script_B1A2_UnrealProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_B1A2_UnrealProject_Source_B1A2_UnrealProject_Variant_SideScrolling_SideScrollingGameMode_h__Script_B1A2_UnrealProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
