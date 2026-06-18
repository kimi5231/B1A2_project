#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define FD_SETSIZE 600
#define DummyCount 150

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <variant>
#include <memory>
#include <mutex>
#include <string>
#include <filesystem>
#include <chrono>

#include "../../Server/Server/Packets.h"
#include "../../Server/Server/Types.h"

#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "ws2_32")

// 매크로 충돌 방지
#undef min
#undef max

enum class DummyState
{
	Title,
	Lobby,
	Room,
	Play,
};

struct NetworkEvent
{
	bool isComplete = false;
	PacketID packetID;
	std::vector<char> serializedPacketData;
};

using NetworkEventRef = std::shared_ptr<NetworkEvent>;

struct DummyPlayer
{
	DummyState state;
	SOCKET socket;
	int dummyID;
	std::vector<NetworkEventRef> sendEvents;
	int clientID;
	int playerID;
	Vector pos;
};