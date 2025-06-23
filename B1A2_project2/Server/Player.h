#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	void SetStat(Protocol::PlayerStat stat) { _stat = stat; }
	Protocol::PlayerStat GetStat() { return _stat; }

	void SetSession(GameSessionRef session) { _session = session; }
	GameSessionRef GetSession() { return _session; }

private:
	Protocol::PlayerStat _stat;
	GameSessionRef _session;
};