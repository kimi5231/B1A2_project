#pragma once

extern GameRoomRef GRoom;

class GameRoom : public enable_shared_from_this<GameRoom>
{
public:
	GameRoom();
	virtual ~GameRoom();

	void Init();
	void Update();

public:
	void EnterRoom(GameSessionRef session);
	void LeaveRoom(GameSessionRef session);

public:
	void AddObject(GameObjectRef object);
	void RemoveObject(GameObjectRef object);
	void Broadcast(SendBufferRef& sendBuffer);

public:
	GameRoomRef GetRoomRef() {return static_pointer_cast<GameRoom>(shared_from_this());}

private:
	std::map<uint64, PlayerRef> _players;
};