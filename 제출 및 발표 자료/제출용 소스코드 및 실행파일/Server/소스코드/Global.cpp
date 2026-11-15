#include "pch.h"
#include "Global.h"
#include <ctime>

std::random_device rd;
std::mt19937 gen(static_cast<unsigned int>(std::time(NULL)));

ServerNetwork* g_network = nullptr;
DataManager* g_dataManager = nullptr;
DBManager* g_dbManager = nullptr;
Timer* g_timer = nullptr;