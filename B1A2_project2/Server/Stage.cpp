#include "pch.h"
#include "Stage.h"
#include <fstream>

Stage::Stage()
{

}

Stage::~Stage()
{

}


void Stage::LoadFieldMonster(std::filesystem::path dataPath, const std::wstring fileName)
{
	std::filesystem::path path = dataPath / fileName;

	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		FieldMonster fieldMonster;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0:fieldMonster.id = std::stoi(cell); break;	// A
			case 1: fieldMonster.dir = static_cast<Protocol::DIR_TYPE>(std::stoi(cell)); break;	// B
			case 2: fieldMonster.spawnPosX = std::stof(cell); break;	// C
			case 3: fieldMonster.spawnPosY = std::stof(cell); break;	// D
			case 4: fieldMonster.movingDistance = std::stof(cell); break;	// E
			case 5: fieldMonster.movementLimitX = std::stof(cell); break;	// F
			case 6: fieldMonster.movementLimitY = std::stof(cell); break;	// G
			}
			++column;
		}

		_fieldMonsters.push_back(fieldMonster);
	}

	ifs.close();
}