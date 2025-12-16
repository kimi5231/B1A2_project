#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

enum class ObjectType
{
	Player,
	Box,
};

enum PacketID
{
	// Client
	C_Move,

	//Server
	S_AddObject,
	S_Move
};

struct Header
{
	PacketID id;
	int dataSize;
};

// Client
struct C_Move_Packet
{
	int objectID;
	FVector pos;
	FRotator rotation;
};

// Server
struct S_AddObject_Packet
{
	int objectID;
	FVector initialLocation;
	FRotator initialRotaion;
};

struct S_Move_Packet
{
	int objectID;
	FVector pos;
	FRotator rotation;
};

using GameObjectRef = std::shared_ptr<class GameObject>;