#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define FD_SETSIZE 600

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <mutex>
#include <string>
#include <filesystem>

#include "../../Server/Server/Packets.h"
#include "../../Server/Server/Types.h"

#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "ws2_32")

// 매크로 충돌 방지
#undef min
#undef max

struct NetworkEvent
{
	bool isComplete = false;
	PacketID packetID;
	std::vector<char> serializedPacketData;
};

using NetworkEventRef = std::shared_ptr<NetworkEvent>;