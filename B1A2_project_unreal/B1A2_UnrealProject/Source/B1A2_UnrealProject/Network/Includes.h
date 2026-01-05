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
struct RecvEvent
{
	bool isComplete = false;
	PacketID packetID;
	T packetData;
};

template <class T>
using RecvEventRef = std::shared_ptr<RecvEvent<T>>;

using RecvEventType = std::variant<RecvEventRef<S_AddObject_Packet>, RecvEventRef<S_Move_Packet>>;