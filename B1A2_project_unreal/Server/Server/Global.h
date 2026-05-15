#pragma once
#include "ServerFramework.h"
#include "ServerNetwork.h"
#include "DataManager.h"
#include "Timer.h"

extern std::random_device rd;
extern std::mt19937 gen;

extern ServerFramework* g_framework;
extern ServerNetwork* g_network;
extern DataManager* g_dataManager;
extern Timer* g_timer;