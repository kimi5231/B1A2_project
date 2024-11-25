#pragma once
#include "Player.h"		// PlayerStat struct �ʿ��ؼ� ���漱�� ���� include�� 

class PlayerStatManager
{
public:
	DECLARE_SINGLE(PlayerStatManager);

	~PlayerStatManager();

public:
	void Init(HWND hwnd, std::filesystem::path resourcePath);
	void Clear();

	const std::filesystem::path& GetResourcePath() { return _resourcePath; }

	PlayerStat* GetPlayerStat(const int32 playerID) { return _playerStats[playerID]; }		// �̱� �÷��̾� �⺻ ���̵� 1(������ 1�̰�, �÷��̾ �� ����� �ٲٴ� �ڵ� �߰� �ʿ�)
	PlayerStat* LoadPlayerStats(const int32 playerID, const std::wstring& path);

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// PlayerStat
	std::unordered_map<int32, PlayerStat*> _playerStats;		// [PlayerID, PlayerStat]
};

