#pragma once

using uint = unsigned int;

enum class ObjectType
{
	Player,
};

enum MoveState
{
	MOVE_STATE_IDLE,
	MOVE_STATE_RUN,
	MOVE_STATE_JUMP,
};

enum class GameRoomType
{
	MainEntranceRoom,
	GapRoom,
	Staircase,
	RailCatwalk,
	ApparatusRoom,
	ServerRoom,
	CabinetRoom,
	StorageRoom,

	PipedHallways,
	FactoryRoom,

	GameRoomTypeCount,
};

enum Difficulty 
{
	Easy,
	Normal,
	Hard,
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

struct GameRoomInfo
{
	GameRoomType type;
	Vector pos;
	Vector size;
	bool isCreateItem;
	bool isCreateExit;
	std::unordered_map<std::string, uint> minCreateCount;
	std::unordered_map<std::string, uint> maxCreateCount;
	float spawnChance;
	uint minDoorCount;
	uint maxDoorCount;
	std::vector<Vector> doorPos;
};