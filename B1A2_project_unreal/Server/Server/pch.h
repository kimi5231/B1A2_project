#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <array>
#include <random>
#include <ranges>
#include <filesystem>
#include <numeric>
#include <utility> 
#include <functional>
#include <chrono>
#include <queue>
#include <cmath>
#include <algorithm>
#include <optional>
#include <MSWSock.h>

#include "Types.h"
#include "Utils.h"

#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "ws2_32")

using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;
using MonsterRef = std::shared_ptr<class Monster>;
using ItemRef = std::shared_ptr<class Item>;
using ToolRef = std::shared_ptr<class Tool>;
using DoorRef = std::shared_ptr<class Door>;
using ObstacleRef = std::shared_ptr<class Obstacle>;

#define TileSize 25

#define MAX_PLAYER 600
#define MAX_ROOM_PLAYER 4
#define MAX_MONSTER 10
#define MAX_ITEM 50
#define MAX 4