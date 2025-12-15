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
	stServerAddr.sin_port = htons(9000);
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
		_networkRunnable = new NetworkRunnable(
			_clientSocket,
			_receivedQueue, // Output Queue
			_sendQueue      // Input Queue
		);

		_networkThread = FRunnableThread::Create(_networkRunnable, TEXT("NetworkRecvSendThread"));

		// 패킷 처리 함수 주기적 호출 - ProcessRecv
		GetWorld()->GetTimerManager().SetTimer(
			_packetProcessTimerHandle,
			this,
			&UMain::ProcessRecv,
			0.016f,
			true
		);

		// 위치 송신 함수 주기적 호출 - SendMyPosition
		GetWorld()->GetTimerManager().SetTimer(
			_sendPositionTimerHandle,
			this,
			&UMain::SendLocalPosition,
			0.05f,
			true
		);
	}
}

void UMain::Shutdown()
{
	closesocket(_clientSocket);
	UE_LOG(LogTemp, Log, TEXT("Connection Closed..."));

	WSACleanup();

	Super::Shutdown();
}

void UMain::GameTick()
{
	// Recv 패킷 처리
	ProcessRecv();
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
	TArray<uint8> SendPacket = CreatePacket(id, packetData, dataSize);
	int32 PacketSize = SendPacket.Num(); // 이 값(전체 패킷 크기)을 먼저 보냄

	TArray<uint8> SizeBuffer;
	SizeBuffer.SetNumUninitialized(sizeof(int32));
	FMemory::Memcpy(SizeBuffer.GetData(), &PacketSize, sizeof(int32));

	// 고정 길이 데이터
	_sendQueue.Enqueue({ SizeBuffer });
	// 가변 길이 데이터
	_sendQueue.Enqueue({ SendPacket });

	return true;
}

void UMain::SendLocalPosition()
{
	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* PlayerController = world->GetFirstPlayerController();
	APawn* playerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;

	C_Move_Packet movePacket;
	movePacket.objectID = _myID;
	movePacket.pos = playerPawn->GetActorLocation();
	movePacket.rotation = playerPawn->GetActorRotation();
	
	// queue에 넣음
	ProcessSend(PacketID::C_Move, &movePacket, sizeof(C_Move_Packet));
}

void UMain::ProcessRecv()
{
	RecvData receivedData;

	// 큐에서 데이터를 가져옵니다. (데이터가 있으면 true 반환)
	while (_receivedQueue.Dequeue(receivedData))
	{
		const TArray<uint8>& PacketBuffer = receivedData.DataBuffer;

		if (PacketBuffer.Num() < sizeof(Header))
		{
			UE_LOG(LogTemp, Warning, TEXT("Received packet is too small: %d bytes"), PacketBuffer.Num());
			continue;
		}

		// Header 추출
		Header NetHeader;
		FMemory::Memcpy(&NetHeader, PacketBuffer.GetData(), sizeof(Header));

		const uint8* DataPtr = PacketBuffer.GetData() + sizeof(Header);

		int32 ExpectedTotalSize = sizeof(Header) + NetHeader.dataSize;
		if (PacketBuffer.Num() != ExpectedTotalSize)
		{
			UE_LOG(LogTemp, Error, TEXT("Packet size mismatch. Received: %d, Expected: %d (Data Size: %d)"),
				PacketBuffer.Num(), ExpectedTotalSize, NetHeader.dataSize);
			continue;
		}

		switch (NetHeader.id)
		{
			case S_AddObject:
			{
				if (NetHeader.dataSize == sizeof(S_AddObject_Packet))
				{
					S_AddObject_Packet addObjectPacket;
					FMemory::Memcpy(&addObjectPacket, DataPtr, sizeof(S_AddObject_Packet));
					RecvAddObject(addObjectPacket.objectID, addObjectPacket.initialLocation, addObjectPacket.initialRotaion);
				}
				break;
			}
			case S_Move:
			{
				if (NetHeader.dataSize == sizeof(S_Move_Packet))
				{
					S_Move_Packet movePacket;
					FMemory::Memcpy(&movePacket, DataPtr, sizeof(S_Move_Packet));
					RecvMovePlayer(movePacket.objectID, movePacket.pos, movePacket.rotation);
				}
				break;
			}
		}
	}
}

void UMain::RecvAddObject(int id, FVector initLocation, FRotator initRotation)
{
	// 이미 존재하는 객체인지 확인
	if (_otherPlayers.Contains(id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add existing object ID: %d"), id);
		return;
	}

	//UWorld* World = GetWorld();
	//if (!World || !RemotePlayerCharacterClass) return;

	//// 스폰
	//FActorSpawnParameters SpawnParams;
	//ACharacter* NewPlayer = World->SpawnActor<ACharacter>(
	//	RemotePlayerCharacterClass,
	//	initLocation,
	//	initRotation,
	//	SpawnParams
	//);

	//if (NewPlayer)
	//{
	//	_otherPlayers.Add(id, NewPlayer);
	//	UE_LOG(LogTemp, Log, TEXT("Player spawned with ID: %d at %s"), id, *initLocation.ToString());
	//}
}

void UMain::RecvMovePlayer(int id, FVector location, FRotator rotation)
{
}
