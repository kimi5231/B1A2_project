#include "pch.h"
#include "Stat.h"

void Stat::LoadFile(std::filesystem::path dataPath)
{
	// �ʿ��� Stat ���� Load

	// Player Stat
	{
		std::filesystem::path path = dataPath / L"playerStat.csv";

		PlayerStat* playerStat = new PlayerStat();
		playerStat->LoadFile(path);

		_playerStat = playerStat;
	}
}