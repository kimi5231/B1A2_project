// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UMain;

/**
 * 
 */
class B1A2_UNREALPROJECT_API NetworkRunnable : public FRunnable
{
public:
    NetworkRunnable(UMain* main);
    virtual ~NetworkRunnable();

    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;

private:
    UMain* _main;
    FThreadSafeBool _running;
};
