#pragma once
class Player
{
public:
	Player();
	virtual ~Player();

	void Update();

public:
	void SetPos(XMFLOAT3 pos) { _pos = pos; }
	void SetID(int id) { _id = id; }

	XMFLOAT3 GetPos() { return _pos; }
	int GetID() { return _id; }

	void SetClient(SOCKET client) { _client = client; }
	SOCKET GetClient() { return _client; }

private:
	XMFLOAT3 _pos{};
	int _id{};
	SOCKET _client{};
};