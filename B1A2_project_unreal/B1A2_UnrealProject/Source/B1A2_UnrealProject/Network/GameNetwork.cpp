#include "GameNetwork.h"

GameNetwork::GameNetwork()
{
	// 扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		//std::cout << "扩加 檬扁拳 角菩" << std::endl;
		return;
	}

	// listenSocket 积己
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == INVALID_SOCKET)
	{
		//std::cout << "listenSocket 积己 角菩" << std::endl;
		return;
	}

	// connect
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//addr.sin_addr.s_addr = inet_addr("61.255.49.141");
	addr.sin_port = htons(7777);
	if (connect(_clientSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		//std::cout << "bind 角菩" << std::endl;
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

	// readSet, writeSet俊 clientSocket 殿废
	FD_SET(_clientSocket, &_readSet);
	FD_SET(_clientSocket, &_writeSet);

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
	{
		//std::cout << "select 角菩" << std::endl;
		return;
	}

	if (FD_ISSET(_clientSocket, &_readSet))
	{
		ProcessRecv();
	}

	// send啊 啊瓷且 锭付促 true
	if (FD_ISSET(_clientSocket, &_writeSet))
	{
		std::lock_guard<std::mutex> lock(_sendMutex);
		for (NetworkEventRef event : _sendEvents)
		{
			ProcessSend(event->packetID, event->serializedPacketData);
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
	// PacketSize 荐脚(绊沥 辨捞)
	int packetSize{};
	if (recv(_clientSocket, (char*)&packetSize, sizeof(int), MSG_WAITALL) <= 0)
	{
		//ProcessDisconnect(client);
		return;
	}

	// Packet 荐脚(啊函 单捞磐)
	std::vector<char> packet(5000);
	if (recv(_clientSocket, packet.data(), packetSize, MSG_WAITALL) <= 0)
	{
		//ProcessDisconnect(client);
		return;
	}

	// Header 眠免
	Header header;
	memcpy(&header, packet.data(), sizeof(Header));

	// Data 眠免
	switch (header.id)
	{
	case S_AddObject:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_AddObject_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_AddObject_Packet));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_AddItem:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_AddItem_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_AddItem_Packet));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_RemoveObject:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_RemoveObject_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_RemoveObject_Packet));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateObjectState:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_UpdateObjectState_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_UpdateObjectState_Packet));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_Move:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_Move_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_Move_Packet));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_CreateCubes:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_AddItemToInventory:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_RemoveItemFromInventory:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_ItemPickupNotify:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_DropItem:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateCurrentTool:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_UseTool:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_SpawnParticle:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_InteractDoorNotify:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_SpawnMonster:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_TurnOnLantern:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_TurnOffLantern:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_StartStage:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	case S_EndStage:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::ProcessSend(PacketID id, const std::vector<char>& packetData)
{
	std::vector<char> packet = CreatePakcet(id, packetData);
	int packetSize = packet.size();

	// packetSize 价脚(绊沥 辨捞)
	send(_clientSocket, (char*)&packetSize, sizeof(int), 0);
	// packet 价脚(啊函 单捞磐)
	send(_clientSocket, packet.data(), packetSize, 0);
}

std::vector<char> GameNetwork::CreatePakcet(PacketID id, const std::vector<char>& packetData)
{
	// Header
	Header header;
	header.id = id;
	header.dataSize = packetData.size();

	// Packet
	std::vector<char> packet(sizeof(Header) + header.dataSize);
	memcpy(packet.data(), &header, sizeof(Header));
	memcpy(packet.data() + sizeof(Header), packetData.data(), header.dataSize);

	return packet;
}

void GameNetwork::SendUpdateObjectStatePacket(int id, ObjectType type, ObjectState state)
{
	// Packet Data 积己
	C_UpdateObjectState_Packet packetData{ id, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UpdateObjectState;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 积己
	C_Move_Packet packetData{ type, id, pos, rotation, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendGetItemPacket(int itemID, bool isTool, int playerID)
{
	// Packet Data 积己
	C_GetItem_Packet packetData{ playerID, isTool, itemID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_GetItem;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendDropItemPacket(int itemID, bool isTool, int playerID)
{
	// Packet Data 积己
	C_DropItem_Packet packetData{ playerID, isTool, itemID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_DropItem;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendChangeToolPacket(int playerID, int toolID)
{
	// Packet Data 积己
	C_ChangeTool_Packet packetData{ playerID, toolID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_ChangeTool;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendUseToolPacket(int playerID, int toolID, Rotation playerRotation)
{
	// Packet Data 积己
	C_UseTool_Packet packetData{ playerID, toolID, playerRotation };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UseTool;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendUseKeyPacket(int playerID, int toolID, int doorID)
{
	// Packet Data 积己
	C_UseTool_Packet packetData{ playerID, toolID, doorID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UseKey;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendInteractDoorPacket(int playerID, int doorID)
{
	// Packet Data 积己
	C_InteractDoor_Packet packetData{ playerID, doorID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_InteractDoor;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendEmotionPacket(float angry, float disgust, float fear, float happy, float sad, float surprise, float neutral)
{
	// Packet Data 积己
	C_Emotion_Packet packetData{ angry, disgust, fear, happy, sad, surprise, neutral };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Emotion;
	event->serializedPacketData = serializedPacketData;

	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendUseLanternPacket(int playerID, int lanternID)
{
	// Packet Data 积己
	C_UseLantern_Packet packetData{ lanternID,  playerID };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UseLantern;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendStartStagePacket()
{
	// Packet Data 积己
	C_StartStage_Packet packetData{ true };

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
	C_EndStage_Packet packetData{ true };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EndStage;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}