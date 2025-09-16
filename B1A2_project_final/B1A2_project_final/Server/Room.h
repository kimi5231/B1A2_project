#pragma once

enum
{
	EnterRoom = 1,
	AddPlayer = 3,
};

class Player;

class Room
{
public:
	Room();
	virtual ~Room();

	void Update();

public:
	void CreatePlayer();

public:
	void SendAddPlayerPacket(std::shared_ptr<Player> player);

public:
	template <class ptkType>
	void SendPakcet(ptkType pkt, uint32_t pktID);

public:
	std::vector<SOCKET> _clients;

private:
	std::unordered_map<int, std::shared_ptr<Player>> _players;

	// temp
	int _playerID = 1;
};

template<class ptkType>
inline void Room::SendPakcet(ptkType pkt, uint32_t pktID)
{
    // 패킷 헤더 작성 및 빅엔디안으로 변환
    uint32_t pktSize = pkt.ByteSizeLong();

    std::array<uint32_t, 2> header;
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

    // 모든 클라이언트에게 알림
    for (SOCKET client : _clients)
    {
        int resultCode = ::send(client, sendBuffer.data(), sendBuffer.size(), 0);
        if (resultCode == SOCKET_ERROR)
        {
            // 연결 끊김 처리
        }
    }
}