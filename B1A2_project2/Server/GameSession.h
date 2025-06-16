#pragma once
#include "Session.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

public:
	GameSessionRef GetSessionRef() { return static_pointer_cast<GameSession>(shared_from_this()); }

public:
	weak_ptr<GameRoom> gameRoom;
	weak_ptr<Player> player;
};
