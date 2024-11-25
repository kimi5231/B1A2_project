#include "pch.h"
#include "PlayerStatManager.h"
#include <fstream>

PlayerStatManager::~PlayerStatManager()
{
	Clear();
}

void PlayerStatManager::Init(HWND hwnd, std::filesystem::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void PlayerStatManager::Clear()
{

}

PlayerStat* PlayerStatManager::LoadPlayerStats(const int32 playerID, const std::wstring& path)
{	
	std::filesystem::path fullpath = _resourcePath / path;

	std::ifstream playerDBFile(fullpath);
	if (!playerDBFile.is_open())
		return _playerStats[playerID];

	std::string line;
	int currentID = 0; // ���� �а� �ִ� �÷��̾� ID

	while (std::getline(playerDBFile, line))
	{
		if (line.empty())
			continue;

		std::istringstream lineStream(line);
		std::string cell;
		PlayerStat* stat = new PlayerStat();
		int column = 0;

		while (std::getline(lineStream, cell, '\t'))
		{
			switch (column)
			{
			// stoi : ���ڿ��� ������ ��ȯ
			case 0: stat->playerID = currentID++; break;
			case 1: stat->healthPoint = std::stoi(cell); break;
			case 2: stat->runSpeed = std::stoi(cell); break;
			case 3: stat->crouchSpeed = std::stoi(cell); break;
			case 4: stat->jumpHeight = std::stoi(cell); break;
			case 5: stat->attRange = std::stoi(cell); break;
			case 6: stat->enemyExistInAttRange = (cell == "1"); break;
			case 7: stat->attID = std::stoi(cell); break;
			case 8: stat->attDamage = std::stoi(cell); break;
			case 9: stat->attStepDistance = std::stoi(cell); break;
			case 10: stat->skillPoint = std::stoi(cell); break;
			case 11: stat->skillDamage = std::stoi(cell); break;
			case 12: stat->skillRange = std::stoi(cell); break;
			case 13: stat->skillDuration = std::stoi(cell); break;
			case 14: stat->skillStepDistance = std::stoi(cell); break;
			}
			++column;
		}
		_playerStats[playerID] = stat;
		return stat;
	}
}
