#include "pch.h"
#include "Room.h"
#include "Player.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Update()
{

}

void Room::CreatePlayer()
{
	std::shared_ptr<Player> player = std::make_shared<Player>();

	player->SetPos(XMFLOAT3(4.0f, 2.0f, 1.0f));
	player->SetID(_playerID);
	_players[_playerID++] = player;

    SendAddPlayerPacket(player);
}

void Room::SendAddPlayerPacket(std::shared_ptr<Player> player)
{
    // 패킷 본문 작성
    Protocol::AddPlayer pkt;

    pkt.set_id(player->GetID());

    XMFLOAT3 pos = player->GetPos();
    pkt.mutable_pos()->set_x(pos.x);
    pkt.mutable_pos()->set_y(pos.y);
    pkt.mutable_pos()->set_z(pos.z);
        
    SendPakcet(pkt, AddPlayer);
}