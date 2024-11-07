#pragma once

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>

#include "Types.h"
#include "Defines.h"
#include "Values.h"
#include "Enums.h"
#include "Utils.h"

//using namespace std;

// C++ 20
#include <format>
#include <filesystem>

// Memory leak Ȯ�� - CRT ���̺귯���� ����� ��� Ȱ��ȭ�ϴ� ��, ���â�� �޸� ���� �� �� �� �˷���.
#define _CRTDEBG_MAP_ALLOC		
#include <cstdlib>				
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// TransparentBlt
#pragma comment(lib, "msimg32.lib")