#include "Main.h"
#include "NetworkRecvRunnable.h"
#include "EmotionExtractionRunnable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "OtherPlayer.h"
#include "Network/GameNetwork.h"
#include "BaseItem.h"

#define BUFSIZE	64

void UMain::Init()
{
	Super::Init();

	// 시작할 때 카메라 연결
	// ConnectOpenCV();
}

void UMain::Shutdown()
{
	// OpenCV 스레드
	if (_emotionExtractionThread)
	{
		_emotionExtractionRunnable->Stop();
		_emotionExtractionThread->WaitForCompletion();
		delete _emotionExtractionThread;
		_emotionExtractionThread = nullptr;
	}

	// GameNetwork
	if (_gameNetwork)
	{
		_gameNetwork->~GameNetwork();
	}
	
	// Recv 스레드
	if (_recvThread)
	{
		_recvRunnable->Stop();
		_recvThread->WaitForCompletion();
		delete _recvThread;
		_recvThread = nullptr;
	}

	Super::Shutdown();
}

void UMain::ConnectServer()
{
	_gameNetwork = new GameNetwork();

	_recvRunnable = new NetworkRunnable(this);
	_recvThread = FRunnableThread::Create(_recvRunnable, TEXT("RecvThread"));
}

void UMain::ConnectOpenCV()
{
	_emotionExtractionRunnable = new EmotionExtractionRunnable(this);
	_emotionExtractionThread = FRunnableThread::Create(_emotionExtractionRunnable, TEXT("EmotionExtractionThread"));

	_emotionExtractionRunnable->Init();
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
}

void UMain::SendLocalPosition()
{
	if (_myID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* PlayerController = world->GetFirstPlayerController();
	APawn* playerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;

	if (playerPawn)
	{
		// 자료형 변환
		Vector pos;
		pos.x = (float)playerPawn->GetActorLocation().X;
		pos.y = (float)playerPawn->GetActorLocation().Y;
		pos.z = (float)playerPawn->GetActorLocation().Z;

		Rotation rot;
		rot.pitch = (float)playerPawn->GetActorRotation().Pitch;
		rot.yaw = (float)playerPawn->GetActorRotation().Yaw;
		rot.roll = (float)playerPawn->GetActorRotation().Roll;

		// 상태 
		ObjectState state = ObjectState::IDLE;
		if (ACharacter* character = Cast<ACharacter>(playerPawn))
		{
			if (character->GetCharacterMovement()->IsFalling())
			{
				state = ObjectState::JUMP;
			}
			else
			{
				const float Speed = character->GetVelocity().Size();

				if (Speed > 10.f)
					state = ObjectState::RUN;
				else
					state = ObjectState::IDLE;
			}
		}
		else
		{
			const float Speed = playerPawn->GetVelocity().Size();
			state = (Speed > 10.f) ? ObjectState::RUN : ObjectState::IDLE;
		}

		_gameNetwork->SendMovePacket(ObjectType::Player, _myID, pos, rot, state);
	}
}

void UMain::SendGetItem(int itemID, int playerID)
{
	if (_myID == 0 || itemID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world) return;

	_gameNetwork->SendGetItemPacket(itemID, playerID);
}

void UMain::Update()
{
	if (!_gameNetwork)
	{
		UE_LOG(LogTemp, Error, TEXT("_gameNetwork is null"));
		return;
	}

	_gameNetwork->Update();

	ProcessRecv();
}

void UMain::ProcessRecv()
{
	if (!_gameNetwork)
	{
		UE_LOG(LogTemp, Error, TEXT("_gameNetwork is null"));
		return;
	}

	std::vector<NetworkEventRef>& recvEvents = _gameNetwork->GetRecvEvents();

	for (NetworkEventRef event : recvEvents)
	{
		switch (event->packetID)
		{
		case S_AddObject:
			S_AddObject_Packet addObjectPacket;
			FMemory::Memcpy(&addObjectPacket, event->serializedPacketData.data(), sizeof(S_AddObject_Packet));
			RecvAddObject(addObjectPacket);
			event->isComplete = true;
			break;
		case S_AddItem:
			S_AddItem_Packet addItemPacket;
			FMemory::Memcpy(&addItemPacket, event->serializedPacketData.data(), sizeof(S_AddItem_Packet));
			RecvAddItem(addItemPacket);
			event->isComplete = true;
			break;
		case S_RemoveObject:
			S_RemoveObject_Packet removeObjectPacket;
			FMemory::Memcpy(&removeObjectPacket, event->serializedPacketData.data(), sizeof(S_RemoveObject_Packet));
			RecvRemoveObject(removeObjectPacket);
			event->isComplete = true;
			break;
		case S_UpdateObjectState:
			S_UpdateObjectState_Packet updateObjectStatePacket;
			FMemory::Memcpy(&updateObjectStatePacket, event->serializedPacketData.data(), sizeof(S_UpdateObjectState_Packet));
			RecvUpdateObjectState(updateObjectStatePacket);
			event->isComplete = true;
			break;
		case S_Move:
			S_Move_Packet movePacket;
			FMemory::Memcpy(&movePacket, event->serializedPacketData.data(), sizeof(S_Move_Packet));
			RecvMoveObject(movePacket);
			event->isComplete = true;
			break;
		case S_CreateGameRoom:
			S_CreateGameRoom_Packet createGameRoomPacket{ _gameNetwork->DeserializeVector<GameRoomDTO>(event->serializedPacketData) };
			RecvCreateGameRoom(createGameRoomPacket);
			event->isComplete = true;
			break;
		}
	}
}

void UMain::RecvAddObject(S_AddObject_Packet packet)
{
	if (packet.type == ObjectType::Player)
		AddPlayer(packet);
	else if (packet.type == ObjectType::Monster)
		AddMonster(packet);
}

void UMain::AddPlayer(S_AddObject_Packet packet)
{
	UE_LOG(LogTemp, Log, TEXT("AddObject Packet [%d], %f, %f, %f"), packet.objectID, packet.pos.x, packet.pos.y, packet.pos.z);

	if (_myID == 0)
	{
		// 자신의 ID 설정
		_myID = packet.objectID;

		// Spawn
		AsyncTask(ENamedThreads::GameThread, [=, this]()
		{
			UWorld* world = GetWorld();
			if (!world) return;

			FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
			FRotator spawnRotation(0, packet.rotation.yaw, 0);

			auto playerController = UGameplayStatics::GetPlayerController(this, 0);
			AMyPlayer* player = Cast<AMyPlayer>(playerController->GetPawn());

			if (!player)
				return;

			// 서버에서 받은 위치로 수정
			player->SetActorLocationAndRotation(
				spawnLocation,
				spawnRotation,
				false,
				nullptr,
				ETeleportType::TeleportPhysics
			);

			_myPlayer = player;

			UE_LOG(LogTemp, Log, TEXT("My Player Spawned! [%d], %f, %f, %f"), packet.objectID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		});
		return;
	}

	if (packet.objectID == _myID)
		return;

	// 이미 존재하는 객체인지 확인
	if (_otherPlayers.Contains(packet.objectID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Player already spawned... object ID: %d"), packet.objectID);
		return;
	}

	// 다른 플레이어 Spawn
	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, packet.rotation.yaw, 0);
	int id = packet.objectID;

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

void UMain::AddMonster(S_AddObject_Packet packet)
{
	if (_monsters.Contains(packet.objectID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster already spawned... object ID: %d"), packet.objectID);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, packet.rotation.yaw, 0);
	int id = packet.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world || !OtherPlayerClass)
			return;

		AStaticMeshActor* monsterActor = world->SpawnActor<AStaticMeshActor>(TestMonsterClass, spawnLocation, spawnRotation);

		if (monsterActor)
		{
			_monsters.Add(id, monsterActor);
			UE_LOG(LogTemp, Log, TEXT("Monster Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}
		else
		{
			_monsters.Remove(id);
			UE_LOG(LogTemp, Error, TEXT("Monster Spawn Failed... ID [%d]"), id);
		}
	});
}

void UMain::RecvAddItem(S_AddItem_Packet packet)
{
	if (_items.Contains(packet.objectID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item already spawned... object ID: %d"), packet.objectID);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, packet.rotation.yaw, 0);
	int id = packet.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		ABaseItem* item;
		switch (packet.itemType)
		{
		case ItemType::CardboardBox:
			item = world->SpawnActor<ABaseItem>(CardboardBoxClass, spawnLocation, spawnRotation);
			item->SetItemID(id);
			UE_LOG(LogTemp, Log, TEXT("[Item] CardboardBox Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}
	});
}

void UMain::RecvRemoveObject(S_RemoveObject_Packet packet)
{
}

void UMain::RecvMoveObject(S_Move_Packet packet)
{
	if (packet.type == ObjectType::Player)
		RecvMovePlayer(packet);
	else if (packet.type == ObjectType::Monster)
		RecvMoveMonster(packet);
}

void UMain::RecvMovePlayer(S_Move_Packet packet)
{
	if (packet.objectID == _myID)
	{
		UE_LOG(LogTemp, Warning, TEXT("ID %d is MyID. Ignore."), packet.objectID);
		return;
	}

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		AOtherPlayer** findPlayer = _otherPlayers.Find(packet.objectID);
		if (!findPlayer)
		{
			UE_LOG(LogTemp, Error, TEXT("Other Player [%d] not in _otherPlayers"), packet.objectID);
			return;
		}

		AOtherPlayer* player = (*findPlayer);

		FVector pos(packet.pos.x, packet.pos.y, packet.pos.z);
		FRotator rot(0, packet.rotation.yaw, 0);
		player->SetPlayerLocation(pos, rot);
		player->SetPlayerState(packet.state);
		//UE_LOG(LogTemp, Display, TEXT("Other Player [%d] SetPlayerLocation!!!"), id);
	});
}

void UMain::RecvMoveMonster(S_Move_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		AStaticMeshActor** findMonster = _monsters.Find(packet.objectID);
		if (!findMonster)
		{
			UE_LOG(LogTemp, Error, TEXT("Monster [%d] not in _monsters"), packet.objectID);
			return;
		}

		AStaticMeshActor* monster = (*findMonster);

		FVector pos(packet.pos.x, packet.pos.y, packet.pos.z);
		FRotator rot(0, packet.rotation.yaw, 0);
		monster->SetActorLocationAndRotation(pos, rot);
		UE_LOG(LogTemp, Error, TEXT("Monster [%d] Moved!!!, %f, %f, %f"), packet.objectID, packet.pos.x, packet.pos.y, packet.pos.z);
	});
}

void UMain::RecvUpdateObjectState(S_UpdateObjectState_Packet packet)
{
}

void UMain::RecvCreateGameRoom(S_CreateGameRoom_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [this, packet]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		for (int i = 0; i < packet.gameRooms.size(); ++i)
		{
			const GameRoomDTO& room = packet.gameRooms[i];

			FVector pos(room.pos.x, room.pos.y, room.pos.z);
			FRotator rot = DirToRotation(room.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AStaticMeshActor* roomActor;
			switch (packet.gameRooms[i].type)
			{
			case GameRoomType::MainEntranceRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(MainEntranceRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("MainEntrance Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::GapRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(GapRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("Gap Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::ApparatusRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ApparatusRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("ApparatusRoom Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::ServerRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ServerRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("Server Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::CabinetRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(CabinetRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("Cabinet Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Rect:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_RectClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("StorageRoom_Rect Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Corner:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_ConerClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("StorageRoom_Coner Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Step:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_StepClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("StorageRoom_Step Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::YellowOfficeRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(YellowOfficeRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("YellowOffice Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::FactoryRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(FactoryRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("Factory Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::RailCatwalk:
				roomActor = world->SpawnActor<AStaticMeshActor>(RailCatwalkClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("RailCatwalk Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::PipedHallways_Line:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_LineClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("PipedHallways_Line Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::PipedHallways_Grid:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_GridClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("PipedHallways_Grid Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::Staircase:
				roomActor = world->SpawnActor<AStaticMeshActor>(StaircaseClass, pos, rot, params);
				UE_LOG(LogTemp, Warning, TEXT("Staircase Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			}
		}
	});
}

FRotator UMain::DirToRotation(Dir dir)
{
	FRotator rotation = FRotator::ZeroRotator;

	switch (dir)
	{
	case Front: rotation.Yaw = 0.f; break;
	case Right: rotation.Yaw = 90.f; break;
	case Back:	rotation.Yaw = 180.f; break;
	case Left:	rotation.Yaw = 270.f; break;
	}

	return rotation;
}
