#pragma once

extern GameRoomRef GRoom;

class GameRoom : public std::enable_shared_from_this<GameRoom>
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
	GameObjectRef FindObject(int32 id);

public:
	void Handle_C_Move(Protocol::C_Move& pkt);

public:
	GameRoomRef GetRoomRef() {return std::static_pointer_cast<GameRoom>(shared_from_this());}

private:
	std::map<uint64, PlayerRef> _players;
	std::map<uint64, MonsterRef> _monsters;
};