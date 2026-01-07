#pragma once
#include "Includes.h"

class GameNetwork
{
public:
	GameNetwork();
	~GameNetwork();

public:
	void Update();
	void ProcessRecv();

	template <class T>
	void ProcessSend(PacketID id, const T& packetData);

	template <class T>
	std::vector<char> CreatePacket(PacketID id, const T& packetData);

public:
	void SendMovePacket(int id, Vector pos, Rotation rotation);

public:
	std::vector<RecvEventType>& GetRecvEvents() { return _recvEvents; }

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _clientSocket{};

	std::vector<RecvEventType> _recvEvents;
	std::vector<SendEventType> _sendEvents;

	
};

template<class T>
inline void GameNetwork::ProcessSend(PacketID id, const T& packetData)
{
	std::vector<char> packet = CreatePacket(id, packetData);
	int packetSize = packet.size();

	// packetSize 송신(고정 길이)
	send(_clientSocket, (char*)&packetSize, sizeof(int), 0);
	// packet 송신(가변 데이터)
	send(_clientSocket, packet.data(), packetSize, 0);
}

template<class T>
inline std::vector<char> GameNetwork::CreatePacket(PacketID id, const T& packetData)
{
	// Header
	Header header;
	header.id = id;
	header.dataSize = sizeof(packetData);

	// Packet
	std::vector<char> packet(sizeof(Header) + header.dataSize);
	memcpy(packet.data(), &header, sizeof(Header));
	memcpy(packet.data() + sizeof(Header), &packetData, header.dataSize);

	return packet;
}