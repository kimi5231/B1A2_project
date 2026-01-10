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

// 매크로 충돌 방지
#undef min
#undef max

template <class T>
struct NetworkEvent
{
	bool isComplete = false;
	PacketID packetID;
	T packetData;
};

template <class T>
using NetworkEventRef = std::shared_ptr<NetworkEvent<T>>;

using RecvEventType = std::variant<NetworkEventRef<S_AddObject_Packet>, NetworkEventRef<S_Move_Packet>, 
	NetworkEventRef<S_UpdateObjectState_Packet>>;
using SendEventType = std::variant<NetworkEventRef<C_UpdateObjectState_Packet>, NetworkEventRef<C_Move_Packet>>;