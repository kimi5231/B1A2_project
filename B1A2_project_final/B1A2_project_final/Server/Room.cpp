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

void Room::AddPlayer()
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
        
    uint32_t pktSize = pkt.ByteSizeLong();
    uint32_t pktID = Add_Player;

    // 패킷 헤더 작성 및 빅엔디안으로 변환
    std::array<uint32_t, 2> header;
    // 빅엔디안으로 변환
    header[0] = ::htonl(pktSize);
    header[1] = ::htonl(pktID);

    // sendBuffer 생성
    std::vector<char> sendBuffer(sizeof(header) + pktSize);
    // sendBuffer에 패킷 헤더 추가
    std::memcpy(sendBuffer.data(), &header, sizeof(header));
    // sendBuffer에 패킷 본문 추가
    // Protobuf 객체를 Byte 배열(sendBuffer)로 변환
    // 이 과정에서 숫자형 필드도 빅엔디안으로 변환
    pkt.SerializeToArray(sendBuffer.data() + sizeof(header), pktSize);

    for (SOCKET client : _clients)
    {
        int resultCode = ::send(client, sendBuffer.data(), sendBuffer.size(), 0);
        if (resultCode == SOCKET_ERROR)
        {
            // 연결 끊김 처리
        }
    }
}