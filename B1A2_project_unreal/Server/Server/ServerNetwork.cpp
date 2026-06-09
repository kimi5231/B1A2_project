#include "pch.h"
#include "ServerNetwork.h"
#include "ServerFramework.h"
#include "Session.h"
#include "ExpOver.h"
#include "Room.h"
#include "Obstacle.h"
#include "Cube.h"
#include "Door.h"
#include "Lantern.h"
#include "EmotionGame.h"
#include "SellingMachine.h"
#include "Global.h"
#include "MainQuest.h"

ServerNetwork::ServerNetwork(ServerFramework* framework)
{
	_framework = framework;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "윈속 초기화 실패" << std::endl;
		return;
	}

	// TCP
	{
		// listenSocket 생성
		_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (_listenSocket == INVALID_SOCKET)
		{
			std::cout << "listenSocket 생성 실패" << std::endl;
			return;
		}

		// bind
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(PORT);
		if (bind(_listenSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			std::cout << "TCP bind 실패" << std::endl;
			return;
		}

		// listen
		if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			std::cout << "listen 실패" << std::endl;
			return;
		}
	}
	
	// UDP
	{
		// socket 생성
		_udpSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);

		// bind
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(PORT);
		if (bind(_udpSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			std::cout << "UDP bind 실패" << std::endl;
			return;
		}
	}
	
	// iocp port 생성
	_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// listenSocket 등록
	CreateIoCompletionPort((HANDLE)_listenSocket, _iocp, 0, 0);

	// accept
	_tempSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	_acceptOver._ioType = IOType::Accept;
	AcceptEx(_listenSocket, _tempSocket, _acceptOver._buffer.data(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &_acceptOver._over);

	// UDP 소켓 등록
	CreateIoCompletionPort((HANDLE)_udpSocket, _iocp, 0, 0);

	// recv
	for (int i = 0; i < 1; ++i)
	{
		ExpOver* udpOver = new ExpOver(IOType::UDPRecv);

		DWORD recvFlag = 0;
		DWORD bytesReceived = 0;
		WSARecvFrom(_udpSocket, &udpOver->_wsaBuffer, 1, &bytesReceived, &recvFlag, (sockaddr*)&udpOver->_udpAddr, &udpOver->_udpAddrLen, &udpOver->_over, nullptr);
	}

	for (int i = 0; i < MAX_CLIENT; ++i)
		_clients[i] = new Session();
}

ServerNetwork::~ServerNetwork()
{
	// socket close
	closesocket(_listenSocket);
	closesocket(_tempSocket);

	// 윈속 종료
	WSACleanup();
}

void ServerNetwork::Update()
{
	DWORD numByte;
	ULONG_PTR key;
	LPOVERLAPPED over;
	GetQueuedCompletionStatus(_iocp, &numByte, &key, &over, 0);
	
	if (over == nullptr)
	{
		if (key < 0 || key >= MAX_CLIENT)
			return;

		ProcessDisconnected(static_cast<int>(key));
		return;
	}

	ExpOver* expOver = reinterpret_cast<ExpOver*>(over);
	switch (expOver->_ioType)
	{
	case IOType::Accept:
		ProcessAccept();
		break;
	case IOType::Recv:
		ProcessRecv(static_cast<int>(key), numByte, expOver);
		break;
	case IOType::Send:
		delete expOver;
		break;
	case IOType::DB:
		ProcessDB(static_cast<int>(key), expOver);
		break;
	case IOType::UDPRecv:
		ProcessUDPRecv(numByte, expOver);
		break;
	default:
		std::cout << "Unknown IO type.\n";
		exit(-1);
		break;
	}
}

void ServerNetwork::ProcessAccept()
{
	// 할당할 수 있는 Client Session 찾기
	int clientIndex = -1;
	for (int i = 0; i < MAX_CLIENT; ++i)
	{
		if (!_clients[i]->_isConnected)
		{
			clientIndex = i;
			break;
		}
	}

	// 할당할 수 있는 Client Session이 없다면 연결끊기
	if (clientIndex == -1)
	{
		closesocket(_tempSocket);
		return;
	}

	std::cout << "Client 접속" << std::endl;

	// clientSocket 등록
	CreateIoCompletionPort((HANDLE)_tempSocket, _iocp, clientIndex, 0);
	_clients[clientIndex]->_clientSocket = _tempSocket;
	_clients[clientIndex]->_id = clientIndex;
	_clients[clientIndex]->_isConnected = true;
	_clients[clientIndex]->_prevRecv = 0;
	_clients[clientIndex]->_room = nullptr;
	_clients[clientIndex]->_player = nullptr;

	_clients[clientIndex]->Recv();

	// accept 다시 걸기
	_tempSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	_acceptOver._ioType = IOType::Accept;
	AcceptEx(_listenSocket, _tempSocket, _acceptOver._buffer.data(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &_acceptOver._over);
}

void ServerNetwork::ProcessDisconnected(int clientIndex)
{
	std::cout << "client[" << clientIndex << "] 접속 종료\n";
	_clients[clientIndex]->_isConnected = false;
	closesocket(_clients[clientIndex]->_clientSocket);
	_clients[clientIndex]->_clientSocket = INVALID_SOCKET;
	if (_clients[clientIndex]->_room)
	{
		_clients[clientIndex]->_room->RemoveObject(ObjectType::Player, _clients[clientIndex]->_player->GetID(), true);
		_clients[clientIndex]->_room = nullptr;
		_clients[clientIndex]->_player = nullptr;
	}
}

void ServerNetwork::ProcessRecv(int clientIndex, int numByte, ExpOver* expOver)
{
	// Client 접속 종료
	if (numByte == 0)
	{
		ProcessDisconnected(clientIndex);
		return;
	}

	// 처리해야할 데이터 조합하기
	std::vector<char> packet;
	packet.insert(packet.end(), _clients[clientIndex]->_recvOver._buffer.begin(), _clients[clientIndex]->_recvOver._buffer.begin() + _clients[clientIndex]->_prevRecv);
	packet.insert(packet.end(), expOver->_buffer.begin(), expOver->_buffer.begin() + numByte);
	
	int dataSize = numByte + _clients[clientIndex]->_prevRecv;
	while (dataSize > 0)
	{
		// packetSize 추출
		char packetSize;
		memcpy(&packetSize, packet.data(), sizeof(char));

		// 남은 데이터의 사이즈가 패킷의 사이즈보다 작으면 중단
		if (packetSize > dataSize)
			break;
		
		ProcessPacket(packet, clientIndex);
		
		// 처리한 패킷 길이만큼 제외
		dataSize -= packetSize;
	}

	// 남은 데이터 저장
	if (dataSize > 0)
	{
		memmove(_clients[clientIndex]->_recvOver._buffer.data(), packet.data(), dataSize);
		_clients[clientIndex]->_prevRecv = dataSize;
	}

	_clients[clientIndex]->Recv();
}

void ServerNetwork::ProcessUDPRecv(int numByte, ExpOver* expOver)
{
	// 남은 데이터가 최소 수치보다 적으면 무시
	if (numByte < sizeof(unsigned short) + sizeof(PacketID))
		return;

	std::vector<char> packet;
	packet.insert(packet.end(), expOver->_buffer.begin(), expOver->_buffer.begin() + numByte);

	// packetSize 추출
	short packetSize;
	memcpy(&packetSize, packet.data(), sizeof(short));

	// 남은 데이터의 사이즈가 패킷의 사이즈보다 작으면 중단
	if (packetSize > numByte)
		return;

	// packetID 추출
	PacketID id;
	memcpy(&id, packet.data() + sizeof(short), sizeof(PacketID));
	packet.erase(packet.begin(), packet.begin() + sizeof(unsigned short) + sizeof(PacketID));

	switch (id)
	{
	case C_VoiceData:
	{
		C_VoiceData_Packet voiceDataPacket;

		voiceDataPacket.size = packetSize;
		voiceDataPacket.packetID = id;
		memcpy(&voiceDataPacket.clientID, packet.data(), sizeof(unsigned short));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned short));
		memcpy(&voiceDataPacket.playerID, packet.data(), sizeof(unsigned char));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char));
		memcpy(&voiceDataPacket.sequenceNumber, packet.data(), sizeof(unsigned int));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned int));
		voiceDataPacket.audioData = DeserializeVector<char>(packet);
		
		ProcessVoiceDataPacket(voiceDataPacket, expOver);
		break;
	}
	}

	DWORD recvFlag = 0;
	DWORD bytesReceived = 0;
	WSARecvFrom(_udpSocket, &expOver->_wsaBuffer, 1, &bytesReceived, &recvFlag, (sockaddr*)&expOver->_udpAddr, &expOver->_udpAddrLen, &expOver->_over, nullptr);
}

void ServerNetwork::ProcessPacket(std::vector<char>& packet, int clientIndex)
{
	// packetID 추출
	PacketID id;
	memcpy(&id, packet.data() + sizeof(char), sizeof(PacketID));

	switch (id)
	{
	case C_Login:
	{
		unsigned char packetSize;
		memcpy(&packetSize, packet.data(), sizeof(unsigned char));
		packet.erase(packet.begin(), packet.begin() + sizeof(unsigned char) + sizeof(PacketID));

		C_Login_Packet loginPacket{ packetSize, C_Login, DeserializeVector<char>(packet) };
		packet.erase(packet.begin(), packet.end());
		ProcessLoginPacket(loginPacket, clientIndex);
		break;
	}
	case C_Logout:
	{
		C_Logout_Packet logoutPacket;
		memcpy(&logoutPacket, packet.data(), sizeof(C_Logout_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_Logout_Packet));
		ProcessLogoutPacket(logoutPacket, clientIndex);
		break;
	}
	case C_CreateRoom:
	{
		C_CreateRoom_Packet createRoomPacket;
		memcpy(&createRoomPacket, packet.data(), sizeof(C_CreateRoom_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_CreateRoom_Packet));
		ProcessCreateRoomPacket(createRoomPacket, clientIndex);
		break;
	}
	case C_EnterRoom:
	{
		C_EnterRoom_Packet enterRoomPacket;
		memcpy(&enterRoomPacket, packet.data(), sizeof(C_EnterRoom_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_EnterRoom_Packet));
		ProcessEnterRoomPacket(enterRoomPacket, clientIndex);
		break;
	}
	case C_ExitRoom:
	{
		C_ExitRoom_Packet exitRoomPacket;
		memcpy(&exitRoomPacket, packet.data(), sizeof(C_ExitRoom_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_ExitRoom_Packet));
		ProcessExitRoomPacket(exitRoomPacket, clientIndex);
		break;
	}
	case C_Move:
	{
		C_Move_Packet movePacket;
		memcpy(&movePacket, packet.data(), sizeof(C_Move_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_Move_Packet));
		ProcessMovePacket(movePacket, clientIndex);
		break;
	}
	case C_UpdateObjectState:
	{
		C_UpdateObjectState_Packet updateObjectPacket;
		memcpy(&updateObjectPacket, packet.data(), sizeof(C_UpdateObjectState_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_UpdateObjectState_Packet));
		ProcessUpdateObjectStatePacket(updateObjectPacket, clientIndex);
		break;
	}
	case C_GetItem:
	{
		C_GetItem_Packet getItemPacket;
		memcpy(&getItemPacket, packet.data(), sizeof(C_GetItem_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_GetItem_Packet));
		ProcessGetItemPacket(getItemPacket, clientIndex);
		break;
	}
	case C_DropItem:
	{
		C_DropItem_Packet dropItemPacket;
		memcpy(&dropItemPacket, packet.data(), sizeof(C_DropItem_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_DropItem_Packet));
		ProcessDropItemPacket(dropItemPacket, clientIndex);
		break;
	}
	case C_DropItemToSellingMachine:
	{
		C_DropItemToSellingMachine_Packet dropItemToSellingMachinePacket;
		memcpy(&dropItemToSellingMachinePacket, packet.data(), sizeof(C_DropItemToSellingMachine_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_DropItemToSellingMachine_Packet));
		ProcessDropItemToSellingMachinePacket(dropItemToSellingMachinePacket, clientIndex);
		break;
	}
	case C_ChangeTool:
	{
		C_ChangeTool_Packet changeToolPacket;
		memcpy(&changeToolPacket, packet.data(), sizeof(C_ChangeTool_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_ChangeTool_Packet));
		ProcessChangeToolPacket(changeToolPacket, clientIndex);
		break;
	}
	case C_UseTool:
	{
		C_UseTool_Packet useToolPacket;
		memcpy(&useToolPacket, packet.data(), sizeof(C_UseTool_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_UseTool_Packet));
		ProcessUseToolPacket(useToolPacket, clientIndex);
		break;
	}
	case C_UseKey:
	{
		C_UseKey_Packet useKeyPacket;
		memcpy(&useKeyPacket, packet.data(), sizeof(C_UseKey_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_UseKey_Packet));
		ProcessUseKeyPacket(useKeyPacket, clientIndex);
		break;
	}
	case C_UseLantern:
	{
		C_UseLantern_Packet useLanternPacket;
		memcpy(&useLanternPacket, packet.data(), sizeof(C_UseLantern_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_UseLantern_Packet));
		ProcessUseLanternPacket(useLanternPacket, clientIndex);
		break;
	}
	case C_InteractDoor:
	{
		C_InteractDoor_Packet interactDoorPacket;
		memcpy(&interactDoorPacket, packet.data(), sizeof(C_InteractDoor_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_InteractDoor_Packet));
		ProcessInteractDoorPacket(interactDoorPacket, clientIndex);
		break;
	}
	case C_SellItem:
	{
		C_SellItem_Packet sellItemPacket;
		memcpy(&sellItemPacket, packet.data(), sizeof(C_SellItem_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_SellItem_Packet));
		ProcessSellItemPacket(sellItemPacket, clientIndex);
		break;
	}
	case C_BuyItem:
	{
		C_BuyItem_Packet buyItemPacket;
		memcpy(&buyItemPacket, packet.data(), sizeof(C_BuyItem_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_BuyItem_Packet));
		ProcessBuyItemPacket(buyItemPacket, clientIndex);
		break;
	}
	case C_ChangeEmotion:
	{
		C_ChangeEmotion_Packet changeEmotionPacket;
		memcpy(&changeEmotionPacket, packet.data(), sizeof(C_ChangeEmotion_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_ChangeEmotion_Packet));
		ProcessChangeEmotionPacket(changeEmotionPacket, clientIndex);
		break;
	}
	case C_EmotionResult:
	{
		C_EmotionResult_Packet emotionResultPacket;
		memcpy(&emotionResultPacket, packet.data(), sizeof(C_EmotionResult_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_EmotionResult_Packet));
		ProcessEmotionResultPacket(emotionResultPacket, clientIndex);
		break;
	}
	case C_StartStage:
	{
		C_StartStage_Packet startStagePacket;
		memcpy(&startStagePacket, packet.data(), sizeof(C_StartStage_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_StartStage_Packet));
		ProcessStartStagePacket(startStagePacket, clientIndex);
		break;
	}
	case C_EndStage:
	{
		C_EndStage_Packet endStagePacket;
		memcpy(&endStagePacket, packet.data(), sizeof(C_EndStage_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_EndStage_Packet));
		ProcessEndStagePacket(endStagePacket, clientIndex);
		break;
	}
	case C_SubmitItem:
	{
		C_SubmitItem_Packet submitItemPacket;
		memcpy(&submitItemPacket, packet.data(), sizeof(C_SubmitItem_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_SubmitItem_Packet));
		ProcessSubmitItemPacket(submitItemPacket, clientIndex);
		break;
	}
	case C_RequestQuestReward:
	{
		C_RequestQuestReward_Packet requestQuestRewardPacket;
		memcpy(&requestQuestRewardPacket, packet.data(), sizeof(C_RequestQuestReward_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_RequestQuestReward_Packet));
		ProcessRequestQuestRewardPacket(requestQuestRewardPacket, clientIndex);
		break;
	}
	}
}

void ServerNetwork::ProcessDB(int clientIndex, ExpOver* expOver)
{
	switch (expOver->_dbType)
	{
	case DBType::ExistID:
	{
		if(expOver->_dbResult)
			SendLoginResultPacket(LoginResult::Sucess, clientIndex, _clients[clientIndex]);
		else
			SendLoginResultPacket(LoginResult::Failed, clientIndex, _clients[clientIndex]);
		delete expOver;
		break;
	}
	}
}

template<class T>
std::vector<char> ServerNetwork::SerializePOD(const T& pod)
{
	std::vector<char> serializedData(sizeof(pod));
	memcpy(serializedData.data(), &pod, sizeof(pod));

	return serializedData;
}

template<class T>
std::vector<char> ServerNetwork::SerializeVector(const std::vector<T>& vector)
{
	int size = vector.size();

	std::vector<char> serializedData(sizeof(int) + vector.size() * sizeof(T));
	memcpy(serializedData.data(), &size, sizeof(int));
	memcpy(serializedData.data() + sizeof(int), vector.data(), size * sizeof(T));

	return serializedData;
}

template<class T>
std::vector<T> ServerNetwork::DeserializeVector(const std::vector<char>& data)
{
	int size;
	memcpy(&size, data.data(), sizeof(int));

	std::vector<T> vector(size);
	memcpy(vector.data(), data.data() + sizeof(int), size * sizeof(T));

	return vector;
}

void ServerNetwork::SendSignupResultPacket(SignupResult result, Session* client)
{
	// Packet Data 생성
	S_SignupResult_Packet packetData{ sizeof(S_SignupResult_Packet), S_SignupResult, result };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendLoginResultPacket(LoginResult result, short clientID, Session* client)
{
	// Packet Data 생성
	S_LoginResult_Packet packetData{ sizeof(S_LoginResult_Packet), S_LoginResult, result, clientID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendCurrentRoomListPacket(std::vector<Room*>& rooms, Session* client)
{
	std::vector<RoomDTO> roomDTOs;
	for (auto& room : rooms)
	{
		RoomDTO DTO{ room->GetCurrentPlayerCount(), room->GetID(), room->GetRoomState(), SerializeVector(room->GetTitle()) };
		roomDTOs.push_back(DTO);
	}

	// Packet Serialize
	std::vector<char> roomData;
	for(auto& roomDTO : roomDTOs)
	{
		roomData.push_back(roomDTO.playerCount);
		roomData.push_back(roomDTO.roomID);
		roomData.push_back(static_cast<char>(roomDTO.roomState));
		roomData.push_back(roomDTO.roomTitle.size());
		roomData.insert(roomData.end(), roomDTO.roomTitle.begin(), roomDTO.roomTitle.end());
	}

	unsigned short packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(char) + roomData.size();
	std::vector<char> serializedPacketData(sizeof(unsigned short));
	memcpy(serializedPacketData.data(), &packetSize, sizeof(unsigned short));
	serializedPacketData.push_back(S_CurrentRoomList);
	serializedPacketData.push_back(roomDTOs.size());
	serializedPacketData.insert(serializedPacketData.end(), roomData.begin(), roomData.end());

	client->Send(serializedPacketData);
}

void ServerNetwork::SendCreateRoomResultPacket(char roomID, bool result, Session* client)
{
	// Packet Data 생성
	S_CreateRoomResult_Packet packetData{ sizeof(S_CreateRoomResult_Packet), S_CreateRoomResult, result, roomID };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	client->Send(serializedPacketData);
}

void ServerNetwork::SendAddPlayerPacket(Player* player, Session* client)
{
	// Packet Data 생성
	S_AddPlayer_Packet packetData{ sizeof(S_AddPlayer_Packet), S_AddPlayer, player->GetID(), player->GetPos(), player->GetRotation() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendAddMonsterPacket(Monster* monster, Session* client)
{
	// Packet Data 생성
	S_AddMonster_Packet packetData{ sizeof(S_AddMonster_Packet), S_AddMonster, monster->GetID(), monster->GetPos(), monster->GetRotation(), monster->GetMonsterType(), monster->GetState() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendAddItemPacket(Item* item, bool isTool, Session* client)
{
	// Packet Data 생성
	S_AddItem_Packet packetData{ sizeof(S_AddItem_Packet), S_AddItem, item->GetID(), isTool, item->GetPos(), item->GetItemType(), item->GetCost() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendAddObstaclePacket(Obstacle* obstacle, Session* client)
{
	// Packet Data 생성
	S_AddObstacle_Packet packetData{ sizeof(S_AddObstacle_Packet), S_AddObstacle, obstacle->GetID(), obstacle->GetPos(), obstacle->GetRotation(), obstacle->GetObstacleType() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendRemoveObjectPacket(ObjectType objectType, int objectID, Session* client)
{
	// Packet Data 생성
	S_RemoveObject_Packet packetData{ sizeof(S_RemoveObject_Packet), S_RemoveObject, objectID, objectType };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendMovePacket(GameObject* object, Session* client)
{
	// Packet Data 생성
	S_Move_Packet packetData{ sizeof(S_Move_Packet), S_Move, object->GetID(), object ->GetPos(), object->GetRotation(), object ->GetObjectType(), object ->GetState() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateObjectStatePacket(GameObject* object, Session* client)
{
	// Packet Data 생성
	S_UpdateObjectState_Packet packetData{ sizeof(S_UpdateObjectState_Packet), S_UpdateObjectState, object->GetID(), object->GetObjectType(), object->GetState() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendCreateCubesPacket(const std::vector<CubeRef>& cubes, const std::vector<Door*>& doors, const std::vector<SellingMachine*>& sellingMachines, Session* client)
{
	std::vector<CubeDTO> cubeDTOs;
	for (auto& cube : cubes)
	{
		// Cube 정보 기록
		CubeDTO DTO{ cube->GetCubeType(), cube->GetPos(), cube->GetDir() };
		cubeDTOs.push_back(DTO);
	}

	std::vector<DoorDTO> doorDTOs;
	for (auto& door : doors)
	{
		// Door 정보 기록
		DoorDTO DTO{ door->GetID(), door->GetPos(), door->GetDir(), door->GetState(), door->GetDoorType() };
		doorDTOs.push_back(DTO);
	}

	std::vector<SellingMachineDTO> sellingMachineDTOs;
	for (auto& sellingMachine : sellingMachines)
	{
		// SellingMachine 정보 기록
		SellingMachineDTO DTO{ sellingMachine->GetID(), sellingMachine->GetPos(), sellingMachine->GetDir(), sellingMachine->GetState(), sellingMachine->GetCreditLimit() };
		sellingMachineDTOs.push_back(DTO);
	}
	
	// Packet Serialize
	std::vector<char> cubeData = SerializeVector(cubeDTOs);
	std::vector<char> doorData = SerializeVector(doorDTOs);
	std::vector<char> sellingMachineData = SerializeVector(sellingMachineDTOs);
	unsigned short packetSize = sizeof(unsigned short) + sizeof(PacketID) + cubeData.size() + doorData.size() + sellingMachineData.size();
	std::vector<char> serializedPacketData(sizeof(unsigned short));

	memcpy(serializedPacketData.data(), &packetSize, sizeof(unsigned short));
	serializedPacketData.push_back(S_CreateCubes);
	serializedPacketData.insert(serializedPacketData.end(), cubeData.begin(), cubeData.end());
	serializedPacketData.insert(serializedPacketData.end(), doorData.begin(), doorData.end());
	serializedPacketData.insert(serializedPacketData.end(), sellingMachineData.begin(), sellingMachineData.end());

	client->Send(serializedPacketData);
}

void ServerNetwork::SendAddItemToInventoryPacket(Item* item, bool isTool, Session* client)
{
	// Packet Data 생성
	S_AddItemToInventory_Packet packetData{ sizeof(S_AddItemToInventory_Packet), S_AddItemToInventory, item->GetID(), isTool, item->GetItemType(), item->GetWeight() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendRemoveItemFromInventoryPacket(Item* item, bool isTool, Session* client)
{
	// Packet Data 생성
	S_RemoveItemFromInventory_Packet packetData{ sizeof(S_RemoveItemFromInventory_Packet), S_RemoveItemFromInventory, item->GetID(), isTool, item->GetItemType() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendItemPickupNotifyPacket(Item* item, int playerID, bool isTool, Session* client)
{
	// Packet Data 생성
	S_ItemPickupNotify_Packet packetData{ sizeof(S_ItemPickupNotify_Packet), S_ItemPickupNotify, item->GetID(), playerID, isTool, item->GetItemType() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendDropItemPacket(Item* item, int playerID, Vector itemPos, bool isTool, bool isToSellingMachine, Session* client)
{
	// Packet Data 생성
	S_DropItem_Packet packetData{ sizeof(S_DropItem_Packet), S_DropItem, item->GetID(), playerID, isTool, isToSellingMachine, item->GetItemType(), itemPos, item->GetCost(), 0};

	// 아이템이 랜턴이라면 배터리 추가
	if (item->GetItemType() == ItemType::LANTERN)
	{
		Lantern* lantern = dynamic_cast<Lantern*>(item);
		packetData.laternBattery = lantern->GetCurrentBattery();
	}

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateCurrentToolPacket(int itemID, int playerID, ItemType type, Session* client)
{
	// Packet Data 생성
	S_UpdateCurrentTool_Packet packetData{ sizeof(S_UpdateCurrentTool_Packet), S_UpdateCurrentTool, itemID, playerID, type };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendUseToolPacket(int playerID, ItemType type, Session* client)
{
	// Packet Data 생성
	S_UseTool_Packet packetData{ sizeof(S_UseTool_Packet), S_UseTool, playerID, type };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendTurnOnLanternPacket(Lantern* lantern, int playerID, Session* client)
{
	// Packet Data 생성
	S_TurnOnLantern_Packet packetData{ sizeof(S_TurnOnLantern_Packet), S_TurnOnLantern, lantern->GetID(), playerID, lantern->GetCurrentBattery(), lantern->GetRange(), lantern->GetRange() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendTurnOffLanternPacket(Lantern* lantern, int playerID, Session* client)
{
	// Packet Data 생성
	S_TurnOffLantern_Packet packetData{ sizeof(S_TurnOffLantern_Packet), S_TurnOffLantern, lantern->GetID(), playerID, lantern->GetCurrentBattery() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendInteractDoorNotifyPacket(int playerID, int doorID, ObjectState doorState, Session* client)
{
	// Packet Data 생성
	S_InteractDoorNotify_Packet packetData{ sizeof(S_InteractDoorNotify_Packet), S_InteractDoorNotify, doorID, playerID, doorState };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendSellItemResultPacket(char playerID, char sellingMachineID, ObjectState sellingMachineState, short remainCredit, short collectCredit, short currentCredit, std::vector<int>& sellItems, Session* client)
{
	// Packet Serialize
	PacketID packetID = S_SellItemResult;
	std::vector<char> itemIDs = SerializeVector(sellItems);
	unsigned short packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(char) + sizeof(char) + sizeof(ObjectState) + sizeof(short) + sizeof(short) + sizeof(short) + itemIDs.size();
	std::vector<char> serializedPacketData(packetSize - itemIDs.size());

	memcpy(serializedPacketData.data(), &packetSize, sizeof(unsigned short));
	memcpy(serializedPacketData.data() + sizeof(unsigned short), &packetID, sizeof(unsigned char));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID), &sellingMachineID, sizeof(unsigned char));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned char), &playerID, sizeof(unsigned char));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned char) + sizeof(unsigned char), &remainCredit, sizeof(unsigned short));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(unsigned short), &collectCredit, sizeof(unsigned short));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned short), &currentCredit, sizeof(unsigned short));
	memcpy(serializedPacketData.data() + sizeof(unsigned short) + sizeof(PacketID) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned short) + sizeof(unsigned short), &sellingMachineState, sizeof(ObjectState));
	serializedPacketData.insert(serializedPacketData.end(), itemIDs.begin(), itemIDs.end());

	client->Send(serializedPacketData);
}

void ServerNetwork::SendBuyItemResultPacket(short currentCredit, Session* client)
{
	// Packet Data 생성
	S_BuyItemResult_Packet packetData{ sizeof(S_BuyItemResult_Packet), S_BuyItemResult, currentCredit };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateHpPacket(int playerID, int hp, Session* client)
{
	// Packet Data 생성
	S_UpdateHp_Packet packetData{ sizeof(S_UpdateHp_Packet), S_UpdateHp, playerID, hp };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendEmotionGameResultPacket(int playerID, int playerHP, EmotionGame* emotionGame, Session* client)
{
	// Packet Data 생성
	S_EmotionGameResult_Packet packetData{ sizeof(S_EmotionGameResult_Packet), S_EmotionGameResult, emotionGame->GetID(), playerID, playerHP, emotionGame->GetEmotion(), emotionGame->GetResult() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendSpawnParticlePacket(Vector pos, Session* client)
{
	// Packet Data 생성
	S_SpawnParticle_Packet packetData{ sizeof(S_SpawnParticle_Packet), S_SpawnParticle, pos };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendStartStagePacket(Session* client)
{
	// Packet Data 생성
	S_StartStage_Packet packetData{ sizeof(S_StartStage_Packet), S_StartStage };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendEndStagePacket(Session* client)
{
	std::vector<StageResultDTO> stageResultDTOs;
	for (auto& player : client->_room->GetPlayers())
	{
		if (player->GetClient())
		{
			StageResultDTO DTO{ false, client->_name };

			if (player->GetState() == ObjectState::DEAD)
				DTO.isDead = true;

			stageResultDTOs.push_back(DTO);
		}
	}

	// Packet Serialize
	std::vector<char> stageResultData;
	for (auto& stageResultDTO : stageResultDTOs)
	{
		stageResultData.push_back(stageResultDTO.isDead);
		stageResultData.push_back(stageResultDTO.name.size());
		stageResultData.insert(stageResultData.end(), stageResultDTO.name.begin(), stageResultDTO.name.end());
	}

	unsigned short packetSize = sizeof(unsigned short) + sizeof(PacketID) + sizeof(char) + stageResultData.size();
	std::vector<char> serializedPacketData(sizeof(unsigned short));
	memcpy(serializedPacketData.data(), &packetSize, sizeof(unsigned short));
	serializedPacketData.push_back(S_EndStage);
	serializedPacketData.push_back(stageResultDTOs.size());
	serializedPacketData.insert(serializedPacketData.end(), stageResultData.begin(), stageResultData.end());

	client->Send(serializedPacketData);
}

void ServerNetwork::SendGameOverPacket(Session* client)
{
	// Packet Data 생성
	S_GameOver_Packet packetData{ sizeof(S_GameOver_Packet), S_GameOver };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateQuestPacket(Quest* quest, bool isMain, Session* client)
{
	// Packet Data 생성
	S_UpdateQuest_Packet packetData{ sizeof(S_UpdateQuest_Packet), S_UpdateQuest, isMain, quest->GetID(), quest->GetGoalCollectCount(), quest->GetDeadLine(), quest->GetCollectItemType()};
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateQuestProgressPacket(Quest* quest, bool isMain, Session* client)
{
	// Packet Data 생성
	S_UpdateQuestProgress_Packet packetData{ sizeof(S_UpdateQuestProgress_Packet), S_UpdateQuestProgress, isMain, quest->GetCurrentCollectCount(), quest->GetDeadLine() };
	
	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);
	
	client->Send(serializedPacketData);
}

void ServerNetwork::SendUpdateCreditPacket(short goalCredit, short collectCredit, short currentCredit, Session* client)
{
	// Packet Data 생성
	S_UpdateCredit_Packet packetData{ sizeof(S_UpdateCredit_Packet), S_UpdateCredit, goalCredit, collectCredit, currentCredit };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendVoiceDataPacket(char playerId, int sequenceNumber, std::vector<char>& audioData, ExpOver* expOver)
{
	std::vector<char> voiceData = SerializeVector(audioData);
	unsigned short packetSize = sizeof(short) + sizeof(PacketID) + sizeof(char) + sizeof(int) + voiceData.size();
	PacketID id = S_VoiceData;

	// Packet Serialize
	std::vector<char> serializedPacketData(packetSize - voiceData.size());
	memcpy(serializedPacketData.data(), &packetSize, sizeof(short));
	memcpy(serializedPacketData.data() + sizeof(short), &id, sizeof(PacketID));
	memcpy(serializedPacketData.data() + sizeof(short) + sizeof(PacketID), &playerId, sizeof(char));
	memcpy(serializedPacketData.data() + sizeof(short) + sizeof(PacketID) + sizeof(char), &sequenceNumber, sizeof(int));
	serializedPacketData.insert(serializedPacketData.end(), voiceData.begin(), voiceData.end());

	ExpOver* over = new ExpOver(IOType::Send);
	memcpy(over->_buffer.data(), serializedPacketData.data(), serializedPacketData.size());
	over->_wsaBuffer.buf = (char*)over->_buffer.data();
	over->_wsaBuffer.len = serializedPacketData.size();
	WSASendTo(_udpSocket, &over->_wsaBuffer, 1, 0, 0,(sockaddr*)&expOver->_udpAddr, expOver->_udpAddrLen, &over->_over, nullptr);
}

void ServerNetwork::ProcessSignupPacket(C_Signup_Packet packet, int clientIndex)
{
	// DB 요청
	/*DBWork work{DBType::ExistID, clientIndex, packet.id };
	g_dbManager->AddWork(work);*/

	// 이건 ProcessDB로 옮길 예정
	SignupResult result = SignupResult::Sucess;

	// 회원가입 결과 전송
	SendSignupResultPacket(result, _clients[clientIndex]);
}

void ServerNetwork::ProcessLoginPacket(C_Login_Packet packet, int clientIndex)
{
	// 현재 접속하고 있는 ID라면 로그인 실패
	for (const auto& client : _clients)
	{
		if (client->_isConnected && client->_name == packet.id)
		{
			SendLoginResultPacket(LoginResult::IsExit, clientIndex, _clients[clientIndex]);
			return;
		}
	}

	// DB에 존재하는 ID인지 확인 요청
	/*DBWork work{DBType::ExistID, clientIndex, packet.id };
	g_dbManager->AddWork(work);*/

	// 이건 ProcessDB로 옮길 예정
	LoginResult result = LoginResult::Sucess;

	// 로그인에 성공했다면 RoomList 보내주기
	if(result == LoginResult::Sucess)
		SendCurrentRoomListPacket(_framework->GetWaitingRooms(), _clients[clientIndex]);

	// 로그인 결과 전송
	SendLoginResultPacket(result, clientIndex, _clients[clientIndex]);
}

void ServerNetwork::ProcessLogoutPacket(C_Logout_Packet packet, int clientIndex)
{
	// RoomList 보내주는 Client 목록에서 제외

	// 게임 중이었다면, Room에서 제외
	_clients[clientIndex]->_room->RemoveObject(ObjectType::Player, _clients[clientIndex]->_player->GetID(), true);
	_clients[clientIndex]->_player = nullptr;
	_clients[clientIndex]->_room = nullptr;
}

void ServerNetwork::ProcessCreateRoomPacket(C_CreateRoom_Packet packet, int clientIndex)
{
	Room* room = _framework->AddRoom(_clients[clientIndex]->_name);
	if (!room)
	{
		// Room 생성 실패 알림
		SendCreateRoomResultPacket(0, false, _clients[clientIndex]);
		return;
	}

	// Room 생성 성공 알림
	SendCreateRoomResultPacket(room->GetID(), true, _clients[clientIndex]);
	_clients[clientIndex]->_room = room;
}

void ServerNetwork::ProcessEnterRoomPacket(C_EnterRoom_Packet packet, int clientIndex)
{
	// 요청한 Room에 들어갈 수 있는지 확인
	std::array<Room*, MAX_ROOM>& rooms = _framework->GetRooms();
	
	// 들어갈 수 있다면, 해당 Room에 Player 추가
	if (rooms[packet.roomID]->GetRoomState() == RoomState::Wait)
	{
		_clients[clientIndex]->_room = rooms[packet.roomID];
		_clients[clientIndex]->_player = _clients[clientIndex]->_room->AddPlayer();
		_clients[clientIndex]->_player->SetClient(_clients[clientIndex]);
		
		// 새로 접속한 Client에게 자신을 나타낼 Player 정보 전송
		SendAddPlayerPacket(_clients[clientIndex]->_player, _clients[clientIndex]);

		// 새로 접속한 Client에게 기존에 있던 Object 정보 전송
		for (auto& player : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!player->GetClient())
				continue;

			// 자기 자신 제외
			if (_clients[clientIndex]->_player == player)
				continue;

			SendAddPlayerPacket(player, _clients[clientIndex]);
		}

		// 기본 셋팅 정보 전송
		SendUpdateQuestPacket(_clients[clientIndex]->_room->GetMainQuest(), true, _clients[clientIndex]);
		SendUpdateQuestPacket(_clients[clientIndex]->_room->GetSubQuest(), false, _clients[clientIndex]);
		SendUpdateCreditPacket(_clients[clientIndex]->_room->GetGoalCredit(), _clients[clientIndex]->_room->GetCollectCredit(), _clients[clientIndex]->_room->GetCurrentCredit(), _clients[clientIndex]);
	}
}

void ServerNetwork::ProcessExitRoomPacket(C_ExitRoom_Packet packet, int clientIndex)
{
	// Room에서 Player 제거
	_clients[clientIndex]->_room->RemoveObject(ObjectType::Player, _clients[clientIndex]->_player->GetID(), true);
	_clients[clientIndex]->_player = nullptr;
	_clients[clientIndex]->_room = nullptr;

	// RoomList 전송
	SendCurrentRoomListPacket(_framework->GetWaitingRooms(), _clients[clientIndex]);
}

void ServerNetwork::ProcessMovePacket(C_Move_Packet packet, int clientIndex)
{
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(packet.type, packet.id));

	if (player == nullptr)
		return;

	if (player->GetIsCanMove())
		player->SetPos(packet.pos);
	player->SetRotation(packet.rotation);
	player->SetState(packet.state);

	// 자신을 제외한 모든 Client들에게 알리기
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		// 자기 자신 제외
		if (_clients[clientIndex]->_player == p && p->GetIsCanMove())
			continue;

		SendMovePacket(player, p->GetClient());
	}
}

void ServerNetwork::ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet, int clientIndex)
{
	GameObject* object = _clients[clientIndex]->_room->GetGameObject(packet.type, packet.id);

	object->SetState(packet.state);

	// 자신을 제외한 모든 클라이언트에게 알리기
	for (auto& player : _clients[clientIndex]->_room->GetPlayers())
	{
		if (player->GetClient())
			continue;

		// 자기 자신 제외
		if (_clients[clientIndex]->_player == player)
			continue;

		SendUpdateObjectStatePacket(object, player->GetClient());
	}
}

void ServerNetwork::ProcessGetItemPacket(C_GetItem_Packet packet, int clientIndex)
{
	// Player가 요청한 아이템이 얻을 수 있는 것인지 확인
	Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.itemID));
	if (item->GetObjectPoolState() != ObjectPoolState::InWorld)
		return;

	// 아이템을 얻을 수 있는 조건인지 확인(거리)
	
	// 아이템이 판매기 안에 있던 거라면 판매기에서 제외
	const std::vector<SellingMachine*>& sellingMachines = _clients[clientIndex]->_room->GetSellingMachine();
	for (auto sellingMachine : sellingMachines)
	{
		if (sellingMachine->ExistItem(packet.itemID))
		{
			sellingMachine->RemoveItem(packet.itemID);
			break;
		}
	}

	// 얻을 수 있는 아이템이라면 Player 인벤토리에 추가
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	// 아이템이 제대로 추가되었다면
	if (player->AddItemToInventory(packet.isTool, packet.itemID))
	{
		// 획득한 아이템 ObjectPoolState 변경
		item->SetObjectPoolState(ObjectPoolState::InInventory);
		// ownerID 설정
		item->SetOwnerID(player->GetID());

		// 아이템을 획득한 Player에게 인벤토리에 아이템 추가 알림
		SendAddItemToInventoryPacket(item, packet.isTool, player->GetClient());

		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			// 자기 자신 제외
			if (p == player)
				continue;

			SendItemPickupNotifyPacket(item, player->GetID(), packet.isTool, p->GetClient());
		}
	}
}

void ServerNetwork::ProcessDropItemPacket(C_DropItem_Packet packet, int clientIndex)
{
	// Player 인벤토리에서 아이템 제거
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	// 아이템이 제대로 제거되었다면
	if (player->RemoveItemFromInventory(packet.isTool, packet.itemID))
	{
		// 떨어뜨린 아이템 정보 수정
		Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.itemID));
		item->SetPos(player->GetPos());
		item->SetObjectPoolState(ObjectPoolState::InWorld);
		// ownerID 초기화
		item->SetOwnerID(-1);

		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			SendDropItemPacket(item, player->GetID(), item->GetPos(), packet.isTool, false,  p->GetClient());
		}
	}
}

void ServerNetwork::ProcessDropItemToSellingMachinePacket(C_DropItemToSellingMachine_Packet packet, int clientIndex)
{
	// 요청한 Player가 판매기와 거리가 되는지 확인 
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	SellingMachine* sellingMachine = dynamic_cast<SellingMachine*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::SellingMachine, packet.sellingMachineID));
	
	// 판매기가 활성화 상태인지 확인
	if (sellingMachine->GetState() == ObjectState::CLOSE)
		return;

	// 금액 제한이 남았는지 확인
	if (sellingMachine->GetRemainCreditLimit() <= 0)
		return;
	
	// Player 인벤토리에서 아이템 제거
	// 아이템이 제대로 제거되었다면
	if (player->RemoveItemFromInventory(false, packet.itemID))
	{
		// 떨어뜨린 아이템 정보 수정
		Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.itemID));
		
		// SellingMachine 안에 배치. 나중에 제대로 된 값으로 입력할 것.
		Vector pos = sellingMachine->GetPos();
		Dir dir = sellingMachine->GetDir();

		switch (dir)
		{
		case Front:
			pos.y -= 35;
			break;
		case Right:
			pos.x -= 35;
			break;
		case Back:
			pos.y += 35;
			break;
		case Left:
			pos.x += 35;
			break;
		}
		pos.z += 147;
		item->SetPos(pos);
		sellingMachine->AddItem(item->GetID());

		item->SetObjectPoolState(ObjectPoolState::InWorld);
		item->SetOwnerID(-1);

		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			SendDropItemPacket(item, player->GetID(), item->GetPos(), false, true, p->GetClient());
		}
	}
}

void ServerNetwork::ProcessChangeToolPacket(C_ChangeTool_Packet packet, int clientIndex)
{
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));

	// toolID가 0이면 도구를 들지 않는 것
	if(packet.toolID == 0)
	{
		player->SetCurrentTool(0);

		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			SendUpdateCurrentToolPacket(packet.toolID, packet.playerID, ItemType::None, p->GetClient());
		}
		return;
	}

	// Player 인벤토리에 해당 도구가 존재하는지 확인
	if (player->ExistItem(true, packet.toolID))
	{
		// 도구가 존재하면 해당 도구를 들도록 설정
		player->SetCurrentTool(packet.toolID);
		Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.toolID));
		
		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			SendUpdateCurrentToolPacket(packet.toolID, packet.playerID, item->GetItemType(), p->GetClient());
		}
	}
}

void ServerNetwork::ProcessUseToolPacket(C_UseTool_Packet packet, int clientIndex)
{
	// 요청된 도구가 Player가 들고 있는 도구가 맞는지 확인
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	if (player->GetCurrentTool() == packet.toolID)
	{
		// 도구 사용 처리
		player->SetRotation(packet.playerRotation);
		player->Attack(_clients[clientIndex]->_room);

		// 도구 사용 알리기
		Tool* tool = dynamic_cast<Tool*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.toolID));
		
		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			SendUseToolPacket(packet.playerID, tool->GetItemType(), p->GetClient());
		}
	}
}

void ServerNetwork::ProcessUseKeyPacket(C_UseKey_Packet packet, int clientIndex)
{
	// Player가 열쇠를 정말 가지고 있는지 확인
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	// 가지고 있지 않으면 무시
	if (!player->ExistItem(true, packet.toolID))
		return;

	// 요청한 Door가 닫힌 상태인지 확인
	Door* door = dynamic_cast<Door*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Door, packet.doorID));
	// 이미 열린 상태면 무시
	if (door->GetState() == ObjectState::OPEN)
		return;

	// 요청한 Player가 열쇠를 사용할 수 있는 거리인지 확인
	

	// 사용 가능한 거리라면 Door State 변경
	door->SetState(ObjectState::OPEN);

	// Player 인벤토리에서 열쇠 제거
	Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.toolID));
	player->RemoveItemFromInventory(true, packet.toolID);

	// 해당 Client에게 Item을 인벤토리에서 제거하라고 알림
	SendRemoveItemFromInventoryPacket(item, true, _clients[clientIndex]);
	
	// Broadcast
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		SendUpdateObjectStatePacket(door, p->GetClient());
	}
}

void ServerNetwork::ProcessUseLanternPacket(C_UseLantern_Packet packet, int clientIndex)
{
	// Player가 랜턴을 정말 가지고 있는지 확인
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	// 가지고 있지 않으면 무시
	if (!player->ExistItem(true, packet.lanternID))
		return;

	// 랜턴 배터리 확인
	Lantern* lantern = dynamic_cast<Lantern*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.lanternID));
	// 배터리가 없으면 무시
	if (lantern->GetCurrentBattery() == 0)
		return;

	// 랜턴 작동
	if (lantern->IsOn())
	{
		lantern->TurnOff();
		_clients[clientIndex]->_room->RemoveProcessingItem(lantern->GetID());
	}	
	else
	{
		lantern->TurnOn();
		_clients[clientIndex]->_room->AddProcessingItem(lantern);
	}
}

void ServerNetwork::ProcessInteractDoorPacket(C_InteractDoor_Packet packet, int clientIndex)
{
	// 요청한 Player와 Door가 상호작용 가능 거리인지 확인
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	Door* door = dynamic_cast<Door*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Door, packet.doorID));

	// 거리 확인 코드 추가하기

	// Hatch라면 Base 안쪽에서 상호작용하는 것인지 확인
	if(door->GetDoorType() == DoorType::Hatch)
	{
		const std::vector<CubeRef>& cubes = _clients[clientIndex]->_room->GetCubes();
		// Player가 Base 안에 있지 않다면 무시
		if (!cubes[door->GetOwnerCubeID()]->CheckInclude(player->GetBoundingBox()))
			return;
	}

	// 상호작용 가능하면 Door State 변경
	if (door->GetState() == ObjectState::OPEN)
		door->SetState(ObjectState::CLOSE);
	else
		door->SetState(ObjectState::OPEN);

	// Broadcast
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		SendInteractDoorNotifyPacket(packet.playerID, packet.doorID, door->GetState(), p->GetClient());
	}
}

void ServerNetwork::ProcessSellItemPacket(C_SellItem_Packet packet, int clientIndex)
{
	// 요청한 Player가 판매기와 거리가 되는지 확인 
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	SellingMachine* sellingMachine = dynamic_cast<SellingMachine*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::SellingMachine, packet.sellingMachineID));

	// 판매기가 활성화 상태인지 확인
	if (sellingMachine->GetState() == ObjectState::CLOSE)
		return;

	// 아이템 판매 및 아이템 제거
	int remainCredit = sellingMachine->SellItem(_clients[clientIndex]->_room);
	std::vector<int>& sellItems = sellingMachine->GetSellItems();
	for (auto& itemID : sellItems)
		_clients[clientIndex]->_room->RemoveObject(ObjectType::Item, itemID, false);
		
	// Broadcast
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		SendSellItemResultPacket(player->GetID(), sellingMachine->GetID(), sellingMachine->GetState(), remainCredit, _clients[clientIndex]->_room->GetCollectCredit(), _clients[clientIndex]->_room->GetCurrentCredit(), sellItems, p->GetClient());
	}

	// 데이터 사용을 위해 나중에 초기화
	sellingMachine->ClearSellItems();
}

void ServerNetwork::ProcessBuyItemPacket(C_BuyItem_Packet packet, int clientIndex)
{
	// 요청한 Player가 아이템을 구매할 수 있는 상태인지 확인
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));

	// 구매가 가능한 상태라면 크레딧이 충분한지 확인
	ItemInfo info = g_dataManager->GetItemInfo(packet.itemType);
	int needCredit = info.cost * packet.itemCount;

	// 크레딧이 충분하다면 구매 완료 및 Base에 아이템 생성
	if (_clients[clientIndex]->_room->GetCurrentCredit() >= needCredit)
	{
		for (int i = 0; i < packet.itemCount; ++i)
			_clients[clientIndex]->_room->AddItem(true, packet.itemType, {0, 0, 25});
		
		// 아이템 가격만큼 크레딧 마이너스
		_clients[clientIndex]->_room->MinusCredit(needCredit);
	}

	// 아이템 구매 결과 전송
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		SendBuyItemResultPacket(_clients[clientIndex]->_room->GetCurrentCredit(), p->GetClient());
	}
}

void ServerNetwork::ProcessChangeEmotionPacket(C_ChangeEmotion_Packet packet, int clientIndex)
{
	// 바뀐 감정 기록
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	player->SetCurrentEmotion(packet.emotion);
	
	if (packet.emotion == Emotion::Fear)
	{
		_clients[clientIndex]->_room->AddFearCount();
		player->AddFearCount();
	}
	
	if (packet.emotion == Emotion::Surprise)
		_clients[clientIndex]->_room->AddSurpriseCount();

	if (packet.emotion == Emotion::Sad)
		_clients[clientIndex]->_room->AddSadCount();
}

void ServerNetwork::ProcessEmotionResultPacket(C_EmotionResult_Packet packet, int clientIndex)
{
}

void ServerNetwork::ProcessStartStagePacket(C_StartStage_Packet packet, int clientIndex)
{
	// 게임 시작을 요청한 Client가 소속한 방이 없다면 무시
	if (!_clients[clientIndex]->_room)
		return;

	// 방의 State가 게임 진행중이면 무시
	if (_clients[clientIndex]->_room->GetRoomState() == RoomState::Play)
		return;

	// 방에 있는 모든 Player에게 게임 시작을 알림
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (p->GetClient())
			SendStartStagePacket(p->GetClient());
	}
	
	_clients[clientIndex]->_room->StartStage();
}

void ServerNetwork::ProcessEndStagePacket(C_EndStage_Packet packet, int clientIndex)
{
	// 게임 종료를 요청한 Client가 소속한 방이 없다면 무시
	if (!_clients[clientIndex]->_room)
		return;

	// 방에 있는 모든 Player에게 게임 종료를 알림
	for (auto& p : _clients[clientIndex]->_room->GetPlayers())
	{
		if (p->GetClient())
			SendEndStagePacket(p->GetClient());
	}

	_clients[clientIndex]->_room->EndStage();
}

void ServerNetwork::ProcessSubmitItemPacket(C_SubmitItem_Packet packet, int clientIndex)
{
	// 제출하려는 아이템과 대응되는 퀘스트가 있는지 확인
	Item* item = dynamic_cast<Item*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Item, packet.itemID));
	Quest* quest = _clients[clientIndex]->_room->IsNeedForQuest(item->GetItemType());
	
	// 없다면 무시
	if (!quest)
		return;

	// 대응되는 퀘스트가 있다면, Player 인벤토리에서 아이템 제거
	Player* player = dynamic_cast<Player*>(_clients[clientIndex]->_room->GetGameObject(ObjectType::Player, packet.playerID));
	// 아이템이 제대로 제거되었다면
	if (player->RemoveItemFromInventory(false, packet.itemID))
	{
		// 아이템 제거 및 퀘스트 진행 상황 업데이트
		_clients[clientIndex]->_room->RemoveObject(ObjectType::Item, packet.itemID, false);
		quest->AddCollectCount();

		// 아이템을 제출한 Player에게 인벤토리에서 아이템 제거 알림
		SendRemoveItemFromInventoryPacket(item, false, player->GetClient());

		// Broadcast
		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (p->GetClient())
				SendUpdateQuestProgressPacket(quest, quest == _clients[clientIndex]->_room->GetMainQuest(), p->GetClient());
		}
	}
}

void ServerNetwork::ProcessRequestQuestRewardPacket(C_RequestQuestReward_Packet packet, int clientIndex)
{
	Quest* quest;
	if(packet.isMain)
		quest = _clients[clientIndex]->_room->GetMainQuest();
	else
		quest = _clients[clientIndex]->_room->GetSubQuest();
	
	if (quest->IsClear())
	{
		// 보상 지급
		switch (quest->GetRewardType())
		{
		case RewardType::Item:
		{
			bool isTool = false;
			switch (quest->GetRewardItemType())
			{
			case ItemType::CUTLASS:
			case ItemType::Blaster:
			case ItemType::Key:
			case ItemType::LANTERN:
				isTool = true;
				break;
			}

			for (int i = 0; i < quest->GetRewardAmount(); ++i)
				_clients[clientIndex]->_room->AddItem(isTool, quest->GetRewardItemType(), { 0, 0, 25 });
			break;
		}
		case RewardType::Credit:
			_clients[clientIndex]->_room->PlusCredit(quest->GetRewardAmount());
			break;
		case RewardType::Hp:
			for (auto& p : _clients[clientIndex]->_room->GetPlayers())
			{
				if (p->GetClient() && p->GetState() != ObjectState::DEAD)
				{
					p->TackHeal(quest->GetRewardAmount());
					SendUpdateHpPacket(p->GetID(), p->GetHP(), p->GetClient());
				}
			}
			break;
		}

		// 퀘스트 업데이트
		quest->UpdateQuest();

		for (auto& p : _clients[clientIndex]->_room->GetPlayers())
		{
			if (p->GetClient())
				SendUpdateQuestPacket(quest, packet.isMain, _clients[clientIndex]);
		}
	}
}

void ServerNetwork::ProcessVoiceDataPacket(C_VoiceData_Packet packet, ExpOver* expOver)
{
	if (packet.clientID < 0 || packet.clientID >= MAX_CLIENT)
		return;

	if (!_clients[packet.clientID]->_isConnected || !_clients[packet.clientID]->_room || !_clients[packet.clientID]->_player)
		return;

	// 살아있는 Player와 죽어있는 Player 통신 따로 하기
	bool isDead = _clients[packet.clientID]->_player->GetState() == ObjectState::DEAD;
	for (auto& player : _clients[packet.clientID]->_room->GetPlayers())
	{
		if (player->GetClient() && isDead == (player->GetState() == ObjectState::DEAD))
			SendVoiceDataPacket(packet.playerID, packet.sequenceNumber, packet.audioData, expOver);
	}
}