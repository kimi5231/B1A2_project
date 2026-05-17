#pragma once

#define PORT 7777
#define BufferSize 10000

using TimePoint = std::chrono::steady_clock::time_point;
using FloatSec = std::chrono::duration<float>;

//------------------Enums------------------
enum class IOType
{
	Send,
	Recv,
	Accept,
};

enum class ObjectType : char
{
	Player,
	Monster,
	Item,
	Obstacle,
	Door,
	SellingMachine,
};

enum class MonsterType : char
{
	Spider,
	EmotionGame,
	Ghost,

	MonsterTypeCount,
};

enum ItemType : char
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
	CUTLASS,
	Blaster,
	Key,
	LANTERN,

	ItemTypeCount,

	None,
};

enum class ObstacleType : char
{
	Web,

	ObstacleTypeCount,
};

// 쓸지말지 고민중
enum class StructureType : char
{
	SellingMachine,

	StructureTypeCount,
};

enum ObjectState : char
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

	// Structure
	LOCK,
	OPEN,
	CLOSE,

	// Monster
	MAKE_WEB,
	ROAMING,
	CHASE,
	ATTACK,
	RETURN,
	TELEPORT,
	GRAB,
	PLAY,
	RELEASE,
	ABSENT,
	STARING,
	VANISHING,
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

	Base,

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

enum class Emotion
{
	Angry,
	Disgust,
	Fear,
	Happy,
	Sad,
	Surprise,
	Neutral ,

	EmotionCount
};

enum class EmotionGameResult
{
	Win,
	Lose,
	Draw,
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
struct VectorInt;

struct Vector
{
	float x;
	float y;
	float z;

	inline Vector() : x(0), y(0), z(0) {}
	inline Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
	inline Vector(const VectorInt& other);

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

	Vector operator*(const int value) const
	{
		return { x * value, y * value, z * value };
	}

	void operator*=(const int value)
	{
		x*= value;
		y*= value;
		z*= value;
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

	bool operator==(const Vector& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	float Length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	float LengthSquared() const {
		return x * x + y * y + z * z;
	}

	void Normalize()
	{
		float len = Length();
		if (len > 0.0001f) // 0으로 나누기 방지
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	float Dot(const Vector& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
};

struct VectorInt
{
	int x;
	int y;
	int z;

	inline VectorInt() : x(0), y(0), z(0) {}
	inline VectorInt(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
	inline VectorInt(const Vector& other)
	{
		x = static_cast<int>(other.x);
		y = static_cast<int>(other.y);
		z = static_cast<int>(other.z);
	}
	inline VectorInt(size_t X, size_t Y, size_t Z)
	{
		x = static_cast<int>(X);
		y = static_cast<int>(Y);
		z = static_cast<int>(Z);
	}
	inline VectorInt(float X, float Y, float Z)
	{
		x = static_cast<int>(X);
		y = static_cast<int>(Y);
		z = static_cast<int>(Z);
	}

	VectorInt operator+(const VectorInt& other) const
	{
		return VectorInt( other.x + x, other.y + y, other.z + z );
	}

	VectorInt operator-(const VectorInt& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	VectorInt operator/(const int value) const
	{
		return { x / value, y / value, z / value };
	}

	VectorInt operator*(const int value) const
	{
		return { x * value, y * value, z * value };
	}

	bool operator<(const VectorInt& other) const
	{
		return (x < other.x || y < other.y || z < other.z);
	}

	bool operator>(const VectorInt& other) const
	{
		return (x > other.x || y > other.y || z > other.z);
	}

	bool operator>=(const VectorInt& other) const
	{
		return (x >= other.x || y >= other.y || z >= other.z);
	}

	bool operator==(const VectorInt& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	VectorInt& operator=(const Vector& other)
	{
		x = static_cast<int>(other.x);
		y = static_cast<int>(other.y);
		z = static_cast<int>(other.z);
		return *this;
	}
};

Vector::Vector(const VectorInt& other)
{
	x = static_cast<float>(other.x);
	y = static_cast<float>(other.y);
	z = static_cast<float>(other.z);
}

// unordered map에 Vector를 쓰기 위해 필요한 구조체
struct VectorHash
{
	size_t operator()(const Vector& v) const noexcept
	{
		// 두 값을 섞어서 Hash 생성
		std::size_t h1 = std::hash<float>()(v.x);
		std::size_t h2 = std::hash<float>()(v.y);
		std::size_t h3 = std::hash<float>()(v.z);
		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

struct VectorIntHash
{
	size_t operator()(const VectorInt& v) const noexcept
	{
		// 두 값을 섞어서 Hash 생성
		std::size_t h1 = std::hash<int>()(v.x);
		std::size_t h2 = std::hash<int>()(v.y);
		std::size_t h3 = std::hash<int>()(v.z);
		return h1 ^ (h2 << 1) ^ (h3 << 2);
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

using CubeRef = std::shared_ptr<class Cube>;

struct CubeNode
{
	CubeRef cube;
	float g, h, f;
	CubeNode* parent;
};

struct TileNode
{
	//VectorInt pos;
	VectorInt index;
	float g, h, f;
	TileNode* parent;
};

struct CubeInfo
{
	CubeType type;
	Vector size;
	bool isCreateItem;
	bool isCreateExit;
	bool isCreateSellingMachine;
	std::unordered_map<Difficulty, int> minCreateCount;
	std::unordered_map<Difficulty, int> maxCreateCount;
	std::unordered_map<Difficulty, float> spawnChance;
	/*std::pair<uint, uint> f1DoorCount;
	std::pair<uint, uint> f2DoorCount;
	std::vector<Vector> f1DoorPos;
	std::vector<Vector> f2DoorPos;*/
	std::vector<Vector> sellingMachinePos;
	std::vector<Dir> sellingMachineDir;
	std::vector<Vector> doorPos;
	std::vector<Dir> doorDir;
	int enterDistance;
};

struct CubeConditionInfo
{
	int totalCubeCount;
	std::pair<int, int> createItemCount;
	std::pair<int, int> createExitCount;
	int createSellingMachineCount;
	int createSpecialSellingMachineCount;
	std::pair<int, int> sellingMachineCreditLimit;
	std::pair<int, int> exitPos;
	std::pair<int, int> floor;
};

struct SpiderStatus
{
	float hp;
	float speed;
	float chaseSpeed;
	float chaseTime;
	float openDoorTime;
	float attackDelay;
	unsigned char attackDamage;
	float makeWebTime;
	unsigned char maxWebCount;
	float pauseTime;
	float roamingTime;
};