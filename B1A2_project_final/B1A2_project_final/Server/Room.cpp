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

void Room::EnterRoom(SOCKET client)
{
    std::shared_ptr<Player> player = CreatePlayer();

    // 접속한 client에게 보낼 것
    std::vector<char> sendBuffer1 = MakeAddPlayerSendBuffer(player);
    // 기존에 있던 client에게 보낼 것
    std::vector<char> sendBuffer2 = MakeAddObjectSendBuffer(player);

    // 접속한 client에게 생성된 player 전송
    send(client, sendBuffer1.data(), sendBuffer1.size(), 0);

    // 기존에 있던 client에게 입장한 player 정보 전송
    for (auto _client : _clients)
    {
        send(_client, sendBuffer2.data(), sendBuffer2.size(), 0);
    }

    _clients.push_back(client);
}

std::shared_ptr<Player> Room::CreatePlayer()
{
	std::shared_ptr<Player> player = std::make_shared<Player>();

	player->SetPos(XMFLOAT3(4.0f, 2.0f, 1.0f));
	player->SetID(_playerID);
	_players[_playerID++] = player;

    return player;
}

std::vector<char> Room::MakeAddPlayerSendBuffer(std::shared_ptr<Player> player)
{
    // 패킷 본문 작성
    Protocol::AddPlayer pkt;

    pkt.set_id(player->GetID());

    XMFLOAT3 pos = player->GetPos();
    pkt.mutable_pos()->set_x(pos.x);
    pkt.mutable_pos()->set_y(pos.y);
    pkt.mutable_pos()->set_z(pos.z);
       
    return MakeSendBuffer(pkt, AddPlayer);
}

std::vector<char> Room::MakeAddObjectSendBuffer(std::shared_ptr<Player> player)
{
    // 패킷 본문 작성
    Protocol::AddObject pkt;

    pkt.set_id(player->GetID());

    XMFLOAT3 pos = player->GetPos();
    pkt.mutable_pos()->set_x(pos.x);
    pkt.mutable_pos()->set_y(pos.y);
    pkt.mutable_pos()->set_z(pos.z);

    return MakeSendBuffer(pkt, AddObject);
}