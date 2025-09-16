#pragma once

enum
{
	EnterRoom = 1,
	AddPlayer = 3,
    AddObject = 4,
};

class Player;

class Room
{
public:
	Room();
	virtual ~Room();

	void Update();

public:
    void EnterRoom(SOCKET client);

    std::shared_ptr<Player> CreatePlayer();

public:
    std::vector<char> MakeAddPlayerSendBuffer(std::shared_ptr<Player> player);
    // 추후 매개변수 수정할 것
    std::vector<char> MakeAddObjectSendBuffer(std::shared_ptr<Player> player);

public:
	template <class ptkType>
    std::vector<char> MakeSendBuffer(ptkType pkt, uint32_t pktID);

public:
	std::vector<SOCKET> _clients;

private:
	std::unordered_map<int, std::shared_ptr<Player>> _players;

	// temp
	int _playerID = 1;
};

template<class ptkType>
inline std::vector<char> Room::MakeSendBuffer(ptkType pkt, uint32_t pktID)
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

    return sendBuffer;
}