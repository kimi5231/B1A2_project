#include "pch.h"
#include "Stat.h"
#include <fstream>

Stat::Stat()
{
}

Stat::~Stat()
{
}

void Stat::LoadPlayerStatFile(std::filesystem::path dataPath)
{
	std::filesystem::path path = dataPath / L"playerStat.csv";

	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	Protocol::PlayerStat stat;

	if (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0:stat.set_hp(std::stoi(cell)); break;	// A
			case 1: stat.set_runspeed(std::stof(cell)); break;	// B
			case 2: stat.set_crouchspeed(std::stof(cell)); break;	// C
			case 3: stat.set_jumpspeed(std::stof(cell)); break;	// D
			case 4: stat.set_skillpoint(std::stoi(cell)); break;	// E
			case 5: stat.set_natkrange(std::stoi(cell)); break;	// F
			case 6: stat.set_nlongatkdistance(std::stoi(cell)); break;	// G
			case 7: stat.set_knockbackdistance(std::stoi(cell)); break;	// H
			case 8: stat.set_strongatkmultiplier(std::stof(cell)); break;	// I
			case 9: stat.set_natkdamage(std::stoi(cell)); break;	// J
			case 10: stat.set_skilldamage(std::stoi(cell)); break;	// K
			case 11: stat.set_skillrange(std::stoi(cell)); break;	// L
			case 12: stat.set_skillduration(std::stof(cell)); break;	// M
			case 13: stat.set_skillstepdistance(std::stoi(cell)); break;	// N
			}
			++column;
		}
	}

	ifs.close();

	_playerStat = stat;
}

void Stat::LoadTiredOfficeWorkerStatFile(std::filesystem::path dataPath)
{
	std::filesystem::path path = dataPath / L"tiredOfficeWorkerStat.csv";

	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	Protocol::TiredOfficeWorkerStat stat;

	if (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0: stat.set_hp(std::stoi(cell)); break;	// A
			case 1: stat.set_healtemdroprate(std::stof(cell)); break;	// B
			case 2: stat.set_speed(std::stof(cell)); break;	// C
			case 3: stat.set_chasespeed(std::stof(cell)); break;	// D
			case 4: stat.set_playerdetectionx(std::stoi(cell)); break;	// E
			case 5: stat.set_playerdetectiony(std::stoi(cell)); break;	// F
			case 6: stat.set_knockbackdistance(std::stoi(cell)); break;	// G
			case 7: stat.set_attackrangex(std::stoi(cell)); break;	// H
			case 8: stat.set_attackrangey(std::stoi(cell)); break;	// I
			case 9: stat.set_attack(std::stoi(cell)); break;	// J
			case 10: stat.set_idletime(std::stof(cell)); break;	// K
			}
			++column;
		}
	}
	ifs.close();
}