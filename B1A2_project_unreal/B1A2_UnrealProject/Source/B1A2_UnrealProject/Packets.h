#pragma once


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