#include "pch.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::LoadFile(const std::wstring& path)
{
	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		StageInfo info;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0:info.id = std::stoi(cell); break;	// A
			case 1: info.dir = static_cast<Dir>(std::stoi(cell)); break;	// B
			case 2: info.spawnPos.x = std::stof(cell); break;	// C
			case 3: info.spawnPos.y = std::stof(cell); break;	// D
			case 4: info.movingDistance = std::stof(cell); break;	// E
			case 5: info.movementLimit.x = std::stof(cell); break;	// F
			case 6: info.movementLimit.y = std::stof(cell); break;	// G
			}
			++column;
		}

		_infos.push_back(info);
	}

	ifs.close();
}