#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	void SetSession(GameSessionRef session) { _session = session; }
	GameSessionRef GetSession() { return _session; }

	void SetPlayerStat(Protocol::PlayerStat& stat) { _stat = stat; }
	Protocol::PlayerStat& GetPlayerStat() { return _stat; }

private:
	GameSessionRef _session;
	Protocol::PlayerStat _stat;
};