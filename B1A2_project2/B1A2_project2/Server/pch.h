#pragma once

// 제일 위에 둬야 함
#include "CorePch.h"
#include "Defines.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

// Librarise
#ifdef _DEBUG 
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else       
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

// shared_ptr
using GameSessionRef = std::shared_ptr<class GameSession>;

using GameRoomRef = std::shared_ptr<class GameRoom>;

using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;
using MonsterRef = std::shared_ptr<class Monster>;
using TiredOfficeWorkerRef = std::shared_ptr<class TiredOfficeWorker>;
using BrokenCopyMachineRef = std::shared_ptr<class BrokenCopyMachine>;

// Object State
using ObjectState = Protocol::OBJECT_STATE_TYPE;

// Direction
using Dir = Protocol::DIR_TYPE;