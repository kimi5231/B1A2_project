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
    player->SetClient(client);

    // 접속한 client에게 보낼 것
    std::vector<char> sendBuffer1 = MakeAddPlayerSendBuffer(player);
    // 기존에 있던 client에게 보낼 것
    std::vector<char> sendBuffer2 = MakeAddObjectSendBuffer(player);

    // 접속한 client에게 생성된 player 및 기존 client 정보 전송
    send(client, sendBuffer1.data(), sendBuffer1.size(), 0);
    for (auto player : _players)
    {
        if (player.second->GetClient() != client)
        {
            std::vector<char> sendBuffer = MakeAddObjectSendBuffer(player.second);
            send(client, sendBuffer.data(), sendBuffer.size(), 0);
        }
    }

    // 기존에 있던 client에게 입장한 player 정보 전송
    for (auto _client : _clients)
    {
        if(_client != client)
            send(_client, sendBuffer2.data(), sendBuffer2.size(), 0);
    }
}

void Room::CheckMove(Protocol::Move pkt)
{
    std::shared_ptr<Player> player = _players[pkt.id()];

    bool canMove = false;
    
    // 가능한 이동인지 판단(임시. 추후 속력으로 판단하기)
    if (std::abs(player->GetPos().x - pkt.pos().x()) < 100)
        canMove = true;
    if (std::abs(player->GetPos().y - pkt.pos().y()) < 100)
        canMove = true;
    if (std::abs(player->GetPos().z - pkt.pos().z()) < 100)
        canMove = true;
    
    if (canMove)
        player->SetPos(XMFLOAT3(pkt.pos().x(), pkt.pos().y(), pkt.pos().z()));

    std::vector<char> sendBuffer = MakeMoveSendBuffer(player, canMove);

    // 모든 client에게 Move 결과 전송
    for (auto client : _clients)
    {
        send(client, sendBuffer.data(), sendBuffer.size(), 0);
    }
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

std::vector<char> Room::MakeMoveSendBuffer(std::shared_ptr<Player> player, bool canMove)
{
    // 패킷 본문 작성
    Protocol::Move pkt;

    pkt.set_id(player->GetID());

    XMFLOAT3 pos = player->GetPos();
    pkt.mutable_pos()->set_x(pos.x);
    pkt.mutable_pos()->set_y(pos.y);
    pkt.mutable_pos()->set_z(pos.z);

    pkt.set_canmove(canMove);

    return MakeSendBuffer(pkt, Move);
}