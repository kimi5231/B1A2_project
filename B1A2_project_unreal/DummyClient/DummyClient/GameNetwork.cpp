#include "pch.h"
#include "GameNetwork.h"

GameNetwork::GameNetwork()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "윈속 초기화 실패" << std::endl;
		return;
	}

	// TCP
	{
		// clientSocket 생성
		_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (_clientSocket == INVALID_SOCKET)
			return;

		// connect
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(7777);
		if (connect(_clientSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
			return;
	}
}

GameNetwork::~GameNetwork()
{
	// clientSocket 종료
	closesocket(_clientSocket);

	// 윈속 종료
	WSACleanup();
}

void GameNetwork::Update()
{
	// socket set 초기화
	FD_ZERO(&_readSet);
 	FD_ZERO(&_writeSet);

	// readSet, writeSet에 clientSocket, udpSocket 등록
	FD_SET(_clientSocket, &_readSet);
	FD_SET(_clientSocket, &_writeSet);

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
		return;

	if (FD_ISSET(_clientSocket, &_readSet))
		ProcessRecv();

	// send가 가능할 때마다 true
	if (FD_ISSET(_clientSocket, &_writeSet))
	{
		for (NetworkEventRef event : _sendEvents)
		{
			send(_clientSocket, event->serializedPacketData.data(), event->serializedPacketData.size(), 0);
			event->isComplete = true;
		}

		_sendEvents.erase(std::remove_if(_sendEvents.begin(), _sendEvents.end(),
			[](NetworkEventRef event) {
				return event->isComplete;
			}), _sendEvents.end());
	}
}

void GameNetwork::ProcessRecv()
{
	unsigned short packetSize{};
	recv(_clientSocket, (char*)&packetSize, sizeof(unsigned short), MSG_WAITALL);
	
	std::vector<char> packet(BufSize);
	memcpy(packet.data(), &packetSize, sizeof(unsigned short));
	
	recv(_clientSocket, packet.data() + sizeof(unsigned short), packetSize - sizeof(unsigned short), MSG_WAITALL);
	
	PacketID id;
	memcpy(&id, packet.data() + sizeof(unsigned short), sizeof(PacketID));

	// Data 추출
	switch (id)
	{
	case S_LoginResult:
	{
		S_LoginResult_Packet loginResultPacket;
		memcpy(&loginResultPacket, packet.data(), sizeof(S_LoginResult_Packet));
		ProcessLoginResultPacket(loginResultPacket);
		break;
	}
	/*case S_CurrentRoomList:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(packetSize);
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_CreateRoomResult:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_CreateRoomResult_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_EnterRoomResult:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_EnterRoomResult_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_AddPlayer:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_AddPlayer_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_RemoveObject:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_RemoveObject_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_Move:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_Move_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_StartStage:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_StartStage_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_EndStage:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(packetSize);
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}*/
	}
}

void GameNetwork::SendLoginPacket(const std::vector<char>& id)
{
	// Packet Data 생성
	std::vector<char> idData = SerializeVector(id);
	char packetSize = sizeof(char) + sizeof(PacketID) + idData.size();
	
	std::vector<char> serializedPacketData;
	serializedPacketData.push_back(packetSize);
	serializedPacketData.push_back(C_Login);
	serializedPacketData.insert(serializedPacketData.end(), idData.begin(), idData.end());
	
	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Login;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::SendCreateRoomPacket()
{
	// Packet Data 생성
	C_CreateRoom_Packet packetData{ sizeof(C_CreateRoom_Packet), C_CreateRoom };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_CreateRoom;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::SendEnterRoomPacket(char roomID)
{
	// Packet Data 생성
	C_EnterRoom_Packet packetData{ sizeof(C_EnterRoom_Packet), C_EnterRoom, roomID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EnterRoom;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 생성
	C_Move_Packet packetData{ sizeof(C_Move_Packet), C_Move, id, pos, rotation, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::SendStartStagePacket()
{
	// Packet Data 생성
	C_StartStage_Packet packetData{ sizeof(C_StartStage_Packet), C_StartStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_StartStage;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::SendEndStagePacket()
{
	// Packet Data 생성
	C_EndStage_Packet packetData{ sizeof(C_EndStage_Packet), C_EndStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EndStage;
	event->serializedPacketData = serializedPacketData;
	_sendEvents.push_back(event);
}

void GameNetwork::ProcessLoginResultPacket(S_LoginResult_Packet packet)
{
	if (packet.result == LoginResult::Sucess)
		std::cout << "로그인 성공\n";
}