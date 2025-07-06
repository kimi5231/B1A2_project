#pragma once

struct FieldMonster
{
	int32 id;	// A
	Protocol::DIR_TYPE dir;	// B
	float spawnPosX;	// C
	float spawnPosY;	// D
	float movingDistance;	// E
	float movementLimitX;	// F
	float movementLimitY;	// G
};

class Stage
{
public:
	Stage();
	virtual ~Stage();

public:
	void LoadFieldMonster(std::filesystem::path dataPath, const std::wstring fileName);

public:
	std::vector<FieldMonster>& GetFieldMonsters() { return _fieldMonsters; }

private:
	std::vector<FieldMonster> _fieldMonsters;
};
