#pragma once

using uint = unsigned int;

//------------------Enums------------------
enum class ObjectType : char
{
	Player,
	Monster,
	Item,
	Door,
};

enum ObjectState
{
	IDLE,
	RUN,
	JUMP,
	CROUCHED,

	// Interaction
	OPEN_DOOR,
	CLOSE_DOOR,
	GET_ITEM,

	// Tool
	SLASH,
	SHOOT,

	// Etc
	HIT,
	DEAD,

	// Door
	LOCK,
	OPEN,
	CLOSE,
};

enum class ObjectPoolState 
{
	InWorld, 
	InInventory,
	Reusable,
};

enum Dir
{
	Front,
	Right,
	Back,
	Left,

	DirCount
};

enum class CubeType
{
	MainEntranceRoom,

	GapRoom,
	ApparatusRoom,
	ServerRoom,
	CabinetRoom,
	StorageRoom_Rect,
	StorageRoom_Corner,
	StorageRoom_Step,
	YellowOfficeRoom,
	FactoryRoom,

	RailCatwalk,
	PipedHallways_Line,
	PipedHallways_Grid,

	Staircase,

	GameRoomTypeCount,
};

enum class DoorType
{
	Wall,
	Door,
};

enum Difficulty 
{
	Easy,
	Normal,
	Hard,

	DifficultyCount,
};

enum TileState : short
{
	Impassable = 0b00, // 갈 수 없음 + 물체 없음
	Passable = 0b01, // 갈 수 있음 + 물체 없음
	Wall = 0b10, // 갈 수 없음 + 물체 있음 == 벽
	Occupied = 0b11  // 갈 수 있음 + 물체 있음
};

enum ItemType
{
	CardboardBox,
	GoldBar,
	RubberDuck,
	PlasticCrate,
	Screw,
	PirateHat,
	HardHat,
	EngineCore,
	ScrapMetal,
	EmptyCan,

	// Tool
	Cutlass,
	Blaster,
	Key,
	Lantern,

	ItemTypeCount,
};

enum Floor
{
	B2 = -2,
	B1 = -1,
	F1_Base = 0,
	F1_Top = 1,
	F2 = 2,
	F3 = 3,
};

enum Corner
{
	LeftFrontBottom,
	LeftFrontTop,
	LeftBackBottom,
	LeftBackTop,
	RightFrontBottom,
	RightFrontTop,
	RightBackBottom,
	RightBackTop,

	CornerCount
};

//------------------Struct------------------
// unordered map에 pair를 쓰기 위해 필요한 구조체
struct PairHash
{
	size_t operator()(const std::pair<int, int>& p) const noexcept 
	{
		// 두 값을 섞어서 Hash 생성
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

struct Vector
{
	float x;
	float y;
	float z;

	Vector operator+(const Vector& other) const
	{
		return {other.x + x, other.y + y, other.z + z};
	}

	Vector operator-(const Vector& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector operator/(const int value) const
	{
		return { x/ value, y/ value, z/ value };
	}

	bool operator<(const Vector& other) const
	{
		return (x < other.x || y < other.y || z < other.z);
	}

	bool operator>(const Vector& other) const
	{
		return (x > other.x || y > other.y || z > other.z);
	}

	bool operator>=(const Vector& other) const
	{
		return (x >= other.x || y >= other.y || z >= other.z);
	}
};

struct AABB
{
	Vector min;
	Vector max;
};

struct Rotation
{
	float pitch;
	float yaw;
	float roll;
};

struct CubeInfo
{
	CubeType type;
	Vector size;
	bool isCreateItem;
	bool isCreateExit;
	std::unordered_map<Difficulty, uint> minCreateCount;
	std::unordered_map<Difficulty, uint> maxCreateCount;
	std::unordered_map<Difficulty, float> spawnChance;
	/*std::pair<uint, uint> f1DoorCount;
	std::pair<uint, uint> f2DoorCount;
	std::vector<Vector> f1DoorPos;
	std::vector<Vector> f2DoorPos;*/
	std::vector<Vector> doorPos;
	std::vector<Dir> doorDir;
	int enterDistance;
};

struct CubeConditionInfo
{
	uint totalCubeCount;
	std::pair<uint, uint> createItemCount;
	std::pair<uint, uint> createExitCount;
	std::pair<uint, uint> exitPos;
	std::pair<uint, uint> floor;
};