#include "pch.h"
#include "Stat.h"

Stat::Stat()
{
}

Stat::~Stat()
{
}

void Stat::LoadPlayerStatFile(std::filesystem::path resourcePath)
{
	std::filesystem::path path = resourcePath / L"Data\\playerStat.csv";

	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	PlayerStat* stat = new PlayerStat();

	if (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0:stat->hp = std::stoi(cell); break;	// A
			case 1: stat->runSpeed = std::stof(cell); break;	// B
			case 2: stat->crouchSpeed = std::stof(cell); break;	// C
			case 3: stat->jumpSpeed = std::stof(cell); break;	// D
			case 4: stat->skillPoint = std::stoi(cell); break;	// E
			case 5: stat->nAtkRange = std::stoi(cell); break;	// F
			case 6: stat->nLongAtkDistance = std::stoi(cell); break;	// G
			case 7: stat->knockBackDistance = std::stoi(cell); break;	// H
			case 8: stat->strongAtkMultiplier = std::stof(cell); break;	// I
			case 9: stat->nAtkDamage = std::stoi(cell); break;	// J
			case 10: stat->skillDamage = std::stoi(cell); break;	// K
			case 11: stat->skillRange = std::stoi(cell); break;	// L
			case 12: stat->skillDuration = std::stof(cell); break;	// M
			case 13: stat->skillStepDistance = std::stoi(cell); break;	// N
			}
			++column;
		}
	}

	_playerStat = stat;

	ifs.close();
}

void Stat::LoadTiredOfficeWorkerStatFile(std::filesystem::path resourcePath)
{
	std::filesystem::path path = resourcePath / L"Data\\TiredOfficeWorkerStat.csv";

	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	TiredOfficeWorkerStat* stat = new TiredOfficeWorkerStat();

	if (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0: stat->hp = std::stoi(cell); break;	// A
			case 1: stat->healtemDropRate = std::stof(cell); break;	// B
			case 2: stat->speed = std::stof(cell); break;	// C
			case 3: stat->chaseSpeed = std::stof(cell); break;	// D
			case 4: stat->playerDetection.x = std::stoi(cell); break;	// E
			case 5: stat->playerDetection.y = std::stoi(cell); break;	// F
			case 6: stat->knockBackDistance = std::stoi(cell); break;	// G
			case 7: stat->attackRange.x = std::stoi(cell); break;	// H
			case 8: stat->attackRange.y = std::stoi(cell); break;	// I
			case 9: stat->attack = std::stoi(cell); break;	// J
			case 10: stat->idleTime = std::stof(cell); break;	// K
			}
			++column;
		}
	}

	_tiredOfficeWorkerStat = stat;

	ifs.close();
}