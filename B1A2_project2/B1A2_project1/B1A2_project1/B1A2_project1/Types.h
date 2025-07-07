#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

// Object Stat
struct CommonStat
{
	int32 id;
	int32 hp;
};

struct MonsterStat
{
	int32 id;
	int32 hp;
	float healItemDropRate;
	float speed;
	int32 knockBackDistance;
	int32 backStepDistance;
	float dashSpeed;
	int32 dashDistance;
	float chaseSpeed;
	float idleTime;
	int32 playerDetectionX;
	int32 playerDetectionY;
	int32 closeAttackRange;
	int32 closeAttack;
	int32 longAttackRange;
	int32 longAttack;
	int32 projectileSpeed;
	int32 projectileCount;
	// 삭제 예정
	std::wstring projectileTypeWidth;
	std::wstring projectileTypeHighet;
	float longAttackTime;
	int32 slashAttack;
};

// 2차원 벡터
struct Vec2
{
	float x;
	float y;

	Vec2() : x(0.f), y(0.f) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(POINT pt) : x((float)pt.x), y((float)pt.y) {}
	
	Vec2 operator+(const Vec2& other)
	{
		Vec2 ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vec2 operator-(const Vec2& other)
	{
		Vec2 ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vec2 operator*(const Vec2& other)
	{
		Vec2 ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
		return ret;
	}

	Vec2 operator*(float value)
	{
		Vec2 ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	bool operator==(const Vec2& other) const
	{
		return x == other.x && y == other.y;
	}

	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	Vec2 Normalize()
	{
		float length = Length();
		if (length < 0.0000000001f)
			return Vec2(0, 0);

		return Vec2(x / length, y / length);
	}

	float Dot(Vec2 other)
	{
		return x * other.x + y * other.y;
	}

	float Cross(Vec2 other)
	{
		return x * other.y - y * other.x;
	}
};

struct Vec2Int
{
	int32 x;
	int32 y;

	Vec2Int() : x(0), y(0) {}
	Vec2Int(int32 x, int32 y) : x(x), y(y) {}
	Vec2Int(POINT pt) : x((int)pt.x), y((int)pt.y) {}

	Vec2Int operator+(const Vec2Int& other)
	{
		Vec2Int ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vec2Int operator-(const Vec2Int& other)
	{
		Vec2Int ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	void operator+=(const Vec2Int& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vec2Int& other)
	{
		x += other.x;
		y += other.y;
	}

	float Dot(Vec2 other)
	{
		return x * other.x + y * other.y;
	}

	float Cross(Vec2 other)
	{
		return x * other.y - y * other.x;
	}
};