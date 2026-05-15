#include "pch.h"
#include "ServerNetwork.h"
#include "ServerFramework.h"
#include "Session.h"
#include "ExpOver.h"
#include "Room.h"

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
		std::cout << "bind 실패" << std::endl;
		return;
	}

	// listen
	if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "listen 실패" << std::endl;
		return;
	}

	// iocp port 생성
	_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// listenSocket 등록
	CreateIoCompletionPort((HANDLE)_listenSocket, _iocp, 0, 0);

	// accept
	_tempSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	_acceptOver._ioType = IOType::Accept;
	AcceptEx(_listenSocket, _tempSocket, _acceptOver._buffer.data(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &_acceptOver._over);

	for (int i = 0; i < MAX_PLAYER; ++i)
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
	GetQueuedCompletionStatus(_iocp, &numByte, &key, &over, INFINITE);
	
	if (over == nullptr)
	{
		if (key == -1)
			exit(-1);

		ProcessDisconnected(static_cast<int>(key));
		
		std::cout << "client[" << key << "] 접속 종료\n";
		_clients[key]->_isConnected = false;
		closesocket(_clients[key]->_clientSocket);
		_clients[key]->_clientSocket = INVALID_SOCKET;
		_clients[key]->_room->RemoveObject(ObjectType::Player, _clients[key]->_player->GetID());
		return;
	}

	ExpOver* expOver = reinterpret_cast<ExpOver*>(over);
	switch (expOver->_ioType)
	{
	case IOType::Accept:
		ProcessAccept();
		break;
	case IOType::Recv:
		printf("ID[%lld]로부터 %d 바이트 받음\n", key, numByte);
		ProcessRecv(static_cast<int>(key), numByte, expOver);
		break;
	case IOType::Send:
	{
		ExpOver* o = reinterpret_cast<ExpOver*>(over);
		delete o;
		break;
	}	
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
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		if (!_clients[i]->_isConnected)
		{
			clientIndex = i;
			break;
		}
	}

	// 할당할 수 있는 Client Session이 없다면 로그인 실패 패킷 전송
	if (clientIndex == -1)
	{
		// 로그인 실패 패킷 전송
		return;
	}

	std::cout << "Client 접속" << std::endl;

	// clientSocket 등록
	CreateIoCompletionPort((HANDLE)_tempSocket, _iocp, clientIndex, 0);
	_clients[clientIndex]->_clientSocket = _tempSocket;
	_clients[clientIndex]->_id = clientIndex;
	_clients[clientIndex]->_isConnected = true;
	_clients[clientIndex]->_prevRecv = 0;
	
	// 나중에 nullptr로 초기화하기
	_clients[clientIndex]->_room = _framework->GetRoom();

	// 나중에 이 부분은 Room에 들어간 후 처리하는 것으로 변경할 것
	{
		// 나중에 nullptr로 초기화하기
		// 새로 접속한 Client를 나타낼 Player 생성
		_clients[clientIndex]->_player = _clients[clientIndex]->_room->AddPlayer();
		_clients[clientIndex]->_player->SetClient(_clients[clientIndex]);

		// 새로 접속한 Client에게 자신을 나타낼 Player 정보 전송
		SendAddPlayerPacket(_clients[clientIndex]->_player, _clients[clientIndex]);

		// 새로 접속한 Client에게 기존에 있던 Player 정보 전송
		for (auto& player : _clients[clientIndex]->_room->GetPlayers())
		{
			if (!player->GetClient())
				continue;

			// 자기 자신 제외
			if (_clients[clientIndex]->_player == player)
				continue;  

			SendAddPlayerPacket(player, _clients[clientIndex]);
		}
	}

	_clients[clientIndex]->Recv();

	// accept 다시 걸기
	_tempSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	_acceptOver._ioType = IOType::Accept;
	AcceptEx(_listenSocket, _tempSocket, _acceptOver._buffer.data(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &_acceptOver._over);
}

void ServerNetwork::ProcessDisconnected(int clientIndex)
{

}

void ServerNetwork::ProcessRecv(int clientIndex, int numByte, ExpOver* expOver)
{
	// Client 접속 종료
	if (numByte == 0)
	{
		std::cout << "client[" << clientIndex << "] 접속 종료\n";
		_clients[clientIndex]->_isConnected = false;
		closesocket(_clients[clientIndex]->_clientSocket);
		_clients[clientIndex]->_clientSocket = INVALID_SOCKET;
		_clients[clientIndex]->_room->RemoveObject(ObjectType::Player, _clients[clientIndex]->_player->GetID());
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

void ServerNetwork::ProcessPacket(std::vector<char>& packet, int clientIndex)
{
	// packetID 추출
	PacketID id;
	memcpy(&id, packet.data() + sizeof(char), sizeof(PacketID));

	switch (id)
	{
	case C_Move:
	{
		C_Move_Packet movePacket;
		memcpy(&movePacket, packet.data(), sizeof(C_Move_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_Move_Packet));
		ProcessMovePacket(movePacket, clientIndex);
	}
	break;
	case C_UpdateObjectState:
	{
		C_UpdateObjectState_Packet updateObjectPacket;
		memcpy(&updateObjectPacket, packet.data(), sizeof(C_UpdateObjectState_Packet));
		packet.erase(packet.begin(), packet.begin() + sizeof(C_UpdateObjectState_Packet));
		ProcessUpdateObjectStatePacket(updateObjectPacket, clientIndex);
	}
	break;


	/*case C_GetItem:
		C_GetItem_Packet getItemPacket;
		memcpy(&getItemPacket, packet.data() + sizeof(Header), sizeof(C_GetItem_Packet));
		ProcessGetItemPacket(client->socket, getItemPacket);
		break;
	case C_DropItem:
		C_DropItem_Packet dropItemPacket;
		memcpy(&dropItemPacket, packet.data() + sizeof(Header), sizeof(C_DropItem_Packet));
		ProcessDropItemPacket(dropItemPacket);
		break;
	case C_ChangeTool:
		C_ChangeTool_Packet changeToolPacket;
		memcpy(&changeToolPacket, packet.data() + sizeof(Header), sizeof(C_ChangeTool_Packet));
		ProcessChangeToolPacket(changeToolPacket);
		break;
	case C_UseTool:
		C_UseTool_Packet useToolPacket;
		memcpy(&useToolPacket, packet.data() + sizeof(Header), sizeof(C_UseTool_Packet));
		ProcessUseToolPacket(useToolPacket);
		break;
	case C_InteractDoor:
		C_InteractDoor_Packet interactDoorPacket;
		memcpy(&interactDoorPacket, packet.data() + sizeof(Header), sizeof(C_InteractDoor_Packet));
		ProcessInteractDoorPacket(interactDoorPacket);
		break;
	case C_Emotion:
		C_Emotion_Packet emotionPacket;
		memcpy(&emotionPacket, packet.data() + sizeof(Header), sizeof(C_Emotion_Packet));
		ProcessEmotionPacket(emotionPacket);
		break;
	case C_UseLantern:
		C_UseLantern_Packet useLanternPacket;
		memcpy(&useLanternPacket, packet.data() + sizeof(Header), sizeof(C_UseLantern_Packet));
		ProcessUseLanternPacket(useLanternPacket);
		break;
	case C_StartStage:
		C_StartStage_Packet startStagePacket;
		memcpy(&startStagePacket, packet.data() + sizeof(Header), sizeof(C_StartStage_Packet));
		ProcessStartStagePacket(startStagePacket);
		break;
	case C_EndStage:
		C_EndStage_Packet endStagePacket;
		memcpy(&endStagePacket, packet.data() + sizeof(Header), sizeof(C_EndStage_Packet));
		ProcessEndStagePacket(endStagePacket);
		break;*/
	}
}

template<class T>
std::vector<char> ServerNetwork::SerializePOD(const T& pod)
{
	std::vector<char> serializedData(sizeof(pod));
	memcpy(serializedData.data(), &pod, sizeof(pod));

	return serializedData;
}

void ServerNetwork::SendAddPlayerPacket(Player* player, Session* client)
{
	// Packet Data 생성
	S_AddPlayer_Packet packetData{ sizeof(S_AddPlayer_Packet), S_AddPlayer, player->GetID(), player->GetPos(), player->GetRotation() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	client->Send(serializedPacketData);
}

void ServerNetwork::SendRemoveObjectPacket(ObjectType objectType, int objectID, Session* client)
{
	// Packet Data 생성
	S_RemoveObject_Packet packetData{ sizeof(S_RemoveObject_Packet), S_RemoveObject, objectType, objectID };

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

void ServerNetwork::ProcessMovePacket(C_Move_Packet packet, int clientIndex)
{
	GameObject* object = _clients[clientIndex]->_room->GetPlayer(packet.type, packet.id);

	if (object == nullptr)
		return;

	object->SetPos(packet.pos);
	object->SetRotation(packet.rotation);
	object->SetState(packet.state);

	// 자신을 제외한 모든 Client들에게 알리기
	for (auto& player : _clients[clientIndex]->_room->GetPlayers())
	{
		if (!player->GetClient())
			continue;

		// 자기 자신 제외
		if (_clients[clientIndex]->_player == player)
			continue;

		SendMovePacket(object, player->GetClient());
	}
}

void ServerNetwork::ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet, int clientIndex)
{
	GameObject* object = _clients[clientIndex]->_room->GetPlayer(packet.type, packet.id);

	object->SetState(packet.state);

	// 자신을 제외한 모든 클라이언트에게 알리기
	for (auto& player : _clients[clientIndex]->_room->GetPlayers())
	{
		if (player->GetClient()->_isConnected)
			continue;

		// 자기 자신 제외
		if (_clients[clientIndex]->_player == player)
			continue;

		SendUpdateObjectStatePacket(object, _clients[clientIndex]);
	}
}