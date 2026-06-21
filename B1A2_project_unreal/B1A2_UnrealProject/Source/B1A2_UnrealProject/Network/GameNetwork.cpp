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
		//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_addr.s_addr = inet_addr("61.255.49.141");
		addr.sin_port = htons(7777);
		if (connect(_clientSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
			return;
	}
	
	// UDP
	{
		// udpSocket 积己
		_udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (_udpSocket == INVALID_SOCKET)
			return;

		memset(&_serverAddr, 0, sizeof(_serverAddr));
		_serverAddr.sin_family = AF_INET;
		_serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		//_serverAddr.sin_addr.s_addr = inet_addr("61.255.49.141");
		_serverAddr.sin_port = htons(7777);
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
	FD_SET(_udpSocket, &_readSet);
	FD_SET(_udpSocket, &_writeSet);

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
		return;

	if (FD_ISSET(_clientSocket, &_readSet))
		ProcessRecv();

	if (FD_ISSET(_udpSocket, &_readSet))
		ProcessUDPRecv();

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

	if (FD_ISSET(_udpSocket, &_writeSet))
	{
		std::lock_guard<std::mutex> lock(_udpSendMutex);
		for (NetworkEventRef event : _unpSendEvents)
		{
			sendto(_udpSocket, event->serializedPacketData.data(), event->serializedPacketData.size(), 0, (sockaddr*)&_serverAddr, sizeof(_serverAddr));
			event->isComplete = true;
		}

		_unpSendEvents.erase(std::remove_if(_unpSendEvents.begin(), _unpSendEvents.end(),
			[](NetworkEventRef event) {
				return event->isComplete;
			}), _unpSendEvents.end());
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
	// 唱吝俊 犁炼赋窍扁
	unsigned short packetSize{};
	recv(_clientSocket, (char*)&packetSize, sizeof(unsigned short), MSG_WAITALL);
	std::vector<char> packet(BufSize);
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
	case S_UpdateTimer:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(sizeof(S_UpdateTimer_Packet));
		memcpy(event->serializedPacketData.data(), &packetSize, sizeof(unsigned short));
		memcpy(event->serializedPacketData.data() + sizeof(unsigned short), packet.data(), packetSize - sizeof(unsigned short));
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::ProcessUDPRecv()
{
	int addrLen = sizeof(_serverAddr);
	std::vector<char> packet(BufSize);
	int recvBytes = recvfrom(_udpSocket, packet.data(), packet.size(), 0, (sockaddr*)&_serverAddr, &addrLen);

	if (recvBytes < sizeof(short) + sizeof(PacketID))
		return;

	// packetSize 眠免
	short packetSize;
	memcpy(&packetSize, packet.data(), sizeof(short));

	// 巢篮 单捞磐狼 荤捞令啊 菩哦狼 荤捞令焊促 累栏搁 吝窜
	if (packetSize > recvBytes)
		return;

	// packetID 眠免
	PacketID id;
	memcpy(&id, packet.data() + sizeof(short), sizeof(PacketID));
	
	// Data 眠免
	switch (id)
	{
	case S_VoiceData:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = id;
		event->serializedPacketData.resize(packetSize);
		memcpy(event->serializedPacketData.data(), packet.data(), packetSize);
		std::lock_guard<std::mutex> lock(_recvMutex);
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::SendSignupPacket(const std::vector<char>& id)
{
	// Packet Data 积己
	std::vector<char> idData = SerializeVector(id);
	char packetSize = sizeof(char) + sizeof(PacketID) + idData.size();

	std::vector<char> serializedPacketData;
	serializedPacketData.push_back(packetSize);
	serializedPacketData.push_back(C_Signup);
	serializedPacketData.insert(serializedPacketData.end(), idData.begin(), idData.end());

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Signup;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
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

void GameNetwork::SendLogoutPacket()
{
	// Packet Data 积己
	C_Logout_Packet packetData{ sizeof(C_Logout_Packet), C_Logout };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Logout;
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

void GameNetwork::SendExitRoomPacket()
{
	// Packet Data 积己
	C_ExitRoom_Packet packetData{ sizeof(C_ExitRoom_Packet), C_ExitRoom };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_ExitRoom;
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

void GameNetwork::SendUpdateObjectStatePacket(int id, ObjectType type, ObjectState state)
{
	// Packet Data 积己
	C_UpdateObjectState_Packet packetData{ sizeof(C_UpdateObjectState_Packet), C_UpdateObjectState, id, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UpdateObjectState;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendGetItemPacket(int itemID, bool isTool, int playerID)
{
	// Packet Data 积己
	C_GetItem_Packet packetData{ sizeof(C_GetItem_Packet), C_GetItem, itemID, playerID, isTool };

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
	C_DropItem_Packet packetData{ sizeof(C_DropItem_Packet), C_DropItem, itemID, playerID, isTool };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_DropItem;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendDropItemToSellingMachinePacket(int itemID, int playerID, int sellingMachineID)
{
	// Packet Data 积己
	C_DropItemToSellingMachine_Packet packetData{ sizeof(C_DropItemToSellingMachine_Packet), C_DropItemToSellingMachine, sellingMachineID, itemID, playerID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_DropItemToSellingMachine;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendChangeToolPacket(int playerID, int toolID)
{
	// Packet Data 积己
	C_ChangeTool_Packet packetData{ sizeof(C_ChangeTool_Packet), C_ChangeTool, toolID, playerID };

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
	C_UseTool_Packet packetData{ sizeof(C_UseTool_Packet), C_UseTool, toolID, playerID, playerRotation };

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
	C_UseKey_Packet packetData{ sizeof(C_UseKey_Packet), C_UseKey, toolID, doorID, playerID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UseKey;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendUseLanternPacket(int playerID, int lanternID)
{
	// Packet Data 积己
	C_UseLantern_Packet packetData{ sizeof(C_UseLantern_Packet), C_UseLantern, lanternID,  playerID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UseLantern;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendInteractDoorPacket(int playerID, int doorID)
{
	// Packet Data 积己
	C_InteractDoor_Packet packetData{ sizeof(C_InteractDoor_Packet), C_InteractDoor, doorID, playerID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_InteractDoor;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendSellItemPacket(int playerID, int sellingMachineID)
{
	// Packet Data 积己
	C_SellItem_Packet packetData{ sizeof(C_SellItem_Packet), C_SellItem, sellingMachineID, playerID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_SellItem;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendBuyItemPacket(int playerID, ItemType itemType, int itemCount)
{
	// Packet Data 积己
	C_BuyItem_Packet packetData{ sizeof(C_BuyItem_Packet), C_BuyItem, playerID, itemType, itemCount };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_BuyItem;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendChangeEmotionPacket(int playerID, Emotion emotion)
{
	// Packet Data 积己
	C_ChangeEmotion_Packet packetData{ sizeof(C_ChangeEmotion_Packet), C_ChangeEmotion, playerID, emotion };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_ChangeEmotion;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendEmotionResultPacket(float angryTime, float disgustTime, float fearTime, float happyTime, float sadTime, float surpriseTime, float neutralTime)
{
	// Packet Data 积己
	C_EmotionResult_Packet packetData{ sizeof(C_EmotionResult_Packet), C_EmotionResult, angryTime, disgustTime, fearTime, happyTime, sadTime, surpriseTime, neutralTime };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_EmotionResult;
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

void GameNetwork::SendSubmitItemPacket(int itemID, int playerID)
{
	// Packet Data 积己
	C_SubmitItem_Packet packetData{ sizeof(C_SubmitItem_Packet), C_SubmitItem, itemID, playerID };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_SubmitItem;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendRequestQuestRewardPacket(bool isMain)
{
	// Packet Data 积己
	C_RequestQuestReward_Packet packetData{ sizeof(C_RequestQuestReward_Packet), C_RequestQuestReward, isMain };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_RequestQuestReward;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_sendMutex);
	_sendEvents.push_back(event);
}

void GameNetwork::SendVoiceDataPacket(short clientID, char playerID, int sequenceNumber, std::vector<char>& audioData)
{
	std::vector<char> voiceData = SerializeVector(audioData);
	unsigned short packetSize = sizeof(short) + sizeof(PacketID) + sizeof(short) + sizeof(char) + sizeof(int) + voiceData.size();
	PacketID id = C_VoiceData;

	// Packet Serialize
	std::vector<char> serializedPacketData(packetSize - voiceData.size());
	memcpy(serializedPacketData.data(), &packetSize, sizeof(short));
	memcpy(serializedPacketData.data() + sizeof(short), &id, sizeof(PacketID));
	memcpy(serializedPacketData.data() + sizeof(short) + sizeof(PacketID), &clientID, sizeof(short));
	memcpy(serializedPacketData.data() + sizeof(short) + sizeof(PacketID) + sizeof(short), &playerID, sizeof(char));
	memcpy(serializedPacketData.data() + sizeof(short) + sizeof(PacketID) + sizeof(short) + sizeof(char), &sequenceNumber, sizeof(int));
	serializedPacketData.insert(serializedPacketData.end(), voiceData.begin(), voiceData.end());

	// SendEvent 积己
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_VoiceData;
	event->serializedPacketData = serializedPacketData;
	std::lock_guard<std::mutex> lock(_udpSendMutex);
	_unpSendEvents.push_back(event);
}