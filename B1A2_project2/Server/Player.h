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

private:
	GameSessionRef _session;
};