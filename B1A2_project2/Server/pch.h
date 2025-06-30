#pragma once

// 제일 위에 둬야 함
#include "CorePch.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

#include "Defines.h"

#include <filesystem>

// 라이브러리
#ifdef _DEBUG   // 디버그 모드일 때
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else          // 릴리즈 모드일 때
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

using GameSessionRef = std::shared_ptr<class GameSession>;

using GameRoomRef = std::shared_ptr<class GameRoom>;

using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;
using MonsterRef = std::shared_ptr<class Monster>;