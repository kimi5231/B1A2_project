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

struct Vector
{
	float x;
	float y;
	float z;
};

struct Rotation
{
	float pitch;
	float yaw;
	float roll;
};

// Client
struct C_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
};

// Server
struct S_AddObject_Packet
{
	int objectID;
	Vector initialLotation;
	Rotation initialRotation;
};

struct S_Move_Packet
{
	int objectID;
	Vector pos;
	Rotation rotation;
};