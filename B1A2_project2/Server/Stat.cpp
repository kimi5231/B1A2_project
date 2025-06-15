#include "pch.h"
#include "Stat.h"

void Stat::LoadFile(std::filesystem::path dataPath)
{
	// 필요한 Stat 전부 Load

	// Player Stat
	{
		std::filesystem::path path = dataPath / L"playerStat.csv";

		PlayerStat* playerStat = new PlayerStat();
		playerStat->LoadFile(path);

		_playerStat = playerStat;
	}
}