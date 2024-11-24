#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ValueManager.h"
#include <fstream>
#include <iostream>
#include "Player.h"		// Stat ���� ����
std::vector<PlayerStat> stats;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);	// hwnd�� hdc �� �� �ִ� �Լ�

	// ��� ��� path �˾Ƴ��� �ڵ�
	_resourcePath = std::filesystem::current_path().relative_path();
	std::filesystem::path _resourcePath = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources";
	
	// CSV ���� �о �迭�� �����ϴ� �ڵ�
	stats = LoadPlayerStats(_resourcePath / "DataBase\\TEST_playerData");

	// ���� ���۸� �ڵ�
	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(_hdc);	// hdc�� ȣȯ�Ǵ� DC ����
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC�� BMP ����
	::DeleteObject(prev);

	// �� �Ŵ����� Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, _resourcePath);
	GET_SINGLE(SoundManager)->Init(hwnd);
	GET_SINGLE(ValueManager)->Init(hwnd);

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);

	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdcBack, 550, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // ��Ʈ �� : ��� ����
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}

std::vector<PlayerStat> Game::LoadPlayerStats(const std::filesystem::path& filePath)
{
	// std::vector<PlayerStat> playerStats;

	std::ifstream playerDBFile(filePath);
	if (!playerDBFile.is_open())
	{
		std::cerr << "Failed to poen file : " << filePath << std::endl;
		return stats;
	}

	std::string line;
	while (std::getline(playerDBFile, line))
	{
		if (line.empty())
			continue;

		std::istringstream lineStream(line);
		std::string cell;
		PlayerStat stat;
		int column = 0;

		while (std::getline(lineStream, cell, '\t')) 
		{
			switch (column)
			{
			// stoi : ���ڿ��� ������ ��ȯ
			case 0: stat.healthPoint = std::stoi(cell); break;
			case 1: stat.runSpeed = std::stoi(cell); break;
			case 2: stat.crouchSpeed = std::stoi(cell); break;
			case 3: stat.jumpHeight = std::stoi(cell); break;
			case 4: stat.attRange = std::stoi(cell); break;
			case 5: stat.enemyExistInAttRange = (cell == "1"); break;
			case 6: stat.attID = std::stoi(cell); break;
			case 7: stat.attDamage = std::stoi(cell); break;
			case 8: stat.attStepDistance = std::stoi(cell); break;
			case 9: stat.skillPoint = std::stoi(cell); break;
			case 10: stat.skillDamage = std::stoi(cell); break;
			case 11: stat.skillRange = std::stoi(cell); break;
			case 12: stat.skillDuration = std::stoi(cell); break;
			case 13: stat.skillStepDistance = std::stoi(cell); break;
			}
			++column;
		}

		if (column >= 14) 
			stats.push_back(stat);
	}

	return stats;
}
