#pragma once

struct PlayerStat
{
	int32 hp = 0; // A
	float runSpeed = 0;	// B
	float crouchSpeed = 0;	// C
	float jumpSpeed = 0;	// D
	int32 skillPoint = 0;	// E
	int32 nAtkRange = 0;	// F
	int32 nLongAtkDistance = 0;	// G
	int32 knockBackDistance = 0;	// H
	float strongAtkMultiplier = 0.f;	// I
	int32 nAtkDamage = 0;	// J
	int32 skillDamage = 0;	// K
	int32 skillRange = 0;	// L
	float skillDuration = 0;	// M
	int32 skillStepDistance = 0;	// N
};

struct TiredOfficeWorkerStat
{
	int32 hp;	// A
	float healtemDropRate;	// B
	float speed;	// B
	float chaseSpeed;	// D
	Vec2Int playerDetection;	// E, F
	int32 knockBackDistance; // G
	Vec2Int attackRange;	// H, I
	int32 attack;	// J
	float idleTime;	// K
};

class Stat
{
public:
	Stat();
	virtual ~Stat();

public:
	void LoadPlayerStatFile(std::filesystem::path resourcePath);
	void LoadTiredOfficeWorkerStatFile(std::filesystem::path resourcePath);

public:
	PlayerStat* GetPlayerStat() { return _playerStat; }
	TiredOfficeWorkerStat* GetTiredOfficeWorkerStat() { return _tiredOfficeWorkerStat; }

private:
	PlayerStat* _playerStat;
	TiredOfficeWorkerStat* _tiredOfficeWorkerStat;
};