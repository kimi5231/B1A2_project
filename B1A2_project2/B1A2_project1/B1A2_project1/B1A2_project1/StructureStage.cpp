#include "pch.h"
#include "StructureStage.h"

StructureStage::StructureStage()
{
}

StructureStage::~StructureStage()
{
}

void StructureStage::LoadFile(const std::wstring& path)
{
	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		StructureStageInfo info;

		while (std::getline(lineStream, cell, ','))
		{
			std::wstring cellWstr(cell.begin(), cell.end());

			switch (column)
			{
            case 0: info.name = cellWstr; break;
            case 1: info.spawnPos.x = std::stof(cell); break;;
            case 2: info.spawnPos.y = std::stof(cell); break;
            case 3: info.keyPos.x = std::stof(cell); break;
            case 4: info.keyPos.y = std::stof(cell); break;
            case 5: info.wallType = std::stoi(cell); break;
            case 6: info.zipLineType = std::stoi(cell); break;
			case 7: info.zipLineRenderType = std::stoi(cell); break;
            case 8: info.zipLineStartPos.x = std::stof(cell); break;
            case 9: info.zipLineStartPos.y = std::stof(cell); break;
            case 10: info.zipLineEndPos.x = std::stof(cell); break;
            case 11: info.zipLineEndPos.y = std::stof(cell); break;
			case 12: info.zipLineButtonPos.x = std::stof(cell); break;
			case 13: info.zipLineButtonPos.y = std::stof(cell); break;
			case 14: info.zipLineDisplayPos.x = std::stof(cell); break;
			case 15: info.zipLineDisplayPos.y = std::stof(cell); break;
            case 16: info.windowFlickeringCycle = std::stof(cell); break;
            case 17: info.windowFlickeringDuration = std::stof(cell); break;
			}
			++column;
		}

		_infos.push_back(info);
	}

	ifs.close();
}
