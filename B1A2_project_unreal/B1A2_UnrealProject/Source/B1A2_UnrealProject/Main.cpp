#include "Main.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "NetworkRecvRunnable.h"

SOCKET _clientSocket;

#define BUFSIZE	64

void UMain::Init()
{
	Super::Init();

	WSADATA wsa;

	// 윈속 초기화
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (nRet != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("WSAStartup Failed..."));
		return;
	}

	// 소켓 생성
	_clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// socket -> WSASocket
	if (_clientSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Socket..."));
		return;
	}

	SOCKADDR_IN stServerAddr;
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(7777);
	stServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// connect
	nRet = connect(_clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket Error..."));
		return;
	}

	if (_clientSocket != INVALID_SOCKET)
	{
		_recvRunnable = new NetworkRunnable(this);
		_recvThread = FRunnableThread::Create(_recvRunnable, TEXT("RecvThread"));
	}
}

void UMain::Shutdown()
{
	if (_recvRunnable)
		_recvRunnable->Stop();

	if (_recvThread)
	{
		_recvThread->WaitForCompletion();
		delete _recvThread;
		_recvThread = nullptr;
	}

	delete _recvRunnable;
	_recvRunnable = nullptr;

	closesocket(_clientSocket);
	UE_LOG(LogTemp, Log, TEXT("Connection Closed..."));

	WSACleanup();

	Super::Shutdown();
}

TArray<uint8> UMain::CreatePacket(PacketID id, const void* packetData, int dataSize)
{
	TArray<uint8> RetBuffer;

	Header NetHeader;
	NetHeader.id = id;
	NetHeader.dataSize = (int16)dataSize;

	// 전체 패킷 크기 계산
	int32 TotalPacketSize = sizeof(Header) + dataSize;

	RetBuffer.SetNumUninitialized(TotalPacketSize);
	FMemory::Memcpy(RetBuffer.GetData(), &NetHeader, sizeof(Header));
	FMemory::Memcpy(RetBuffer.GetData() + sizeof(Header), packetData, dataSize);

	return RetBuffer;
}

bool UMain::ProcessSend(PacketID id, const void* packetData, int dataSize)
{
	//TArray<uint8> SendPacket = CreatePacket(id, packetData, dataSize);
	//int32 PacketSize = SendPacket.Num(); // 이 값(전체 패킷 크기)을 먼저 보냄

	//TArray<uint8> SizeBuffer;
	//SizeBuffer.SetNumUninitialized(sizeof(int32));
	//FMemory::Memcpy(SizeBuffer.GetData(), &PacketSize, sizeof(int32));

	//// 고정 길이 데이터
	//_sendQueue.Enqueue({ SizeBuffer });
	//// 가변 길이 데이터
	//_sendQueue.Enqueue({ SendPacket });

	return true;
}

void UMain::SendLocalPosition()
{
	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* PlayerController = world->GetFirstPlayerController();
	APawn* playerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;

	// 자료형 변환
	Vector pos;
	pos.x = (float)playerPawn->GetActorLocation().X;
	pos.y = (float)playerPawn->GetActorLocation().Y;
	pos.z = (float)playerPawn->GetActorLocation().Z;
	
	Rotation rot;
	rot.pitch = (float)playerPawn->GetActorRotation().Pitch;
	rot.yaw = (float)playerPawn->GetActorRotation().Yaw;
	rot.roll = (float)playerPawn->GetActorRotation().Roll;

	C_Move_Packet movePacket;
	movePacket.objectID = _myID;
	movePacket.pos = pos;
	movePacket.rotation = rot;

	// queue에 넣음
	ProcessSend(PacketID::C_Move, &movePacket, sizeof(C_Move_Packet));
}

void UMain::Update()
{
	ProcessRecv();
}

void UMain::ProcessRecv()
{
	int packetSize = 0;
	int ret = recv(_clientSocket, (char*)&packetSize, sizeof(int), MSG_WAITALL);
	if (ret <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("recv packetSize failed"));
		return;
	}

	constexpr int MAX_PACKET_SIZE = 4096;

	if (packetSize <= 0 || packetSize > MAX_PACKET_SIZE)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid packetSize: %d"), packetSize);
		return;
	}

	if (packetSize < sizeof(Header))
	{
		UE_LOG(LogTemp, Error, TEXT("Packet too small for Header"));
		return;
	}

	TArray<uint8> packet;
	packet.SetNumUninitialized(packetSize);

	ret = recv(_clientSocket, (char*)packet.GetData(), packetSize, MSG_WAITALL);
	if (ret <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("recv packet failed"));
		return;
	}

	Header header;
	FMemory::Memcpy(&header, packet.GetData(), sizeof(Header));

	// Data
	switch (header.id)
	{
	case S_AddObject:
		UE_LOG(LogTemp, Warning, TEXT("Original AddObject Packet Size  = %d"), sizeof(S_AddObject_Packet));
		UE_LOG(LogTemp, Warning, TEXT("AddObject Header Size  = %d"), sizeof(Header));
		UE_LOG(LogTemp, Warning, TEXT("AddObject Packet Size = %d"), packetSize);

		S_AddObject_Packet addObjectPacket;
		//memcpy(&addObjectPacket, packet.data() + sizeof(Header), sizeof(S_AddObject_Packet));
		FMemory::Memcpy(&addObjectPacket, packet.GetData() + sizeof(Header), sizeof(S_AddObject_Packet));
		RecvAddObject(addObjectPacket);
		break;
	case S_CreateGameRoom:
		UE_LOG(LogTemp, Warning, TEXT("Original CreateGameRoom Packet Size  = %d"), sizeof(S_CreateGameRoom_Packet));
		UE_LOG(LogTemp, Warning, TEXT("CreateGameRoom Header Size  = %d"), sizeof(Header));
		UE_LOG(LogTemp, Warning, TEXT("CreateGameRoom Packet Size = %d"), packetSize);

		S_CreateGameRoom_Packet createGameRoomPacket;
		//memcpy(&createGameRoomPacket, packet.data() + sizeof(Header), sizeof(S_CreateGameRoom_Packet));
		FMemory::Memcpy(&createGameRoomPacket, packet.GetData() + sizeof(Header), sizeof(S_CreateGameRoom_Packet));
		RecvCreateGameRoom(createGameRoomPacket);
		break;
	case S_Move:
		S_Move_Packet movePacket;
		FMemory::Memcpy(&movePacket, packet.GetData() + sizeof(Header), sizeof(S_Move_Packet));
		RecvMovePlayer(movePacket.objectID, movePacket.pos, movePacket.rotation);
		break;
	}
}

void UMain::RecvAddObject(S_AddObject_Packet addObjectPacket)
{
	// 자신의 ID 설정
	if (_myID == 0)
	{
		_myID = addObjectPacket.objectID;
		return;
	}

	if (addObjectPacket.objectID == _myID)
		return;

	// 이미 존재하는 객체인지 확인
	if (_otherPlayers.Contains(addObjectPacket.objectID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add existing object ID: %d"), addObjectPacket.objectID);
		return;
	}

	FVector spawnLocation(addObjectPacket.pos.x, addObjectPacket.pos.y, addObjectPacket.pos.z);
	FRotator spawnRotation(addObjectPacket.rotation.pitch, addObjectPacket.rotation.yaw, addObjectPacket.rotation.roll);
	int id = addObjectPacket.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world || !OtherPlayerClass)
			return;

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACharacter* newPlayer = world->SpawnActor<ACharacter>(OtherPlayerClass, spawnLocation, spawnRotation, spawnParams);

		if (!newPlayer)
			return;

		_otherPlayers.Add(id, newPlayer);

		UE_LOG(LogTemp, Log, TEXT("Other Player ID = %d"), id);
	});
} 

void UMain::RecvCreateGameRoom(S_CreateGameRoom_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [this, packet]()
	{
		UWorld* world = GetWorld();
		if (!world || !GameRoomClass)
			return;

		const GameRoomInfo* rooms[5] = { &packet.room1, &packet.room2, &packet.room3, &packet.room4, &packet.room5 };

		for (int i = 0; i < 5; ++i)
		{
			const GameRoomInfo& room = *rooms[i];

			UE_LOG(LogTemp, Warning, TEXT("Room[%d] pos = %f, %f, %f, type = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type);

			FVector pos(room.pos.x, room.pos.y, room.pos.z);
			FVector size(room.size.x, room.size.y, room.size.z);
			FVector scale = size / 100.f;

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AStaticMeshActor* roomActor = world->SpawnActor<AStaticMeshActor>(GameRoomClass, pos, FRotator::ZeroRotator, params);

			if (!roomActor)
				continue;

			// roomActor->GetStaticMeshComponent()->SetWorldScale3D(scale);
		}
	});
}

void UMain::RecvMovePlayer(int id, Vector location, Rotation rotation)
{
}
