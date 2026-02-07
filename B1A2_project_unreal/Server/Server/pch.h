#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <array>
#include <random>
#include <ranges>
#include <filesystem>
#include <numeric>
#include <utility> 
#include <functional>

#include "Types.h"

#pragma comment(lib, "ws2_32")

using SendEventRef = std::shared_ptr<class SendEvent>;

using ClientRef = std::shared_ptr<class Client>;
using RoomRef = std::shared_ptr<class Room>;

using GameRoomRef = std::shared_ptr<class GameRoom>;
using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;
using MonsterRef = std::shared_ptr<class Monster>;
using DoorRef = std::shared_ptr<class Door>;

#define Width 10000
#define Height 10000

// 비트연산
#define LAYER_SHIFT(n) ((n) * 2)
#define LAYER_MASK(n)  (0b11 << LAYER_SHIFT(n))