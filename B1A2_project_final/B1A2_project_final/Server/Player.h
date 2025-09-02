#pragma once
class Player
{
public:
	Player();
	virtual ~Player();

	void Update();

private:
	DirectX::XMFLOAT3 _pos{};
};