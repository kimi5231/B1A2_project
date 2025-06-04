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

// Server
#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

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

// Window API
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")