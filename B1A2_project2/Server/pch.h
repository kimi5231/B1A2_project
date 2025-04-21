#pragma once

#include "CorePch.h"

#ifdef _DEBUG   // 디버그 모드일 때
#pragma comment(lib, "Debug\\ServerCore.lib")
#else          // 릴리즈 모드일 때
#pragma comment(lib, "Release\\ServerCore.lib")
#endif

