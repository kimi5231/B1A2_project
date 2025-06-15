#pragma once
#include <fstream>

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

	void LoadFile(const std::wstring& path)
	{
		std::ifstream ifs;
		ifs.open(path);

		std::string line;

		if (std::getline(ifs, line))
		{
			std::istringstream lineStream(line);
			std::string cell;
			int column = 0;

			while (std::getline(lineStream, cell, ','))
			{
				switch (column)
				{
				case 0:this->hp = std::stoi(cell); break;	// A
				case 1: this->runSpeed = std::stof(cell); break;	// B
				case 2: this->crouchSpeed = std::stof(cell); break;	// C
				case 3: this->jumpSpeed = std::stof(cell); break;	// D
				case 4: this->skillPoint = std::stoi(cell); break;	// E
				case 5: this->nAtkRange = std::stoi(cell); break;	// F
				case 6: this->nLongAtkDistance = std::stoi(cell); break;	// G
				case 7: this->knockBackDistance = std::stoi(cell); break;	// H
				case 8: this->strongAtkMultiplier = std::stof(cell); break;	// I
				case 9: this->nAtkDamage = std::stoi(cell); break;	// J
				case 10: this->skillDamage = std::stoi(cell); break;	// K
				case 11: this->skillRange = std::stoi(cell); break;	// L
				case 12: this->skillDuration = std::stof(cell); break;	// M
				case 13: this->skillStepDistance = std::stoi(cell); break;	// N
				}
				++column;
			}
		}
		ifs.close();
	}
};

class Stat
{
public:
	void LoadFile(std::filesystem::path dataPath);

private:
	PlayerStat* _playerStat;
};