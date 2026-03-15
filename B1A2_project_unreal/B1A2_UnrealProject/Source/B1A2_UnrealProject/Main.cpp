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

	_gameNetwork->SendGetItemPacket(itemID, false, playerID);
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
			if (addItemPacket.objectType == ObjectType::Item)
				RecvAddItem(addItemPacket);
			else if (addItemPacket.objectType == ObjectType::Tool)
				RecvAddTool(addItemPacket);
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
		case S_AddItemToInventory:
			S_AddItemToInventory_Packet addItemToInventoryPacket;
			FMemory::Memcpy(&addItemToInventoryPacket, event->serializedPacketData.data(), sizeof(S_AddItemToInventory_Packet));
			RecvAddItemToInventory(addItemToInventoryPacket);
			event->isComplete = true;
			break;
		case S_CreateGameRoom:
			S_CreateGameRoom_Packet createGameRoomPacket{ _gameNetwork->DeserializeVector<GameRoomDTO>(event->serializedPacketData), _gameNetwork->DeserializeVector<WallDTO>(event->serializedPacketData) };
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

		ABaseItem* item = nullptr;
		switch (packet.itemType)
		{
		case ItemType::CardboardBox:
			item = world->SpawnActor<ABaseItem>(CardboardBoxClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] CardboardBox Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::GoldBar:
			item = world->SpawnActor<ABaseItem>(GoldBarClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] GoldBar Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::RubberDuck:
			item = world->SpawnActor<ABaseItem>(RubberDuckClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] RubberDuck Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::PlasticCrate:
			item = world->SpawnActor<ABaseItem>(PlasticCrateClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] PlasticCrate Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::Screw:
			item = world->SpawnActor<ABaseItem>(ScrewClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] Screw Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::PirateHat:
			item = world->SpawnActor<ABaseItem>(PirateHatClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] PirateHat Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::HardHat:
			item = world->SpawnActor<ABaseItem>(HardHatClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] HardHat Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::EngineCore:
			item = world->SpawnActor<ABaseItem>(EngineCoreClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] EngineCore Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::ScrapMetal:
			item = world->SpawnActor<ABaseItem>(ScrapMetalClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] ScrapMetal Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::EmptyCan:
			item = world->SpawnActor<ABaseItem>(EmptyCanClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Item] EmptyCan Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		}

		item->SetItemID(id);
		
		// Spawn 후 Map에 등록
		_items.Add(id, item);	
	});
}

void UMain::RecvAddTool(S_AddItem_Packet packet)
{
	if (_tools.Contains(packet.objectID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tool already spawned... object ID: %d"), packet.objectID);
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

		ABaseItem* tool = nullptr;
		switch (packet.itemType)
		{
		case ItemType::Cutlass:
			tool = world->SpawnActor<ABaseItem>(CardboardBoxClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Cutlass Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::Blaster:
			tool = world->SpawnActor<ABaseItem>(BlasterClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Blaster Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::Key:
			tool = world->SpawnActor<ABaseItem>(KeyClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Key Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		}

		tool->SetItemID(id);

		// Spawn 후 Map에 등록
		_tools.Add(id, tool);
	});
}

void UMain::RecvRemoveObject(S_RemoveObject_Packet packet)
{
	switch (packet.objectType)
	{
	case ObjectType::Player:
		RemovePlayer(packet);
		break;
	case ObjectType::Monster:
		RemoveMonster(packet);
		break;
	default:
		break;
	}
}

void UMain::RemovePlayer(S_RemoveObject_Packet packet)
{
	int id = packet.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		AOtherPlayer** foundPlayer = _otherPlayers.Find(id);
		if (!foundPlayer || !(*foundPlayer))
		{
			UE_LOG(LogTemp, Log, TEXT("[Player] Remove Failed... ID %llu Not found"), id);
			return;
		}

		AOtherPlayer* player = *foundPlayer;

		// Map에서 제거
		_otherPlayers.Remove(id);
		// 월드에서 제거
		player->Destroy();

		UE_LOG(LogTemp, Log, TEXT("[Player] Player Removed!!! ID %llu, Name %s"), id, *player->GetName());
	});
}

void UMain::RemoveMonster(S_RemoveObject_Packet packet)
{
	int id = packet.objectID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		AStaticMeshActor** foundMonster = _monsters.Find(id);
		if (!foundMonster || !(*foundMonster))
		{
			UE_LOG(LogTemp, Log, TEXT("[Item] Remove Failed... ID %llu Not found"), id);
			return;
		}

		AStaticMeshActor* monster = *foundMonster;

		// Map에서 제거
		_monsters.Remove(id);
		// 월드에서 제거
		monster->Destroy();

		UE_LOG(LogTemp, Log, TEXT("[Monster] Monster Removed!!! ID %llu, Name %s"), id, *monster->GetName());
	});
}

//void UMain::RemoveItem(S_RemoveObject_Packet packet)
//{
//	int id = packet.objectID;
//
//	AsyncTask(ENamedThreads::GameThread, [=, this]()
//	{
//		UWorld* world = GetWorld();
//		if (!world)
//			return;
//
//		ABaseItem** foundItem = _items.Find(id);
//		if (!foundItem || !(*foundItem))
//		{
//			UE_LOG(LogTemp, Log, TEXT("[Item] Remove Failed... ID %llu Not found"), id);
//			return;
//		}
//
//		ABaseItem* item = *foundItem;
//
//		// Map에서 제거
//		_items.Remove(id);
//		// 월드에서 제거
//		item->Destroy();
//
//		UE_LOG(LogTemp, Log, TEXT("[Item] Item Removed!!! ID %llu, Name %s"), id, *item->GetName());
//	});
//}

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
		// UE_LOG(LogTemp, Error, TEXT("Monster [%d] Moved!!!, %f, %f, %f"), packet.objectID, packet.pos.x, packet.pos.y, packet.pos.z);
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

		// Room
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
				UE_LOG(LogTemp, Log, TEXT("[Room] MainEntrance Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::GapRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(GapRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Gap Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::ApparatusRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ApparatusRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] ApparatusRoom Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::ServerRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ServerRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Server Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::CabinetRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(CabinetRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Cabinet Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Rect:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_RectClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Rect Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Corner:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_ConerClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Coner Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::StorageRoom_Step:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_StepClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Step Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::YellowOfficeRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(YellowOfficeRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] YellowOffice Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::FactoryRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(FactoryRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Factory Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::RailCatwalk:
				roomActor = world->SpawnActor<AStaticMeshActor>(RailCatwalkClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] RailCatwalk Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::PipedHallways_Line:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_LineClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] PipedHallways_Line Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::PipedHallways_Grid:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_GridClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] PipedHallways_Grid Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			case GameRoomType::Staircase:
				roomActor = world->SpawnActor<AStaticMeshActor>(StaircaseClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Staircase Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, room.pos.x, room.pos.y, room.pos.z, room.type, room.dir);
				break;
			}
		}

		// Wall
		for (int i = 0; i < packet.walls.size(); ++i)
		{
			const WallDTO& wall = packet.walls[i];

			FVector pos(wall.pos.x, wall.pos.y, wall.pos.z);
			FRotator rot = DirToRotation(wall.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AStaticMeshActor* wallActor = world->SpawnActor<AStaticMeshActor>(Wall_FillerClass, pos, rot, params);
			UE_LOG(LogTemp, Log, TEXT("[Room] Wall Spawned [%d] pos = %f, %f, %f, dir = %d"), i, wall.pos.x, wall.pos.y, wall.pos.z, wall.dir);
		}
	});
}

void UMain::RecvAddItemToInventory(S_AddItemToInventory_Packet packet)
{
	//int playerID = packet.playerID;
	int itemID = packet.itemID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		ABaseItem** foundItem = _items.Find(itemID);
		if (!foundItem || !(*foundItem))
		{
			UE_LOG(LogTemp, Log, TEXT("[Item] Remove Failed... ID %llu Not found"), itemID);
			return;
		}

		ABaseItem* item = *foundItem;

		// Map에서 제거
		//_items.Remove(itemID);

		// 아이템 줍기 애니메이션 재생(+ 월드에서 아이템 삭제)
		//if (playerID == _myID)
			_myPlayer->PlayPickUpAnimation(item);
		/*else
		{
			AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);

			if (foundPlayer && *foundPlayer)
			{
				(*foundPlayer)->PlayPickUpAnimation(item);
				UE_LOG(LogTemp, Warning, TEXT("[Item] OtherPlayer ID %llu Item PickUp Animation!"), playerID);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("[Item] OtherPlayer ID %llu not found in map!"), playerID);
		}*/
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
