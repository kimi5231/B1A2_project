#pragma once

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <random>

#include "Types.h"
#include "Defines.h"
#include "Values.h"
#include "Enums.h"
#include "Utils.h"

//using namespace std;

// C++ 20
#include <format>
#include <filesystem>

// Memory leak 확인 - CRT 라이브러리의 디버그 기능 활성화하는 것, 출력창에 메모리 해제 안 된 것 알려줌.
#define _CRTDEBG_MAP_ALLOC		
#include <cstdlib>				
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// TransparentBlt
#pragma comment(lib, "msimg32.lib")

// Window API
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")