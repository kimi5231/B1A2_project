#pragma once

using uint = unsigned int;

enum class ObjectType
{
	Player,
};

enum ObjectState
{
	IDLE,
	RUN,
	JUMP,
};

enum Dir
{
	Front,
	Right,
	Back,
	Left,
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
	StorageRoom_Rect,
	StorageRoom_Corner,
	StorageRoom_Step,
	YellowOfficeRoom,
	PipedHallways,
	FactoryRoom,
};

enum Difficulty 
{
	Easy,
	Normal,
	Hard,

	DifficultyCount,
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
	std::unordered_map<Difficulty, uint> minCreateCount;
	std::unordered_map<Difficulty, uint> maxCreateCount;
	std::unordered_map<Difficulty, float> spawnChance;
	std::pair<uint, uint> doorCount;
	std::vector<Vector> doorPos;
};