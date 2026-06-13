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

	// TCP
	{
		// clientSocket 积己
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
	// clientSocket 辆丰
	closesocket(_clientSocket);

	// 扩加 辆丰
	WSACleanup();
}

void GameNetwork::Update()
{
	// socket set 檬扁拳
	FD_ZERO(&_readSet);
 	FD_ZERO(&_writeSet);

	// readSet, writeSet俊 clientSocket, udpSocket 殿废
	FD_SET(_clientSocket, &_readSet);
	FD_SET(_clientSocket, &_writeSet);

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
		return;

	if (FD_ISSET(_clientSocket, &_readSet))
		ProcessRecv();

	// send啊 啊瓷且 锭付促 true
	if (FD_ISSET(_clientSocket, &_writeSet))
	{
		std::lock_guard<std::mutex> lock(_sendMutex);
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

	// 贸府等 Recv 捞亥飘 昏力
	std::lock_guard<std::mutex> lock(_recvMutex);
	_recvEvents.erase(std::remove_if(_recvEvents.begin(), _recvEvents.end(),
		[](NetworkEventRef event) {
			return event->isComplete;
		}), _recvEvents.end());
}

void GameNetwork::ProcessRecv()
{
	unsigned short packetSize{};
	recv(_clientSocket, (char*)&packetSize, sizeof(unsigned short), MSG_WAITALL);
	std::vector<char> packet(BufferSize);
	recv(_clientSocket, packet.data(), packetSize - sizeof(unsigned short), MSG_WAITALL);
	
	PacketID id;
	memcpy(&id, packet.data(), sizeof(PacketID));

	// Data 眠免
	switch (id)
	{
	case S_SignupResult:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_SignupResult_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_LoginResult:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_LoginResult_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_CurrentRoomList:
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
	case S_AddMonster:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_AddMonster_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_AddItem:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_AddItem_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_AddObstacle:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_AddObstacle_Packet));
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
	case S_UpdateObjectState:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateObjectState_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_CreateCubes:
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
	case S_AddItemToInventory:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_AddItemToInventory_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_RemoveItemFromInventory:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_RemoveItemFromInventory_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_ItemPickupNotify:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_ItemPickupNotify_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_DropItem:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_DropItem_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateCurrentTool:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateCurrentTool_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UseTool:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UseTool_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_TurnOnLantern:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_TurnOnLantern_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_TurnOffLantern:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_TurnOffLantern_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_InteractDoorNotify:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_InteractDoorNotify_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_SellItemResult:
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
	case S_BuyItemResult:
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
	case S_UpdateHp:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateHp_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_EmotionGameResult:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_EmotionGameResult_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_SpawnParticle:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_SpawnParticle_Packet));
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
	}
	case S_GameOver:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_GameOver_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateQuest:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateQuest_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateQuestProgress:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateQuestProgress_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateCredit:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateCredit_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::SendLoginPacket(const std::vector<char>& id)
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
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendCreateRoomPacket()
{
	// Packet Data 积己
	C_CreateRoom_Packet packetData{ sizeof(C_CreateRoom_Packet), C_CreateRoom };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_CreateRoom;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendEnterRoomPacket(char roomID)
{
	// Packet Data 积己
	C_EnterRoom_Packet packetData{ sizeof(C_EnterRoom_Packet), C_EnterRoom, roomID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EnterRoom;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 积己
	C_Move_Packet packetData{ sizeof(C_Move_Packet), C_Move, id, pos, rotation, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendStartStagePacket()
{
	// Packet Data 积己
	C_StartStage_Packet packetData{ sizeof(C_StartStage_Packet), C_StartStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_StartStage;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendEndStagePacket()
{
	// Packet Data 积己
	C_EndStage_Packet packetData{ sizeof(C_EndStage_Packet), C_EndStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EndStage;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}
