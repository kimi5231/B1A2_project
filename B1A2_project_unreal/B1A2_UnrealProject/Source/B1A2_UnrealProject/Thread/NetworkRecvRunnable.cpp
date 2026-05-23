// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkRecvRunnable.h"
#include "Main/Main.h"


NetworkRunnable::NetworkRunnable(UMain* main)
	: _main(main)
{
	_running = true;
}

NetworkRunnable::~NetworkRunnable()
{
	
}

bool NetworkRunnable::Init()
{
	return true;
}

uint32 NetworkRunnable::Run()
{
	while (_running)
	{
		if (_main)
		{
			_main->Update();	// Recv
		}
	}

	return 0;
}

void NetworkRunnable::Stop()
{
	_running = false;
}