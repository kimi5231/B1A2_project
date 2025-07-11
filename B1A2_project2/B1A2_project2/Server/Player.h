#pragma once
#include "GameObject.h"
#include "Stat.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	void SetSession(GameSessionRef session) { _session = session; }
	GameSessionRef GetSession() { return _session; }

	void SetPlayerStat(PlayerStat* stat) { _stat = stat; }
	PlayerStat* GetPlayerStat() { return _stat; }

private:
	GameSessionRef _session;
	PlayerStat* _stat;
};