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

#include "Types.h"

#pragma comment(lib, "ws2_32")

using SendEventRef = std::shared_ptr<class SendEvent>;

using ClientRef = std::shared_ptr<class Client>;
using RoomRef = std::shared_ptr<class Room>;

using GameRoomRef = std::shared_ptr<class GameRoom>;
using GameObjectRef = std::shared_ptr<class GameObject>;
using PlayerRef = std::shared_ptr<class Player>;