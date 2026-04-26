#include "pch.h"
#include "Global.h"
#include <ctime>

std::random_device rd;
std::mt19937 gen(static_cast<unsigned int>(std::time(NULL)));

ServerFramework* g_framework = nullptr;
DataManager* g_dataManager = nullptr;
Timer* g_timer = nullptr;