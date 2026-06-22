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

	// Dummy 생성 및 connect
	for (int i = 0; i < DummyCount; ++i)
	{
		_dummys[i].dummyID = i;
		_dummys[i].playerID = -1;
		_dummys[i].state = DummyState::Title;
		_dummys[i].playerCount = 0;

		// TCP
		{
			// clientSocket 생성
			_dummys[i].socket = socket(AF_INET, SOCK_STREAM, 0);
			if (_dummys[i].socket == INVALID_SOCKET)
				return;

			// connect
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr("192.168.78.46");
			addr.sin_port = htons(PORT);
			if (connect(_dummys[i].socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
				return;
		}
	}
}

GameNetwork::~GameNetwork()
{
	// clientSocket 종료
	for (auto& dummy : _dummys)
		closesocket(dummy.socket);

	// 윈속 종료
	WSACleanup();
}

void GameNetwork::Update()
{
	// socket set 초기화
	FD_ZERO(&_readSet);
 	FD_ZERO(&_writeSet);

	// readSet, writeSet에 clientSocket, udpSocket 등록
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

		// send가 가능할 때마다 true
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
			std::string dummyID = "Dummy" + std::to_string(dummy.dummyID);
			std::vector<char> id(dummyID.size());
			std::memcpy(id.data(), dummyID.c_str(), dummyID.size());
			SendLoginPacket(dummy.dummyID, id);
			break;
		}
		case DummyState::Room:
		{
			if (dummy.dummyID % 4 == 0 && dummy.playerCount == 4)
				SendStartStagePacket(dummy.dummyID);
			break;
		}
		case DummyState::Play:
		{
			Vector pos{ -200, -200, 25};

			// 랜덤 이동
			while (pos.x < -100 || pos.x > 100 || pos.y < -100 || pos.y > 100)
			{
				pos = dummy.pos;

				Dir dir = static_cast<Dir>(rand() % 4);
				switch (dir)
				{
				case Front:
					pos.y -= TileSize;
					break;
				case Right:
					pos.x += TileSize;
					break;
				case Back:
					pos.y += TileSize;
					break;
				case Left:
					pos.x -= TileSize;
					break;
				}
			}

			dummy.pos = pos;
			SendMovePacket(dummy.dummyID, ObjectType::Player, dummy.playerID, dummy.pos, Rotation{ 0, 0, 0 }, ObjectState::MOVE);
			std::cout << "Dummy[" << dummy.dummyID << "] 이동\n";
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

	// Data 추출
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

		unsigned char roomDTOSize;
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
		S_EnterRoomResult_Packet enterRoomResultPacket;
		memcpy(&enterRoomResultPacket, packet.data(), sizeof(S_EnterRoomResult_Packet));
		ProcessEnterRoomResultPacket(dummyID, enterRoomResultPacket);
		break;
	}
	case S_AddPlayer:
	{
		S_AddPlayer_Packet addPlayerPacket;
		memcpy(&addPlayerPacket, packet.data(), sizeof(S_AddPlayer_Packet));
		ProcessAddPlayerPacket(dummyID, addPlayerPacket);
		break;
	}
	case S_StartStage:
	{
		S_StartStage_Packet startStagePacket;
		memcpy(&startStagePacket, packet.data(), sizeof(S_StartStage_Packet));
		ProcessStartStagePacket(dummyID, startStagePacket);
		break;
	}
	case S_EndStage:
	{
		unsigned short packetSize;
		memcpy(&packetSize, packet.data(), sizeof(unsigned short));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned short) + sizeof(PacketID));
		
		S_EndStage_Packet endStagePacket;
		endStagePacket.size = packetSize;
		endStagePacket.packetID = S_EndStage;

		unsigned char stageResultDTOSize;
		memcpy(&stageResultDTOSize, packet.data(), sizeof(unsigned char));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));

		for (int i = 0; i < stageResultDTOSize; ++i)
		{
			StageResultDTO stageResultDTO;

			memcpy(&stageResultDTO.isDead, packet.data(), sizeof(bool));
			packet.erase(packet.begin(), packet.begin() + sizeof(bool));

			char nameSize;
			memcpy(&nameSize, packet.data(), sizeof(unsigned char));
			packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));
			stageResultDTO.name.resize(nameSize);
			memcpy(stageResultDTO.name.data(), packet.data(), sizeof(char) * nameSize);
			packet.erase(packet.begin(), packet.begin() + sizeof(char) * nameSize);
			endStagePacket.stageResult.push_back(stageResultDTO);
		}

		ProcessEndStagePacket(dummyID, endStagePacket);
		break;
	}
	}
}

void GameNetwork::SendLoginPacket(int dummyID, const std::vector<char>& id)
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
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendCreateRoomPacket(int dummyID)
{
	// Packet Data 생성
	C_CreateRoom_Packet packetData{ sizeof(C_CreateRoom_Packet), C_CreateRoom };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_CreateRoom;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendEnterRoomPacket(int dummyID, char roomID)
{
	// Packet Data 생성
	C_EnterRoom_Packet packetData{ sizeof(C_EnterRoom_Packet), C_EnterRoom, roomID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EnterRoom;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(int dummyID, ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 생성
	C_Move_Packet packetData{ sizeof(C_Move_Packet), C_Move, id, pos, rotation, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendStartStagePacket(int dummyID)
{
	// Packet Data 생성
	C_StartStage_Packet packetData{ sizeof(C_StartStage_Packet), C_StartStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_StartStage;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::SendEndStagePacket(int dummyID)
{
	// Packet Data 생성
	C_EndStage_Packet packetData{ sizeof(C_EndStage_Packet), C_EndStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EndStage;
	event->serializedPacketData = serializedPacketData;
	_dummys[dummyID].sendEvents.push_back(event);
}

void GameNetwork::ProcessLoginResultPacket(int dummyID, S_LoginResult_Packet packet)
{
	if (packet.result == LoginResult::Sucess)
	{
		std::cout << "Dummy[" << dummyID << "] 로그인 성공\n";
		_dummys[dummyID].state = DummyState::Lobby;
		_dummys[dummyID].clientID = packet.clientID;
	}
}

void GameNetwork::ProcessCurrentRoomListPacket(int dummyID, S_CurrentRoomList_Packet packet)
{
	// 들어갈 수 있는 방이 없다면 방 생성
	if (dummyID % 4 == 0)
	{
		SendCreateRoomPacket(dummyID);
		std::cout << "Dummy[" << dummyID << "] 방 생성\n";
		return;
	}

	// 들어갈 수 있는 방이 있으면 방 입장
	if(packet.roomList.size() != 0 && dummyID / 4 < packet.roomList.size())
		SendEnterRoomPacket(dummyID, packet.roomList[dummyID / 4].roomID);
}

void GameNetwork::ProcessCreateRoomResultPacket(int dummyID, S_CreateRoomResult_Packet packet)
{
	if (packet.result)
	{
		std::cout << "Dummy[" << dummyID << "] 방 입장 성공\n";
		_dummys[dummyID].state = DummyState::Room;
	}
}

void GameNetwork::ProcessEnterRoomResultPacket(int dummyID, S_EnterRoomResult_Packet packet)
{
	if (packet.result)
	{
		std::cout << "Dummy[" << dummyID << "] 방 입장 성공\n";
		_dummys[dummyID].state = DummyState::Room;
	}
}

void GameNetwork::ProcessAddPlayerPacket(int dummyID, S_AddPlayer_Packet packet)
{
	if (_dummys[dummyID].playerID == -1)
	{
		_dummys[dummyID].playerID = packet.id;
		_dummys[dummyID].pos = packet.pos;
	}

	_dummys[dummyID].playerCount++;
}

void GameNetwork::ProcessStartStagePacket(int dummyID, S_StartStage_Packet packet)
{
	_dummys[dummyID].state = DummyState::Play;
}

void GameNetwork::ProcessEndStagePacket(int dummyID, S_EndStage_Packet packet)
{
	_dummys[dummyID].state = DummyState::Room;
}