#include "pch.h"
#include "GameNetwork.h"

GameNetwork::GameNetwork()
{
	// 扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "扩加 檬扁拳 角菩" << std::endl;
		return;
	}

	// Dummy 积己 棺 connect
	for (int i = 0; i < DummyCount; ++i)
	{
		_dummys[i].dummyID = i;
		_dummys[i].state = DummyState::Title;

		// TCP
		{
			// clientSocket 积己
			_dummys[i].socket = socket(AF_INET, SOCK_STREAM, 0);
			if (_dummys[i].socket == INVALID_SOCKET)
				return;

			// connect
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			addr.sin_port = htons(7777);
			if (connect(_dummys[i].socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
				return;
		}
	}
}

GameNetwork::~GameNetwork()
{
	// clientSocket 辆丰
	for (auto& dummy : _dummys)
		closesocket(dummy.socket);

	// 扩加 辆丰
	WSACleanup();
}

void GameNetwork::Update()
{
	// socket set 檬扁拳
	FD_ZERO(&_readSet);
 	FD_ZERO(&_writeSet);

	// readSet, writeSet俊 clientSocket, udpSocket 殿废
	for (auto& dummy : _dummys)
	{
		FD_SET(dummy.socket, &_readSet);
		FD_SET(dummy.socket, &_writeSet);
	}

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
		return;

	for (auto& dummy : _dummys)
	{
		if (FD_ISSET(dummy.socket, &_readSet))
			ProcessRecv(dummy.dummyID);

		// send啊 啊瓷且 锭付促 true
		if (FD_ISSET(dummy.socket, &_writeSet))
		{
			for (NetworkEventRef event : dummy.sendEvents)
			{
				send(dummy.socket, event->serializedPacketData.data(), event->serializedPacketData.size(), 0);
				event->isComplete = true;
			}

			dummy.sendEvents.erase(std::remove_if(dummy.sendEvents.begin(), dummy.sendEvents.end(),
				[](NetworkEventRef event) {
					return event->isComplete;
				}), dummy.sendEvents.end());
		}
	}
}

void GameNetwork::UpdateDummy()
{
	for (auto& dummy : _dummys)
	{
		switch (dummy.state)
		{
		case DummyState::Title:
		{
			std::string dummyName = "Dummy_" + std::to_string(dummy.dummyID);
			std::vector<char> id(dummyName.size());
			std::memcpy(id.data(), dummyName.c_str(), dummyName.size());
			SendLoginPacket(dummy.dummyID, id);
			break;
		}
		}
	}
}

void GameNetwork::ProcessRecv(int dummyID)
{
	unsigned short packetSize{};
	recv(_dummys[dummyID].socket, (char*)&packetSize, sizeof(unsigned short), MSG_WAITALL);
	
	std::vector<char> packet(BufSize);
	memcpy(packet.data(), &packetSize, sizeof(unsigned short));
	
	recv(_dummys[dummyID].socket, packet.data() + sizeof(unsigned short), packetSize - sizeof(unsigned short), MSG_WAITALL);
	
	PacketID id;
	memcpy(&id, packet.data() + sizeof(unsigned short), sizeof(PacketID));

	// Data 眠免
	switch (id)
	{
	case S_LoginResult:
	{
		S_LoginResult_Packet loginResultPacket;
		memcpy(&loginResultPacket, packet.data(), sizeof(S_LoginResult_Packet));
		ProcessLoginResultPacket(dummyID, loginResultPacket);
		break;
	}
	case S_CurrentRoomList:
	{
		unsigned short packetSize;
		memcpy(&packetSize, packet.data(), sizeof(unsigned short));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned short) + sizeof(PacketID));
		
		S_CurrentRoomList_Packet currentRoomListPacket;
		currentRoomListPacket.size = packetSize;
		currentRoomListPacket.packetID = S_CurrentRoomList;

		char roomDTOSize;
		memcpy(&roomDTOSize, packet.data(), sizeof(unsigned char));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));

		for (int i = 0; i < roomDTOSize; ++i)
		{
			RoomDTO roomDTO;

			memcpy(&roomDTO.playerCount, packet.data(), sizeof(unsigned char));
			packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));
			memcpy(&roomDTO.roomID, packet.data(), sizeof(unsigned char));
			packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));
			memcpy(&roomDTO.roomState, packet.data(), sizeof(RoomState));
			packet.erase(packet.begin(), packet.begin() + sizeof(RoomState));

			int roomTitleSize;
			memcpy(&roomTitleSize, packet.data(), sizeof(int));
			packet.erase(packet.begin(), packet.begin() + sizeof(int));
			roomDTO.roomTitle.resize(roomTitleSize);
			memcpy(roomDTO.roomTitle.data(), packet.data(), sizeof(char) * roomTitleSize);
			packet.erase(packet.begin(), packet.begin() + sizeof(char) * roomTitleSize);
			currentRoomListPacket.roomList.push_back(roomDTO);
		}

		ProcessCurrentRoomListPacket(dummyID, currentRoomListPacket);
		break;
	}
	case S_CreateRoomResult:
	{
		S_CreateRoomResult_Packet createRoomResultPacket;
		memcpy(&createRoomResultPacket, packet.data(), sizeof(S_CreateRoomResult_Packet));
		ProcessCreateRoomResultPacket(dummyID, createRoomResultPacket);
		break;
	}
	case S_EnterRoomResult:
	{
		
		break;
	}
	case S_AddPlayer:
	{
		
		break;
	}
	case S_RemoveObject:
	{
		
		break;
	}
	case S_Move:
	{
		
		break;
	}
	case S_StartStage:
	{
		
		break;
	}
	case S_EndStage:
	{
		
		break;
	}
	}
}

void GameNetwork::SendLoginPacket(int dummyID, const std::vector<char>& id)
{
	// Packet Data 积己
	std::vector<char> idData = SerializeVector(id);
	char packetSize = sizeof(char) + sizeof(PacketID) + idData.size();
	
	std::vector<char> serializedPacketData;
	serializedPacketData.push_back(packetSize);
	serializedPacketData.push_back(C_Login);
	serializedPacketData.insert(serializedPacketData.end(), idData.begin(), idData.end());
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Login;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendCreateRoomPacket(int dummyID)
{
	// Packet Data 积己
	C_CreateRoom_Packet packetData{ sizeof(C_CreateRoom_Packet), C_CreateRoom };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_CreateRoom;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendEnterRoomPacket(int dummyID, char roomID)
{
	// Packet Data 积己
	C_EnterRoom_Packet packetData{ sizeof(C_EnterRoom_Packet), C_EnterRoom, roomID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EnterRoom;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(int dummyID, ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 积己
	C_Move_Packet packetData{ sizeof(C_Move_Packet), C_Move, id, pos, rotation, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendStartStagePacket(int dummyID)
{
	// Packet Data 积己
	C_StartStage_Packet packetData{ sizeof(C_StartStage_Packet), C_StartStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_StartStage;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendEndStagePacket(int dummyID)
{
	// Packet Data 积己
	C_EndStage_Packet packetData{ sizeof(C_EndStage_Packet), C_EndStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EndStage;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::ProcessLoginResultPacket(int dummyID, S_LoginResult_Packet packet)
{
	if (packet.result == LoginResult::Sucess)
	{
		std::cout << "肺弊牢 己傍\n";
		_dummys[dummyID].state = DummyState::Lobby;
	}
}

void GameNetwork::ProcessCurrentRoomListPacket(int dummyID, S_CurrentRoomList_Packet packet)
{

}

void GameNetwork::ProcessCreateRoomResultPacket(int dummyID, S_CreateRoomResult_Packet packet)
{
}
