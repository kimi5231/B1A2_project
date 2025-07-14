#pragma once

struct FieldMonster
{
	int32 id;	// A
	Protocol::DIR_TYPE dir;	// B
	Vec2 spawnPos;		// C, D
	float movingDistance;	// E
	Vec2 movementLimit;	// F, G
};

class Stage
{
public:
	Stage();
	virtual ~Stage();

public:
	void LoadFieldMonster(std::filesystem::path dataPath, const std::wstring fileName);
	std::vector<FieldMonster>& GetFieldMonsters() { return _fieldMonsters; }

private:
	std::vector<FieldMonster> _fieldMonsters;
};
