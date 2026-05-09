// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Components/PointLightComponent.h"

ALantern::ALantern()
{
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(RootComponent);

    PointLight->SetIntensity(1500.f);      // ¹à±â
    PointLight->SetLightColor(FLinearColor(1.0f, 0.6f, 0.2f)); // µû¶æÇÑ ¿À·»Áö»ö
    PointLight->SetVisibility(false);
}

void ALantern::UpdateLantern(bool isOn, float range)
{
    PointLight->SetVisibility(isOn);
    if (isOn)
    {
        PointLight->SetAttenuationRadius(range);
    }
}