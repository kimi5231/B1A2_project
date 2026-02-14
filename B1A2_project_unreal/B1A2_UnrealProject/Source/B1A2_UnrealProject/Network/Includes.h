#pragma once
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory> 

#include "Packets.h"
#include "UnrealPackets.h"

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