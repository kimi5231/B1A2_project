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

// Sound
#include <MMSystem.h>
#include <dsound.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dsound.lib")

//#include <fmod_studio.hpp>  // ��� ���� (���� ���͸� ���� �ʿ�)
//#pragma comment(lib, "fmodstudio_vc.lib")  // ���� ���̺귯�� ��ũ
//#pragma comment(lib, "fmodstudioL_vc.lib") // ����׿� ���̺귯�� ��ũ