#include "pch.h"
#include "Global.h"

std::random_device rd;
std::mt19937 gen(rd());

ServerFramework* g_framework = new ServerFramework();