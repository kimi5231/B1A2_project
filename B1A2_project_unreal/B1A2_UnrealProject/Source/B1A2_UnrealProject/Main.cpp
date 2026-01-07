#include "Main.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "NetworkRecvRunnable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "OtherPlayer.h"

SOCKET _clientSocket;

#define BUFSIZE	64

void UMain::Init()
{
	Super::Init();
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

void UMain::ConnectServer()
{
	WSADATA wsa;

	// 윈속 초기화
	int retval = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (retval != 0)
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
	retval = connect(_clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (retval == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket Error..."));
		return;
	}

	if (_clientSocket != INVALID_SOCKET)
	{
		_recvRunnable = new NetworkRunnable(this);
		_recvThread = FRunnableThread::Create(_recvRunnable, TEXT("RecvThread"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Server Connected!"));
}

TArray<uint8> UMain::CreatePacket(PacketID id, const void* packetData, int dataSize)
{
	TArray<uint8> retPacket;

	// 헤더
	Header header;
	header.id = id;
	header.dataSize = (int16)dataSize;

	// 전체 패킷 크기 계산
	int32 totalSize = sizeof(Header) + dataSize;

	retPacket.SetNumUninitialized(totalSize);
	
	// 패킷에 데이터 넣기
	FMemory::Memcpy(retPacket.GetData(), &header, sizeof(Header));
	FMemory::Memcpy(retPacket.GetData() + sizeof(Header), packetData, dataSize);

	return retPacket;
}

void UMain::ProcessSend(PacketID id, const void* packetData, int dataSize)
{
	// 패킷 생성
	TArray<uint8> sendPacket = CreatePacket(id, packetData, dataSize);
	
	int32 retval;
	int32 packetSize = sendPacket.Num(); 

	// 고정 길이 데이터 전송
	retval = send(_clientSocket, reinterpret_cast<const char*>(&packetSize), sizeof(int32), 0);
	if (retval == SOCKET_ERROR)
		return;

	// 가변 길이 데이터 전송
	retval = send(_clientSocket, reinterpret_cast<const char*>(sendPacket.GetData()), packetSize, 0);
	if (retval == SOCKET_ERROR)
		return;
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
		S_AddObject_Packet addObjectPacket;
		FMemory::Memcpy(&addObjectPacket, packet.GetData() + sizeof(Header), sizeof(S_AddObject_Packet));
		RecvAddObject(addObjectPacket);
		break;
	case S_CreateGameRoom:
		S_CreateGameRoom_Packet createGameRoomPacket;
		FMemory::Memcpy(&createGameRoomPacket, packet.GetData() + sizeof(Header), sizeof(S_CreateGameRoom_Packet));
		RecvCreateGameRoom(createGameRoomPacket);
		break;
	case S_Move:
		S_Move_Packet movePacket;
		FMemory::Memcpy(&movePacket, packet.GetData() + sizeof(Header), sizeof(S_Move_Packet));
		RecvMovePlayer(movePacket.objectID, movePacket.pos, movePacket.rotation);
		//UE_LOG(LogTemp, Warning, TEXT("Other Player Moved... [%d] %f, %f, %f"), movePacket.objectID, movePacket.pos.x, movePacket.pos.y, movePacket.pos.z);
		break;
	}
}

void UMain::RecvAddObject(S_AddObject_Packet addObjectPacket)
{

	if (_myID == 0)
	{	
		// 자신의 ID 설정
		_myID = addObjectPacket.objectID;

		// Spawn
		AsyncTask(ENamedThreads::GameThread, [=, this]()
		{
			UWorld* world = GetWorld();
			if (!world) return;

			FVector spawnLocation(addObjectPacket.pos.x, addObjectPacket.pos.y, addObjectPacket.pos.z);
			FRotator spawnRotation(0, addObjectPacket.rotation.yaw, 0);

			auto playerController = UGameplayStatics::GetPlayerController(this, 0);
			AMyPlayer* player = Cast<AMyPlayer>(playerController->GetPawn());
			
			if (!player)
				return;

			_myPlayer = player;

			UE_LOG(LogTemp, Log, TEXT("My Player Spawned! [%d], %f, %f, %f"), addObjectPacket.objectID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		});
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

	// 다른 플레이어 Spawn
	FVector spawnLocation(addObjectPacket.pos.x, addObjectPacket.pos.y, addObjectPacket.pos.z);
	FRotator spawnRotation(0, 0, 0);	// 일단 0으로 설정
	int id = addObjectPacket.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world || !OtherPlayerClass)
			return;

		AOtherPlayer* player = world->SpawnActor<AOtherPlayer>(OtherPlayerClass, spawnLocation, spawnRotation);
		
		if (player)
		{
			_otherPlayers.Add(id, player);
			UE_LOG(LogTemp, Log, TEXT("Other Player Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}
		else
		{
			_otherPlayers.Remove(id);
			UE_LOG(LogTemp, Error, TEXT("Other Spawn Failed... ID [%d]"), id);
		}

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
	if (id == _myID)
	{
		UE_LOG(LogTemp, Warning, TEXT("ID %d is MyID. Ignore."), id);
		return;
	}

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		AOtherPlayer** findPlayer = _otherPlayers.Find(id);
		if (!findPlayer)
		{
			UE_LOG(LogTemp, Error, TEXT("Other Player [%d] not in _otherPlayers"), id);
			return;
		}

		AOtherPlayer* player = (*findPlayer);

		FVector pos(location.x, location.y, location.z);
		FRotator rot(0, rotation.yaw, 0);
		player->SetPlayerLocation(pos, rot);
		//UE_LOG(LogTemp, Display, TEXT("Other Player [%d] SetPlayerLocation!!!"), id);
	});
}
