#include "pch.h"
#include "ItemStage.h"

ItemStage::ItemStage()
{
}

ItemStage::~ItemStage()
{
}

void ItemStage::LoadFile(const std::wstring& path)
{
	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		ItemStageInfo info;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0:info.id = std::stoi(cell); break;	
			case 1: 
			{
				int32 intAcquiredByKey = std::stoi(cell);
				if (intAcquiredByKey == 0)
					info.acquiredByFKey = false;
				else
					info.acquiredByFKey = true;
				break;
			}
			case 2: info.spawnPos.x = std::stof(cell); break;	
			case 3: info.spawnPos.y = std::stof(cell); break;	
			}
			++column;
		}

		_infos.push_back(info);
	}

	ifs.close();
}