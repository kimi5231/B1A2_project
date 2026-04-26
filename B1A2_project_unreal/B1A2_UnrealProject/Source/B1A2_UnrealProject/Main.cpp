#include "Main.h"
#include "NetworkRecvRunnable.h"
#include "EmotionExtractionRunnable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "OtherPlayer.h"
#include "Network/GameNetwork.h"
#include "BaseItem.h"
#include "BaseDoor.h"
#include "ToolBarWidget.h"
#include "BaseMonster.h"

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
			{
				S_AddObject_Packet addObjectPacket;
				FMemory::Memcpy(&addObjectPacket, event->serializedPacketData.data(), sizeof(S_AddObject_Packet));
				RecvAddObject(addObjectPacket);
				event->isComplete = true;
				break;
			}
			case S_AddItem:
			{
				S_AddItem_Packet addItemPacket;
				FMemory::Memcpy(&addItemPacket, event->serializedPacketData.data(), sizeof(S_AddItem_Packet));
				if (addItemPacket.isTool)
					RecvAddTool(addItemPacket);
				else
					RecvAddItem(addItemPacket);
				event->isComplete = true;
				break;
			}
			case S_RemoveObject:
			{
				S_RemoveObject_Packet removeObjectPacket;
				FMemory::Memcpy(&removeObjectPacket, event->serializedPacketData.data(), sizeof(S_RemoveObject_Packet));
				RecvRemoveObject(removeObjectPacket);
				event->isComplete = true;
				break;
			}
			case S_UpdateObjectState:
			{
				S_UpdateObjectState_Packet updateObjectStatePacket;
				FMemory::Memcpy(&updateObjectStatePacket, event->serializedPacketData.data(), sizeof(S_UpdateObjectState_Packet));
				RecvUpdateObjectState(updateObjectStatePacket);
				event->isComplete = true;
				break;
			}
			case S_Move:
			{
				S_Move_Packet movePacket;
				FMemory::Memcpy(&movePacket, event->serializedPacketData.data(), sizeof(S_Move_Packet));
				RecvMoveObject(movePacket);
				event->isComplete = true;
				break;
			}
			case S_AddItemToInventory:	// MyPlayer의 아이템과 장비를 인벤과 툴바에 넣음 (OtherPlayer는 UpdateObjectState)
			{
				S_AddItemToInventory_Packet addItemToInventoryPacket;
				FMemory::Memcpy(&addItemToInventoryPacket, event->serializedPacketData.data(), sizeof(S_AddItemToInventory_Packet));
				RecvAddItemToInventory(addItemToInventoryPacket);
				event->isComplete = true;
				break;
			}
			case S_RemoveItemFromInventory:
			{
				S_RemoveItemFromInventory_Packet removeItemFromInventoryPacket;
				FMemory::Memcpy(&removeItemFromInventoryPacket, event->serializedPacketData.data(), sizeof(S_RemoveItemFromInventory_Packet));
				RecvRemoveItemFromInventory(removeItemFromInventoryPacket);
				event->isComplete = true;
				break;
			}
			case S_ItemPickupNotify:
			{
				S_ItemPickupNotify_Packet itemPickupNotifyPacket;
				FMemory::Memcpy(&itemPickupNotifyPacket, event->serializedPacketData.data(), sizeof(S_ItemPickupNotify_Packet));
				RecvItemPickupNotify(itemPickupNotifyPacket);
				event->isComplete = true;
				break;
			}
			case S_DropItem:
			{
				S_DropItem_Packet dropItemPacket;
				FMemory::Memcpy(&dropItemPacket, event->serializedPacketData.data(), sizeof(S_DropItem_Packet));
				RecvDropItem(dropItemPacket);
				event->isComplete = true;
				break;
			}
			case S_UpdateCurrentTool:
			{
				S_UpdateCurrentTool_Packet updateCurrentToolPacket;
				FMemory::Memcpy(&updateCurrentToolPacket, event->serializedPacketData.data(), sizeof(S_UpdateCurrentTool_Packet));
				RecvUpdateCurrentTool(updateCurrentToolPacket);
				event->isComplete = true;
				break;
			}
			case S_UseTool:
				S_UseTool_Packet useToolPacket;
				FMemory::Memcpy(&useToolPacket, event->serializedPacketData.data(), sizeof(S_UseTool_Packet));
				RecvUseTool(useToolPacket);
				event->isComplete = true;
				break;
			case S_SpawnParticle:
			{
				S_SpawnParticle_Packet spawnParticlePacket;
				FMemory::Memcpy(&spawnParticlePacket, event->serializedPacketData.data(), sizeof(S_SpawnParticle_Packet));
				RecvSpawnParticle(spawnParticlePacket);
				event->isComplete = true;
				break;
			}
			case S_InteractDoorNotify:
			{
				S_InteractDoorNotify_Packet interactDoorNotifyPacket;
				FMemory::Memcpy(&interactDoorNotifyPacket, event->serializedPacketData.data(), sizeof(S_InteractDoorNotify_Packet));
				RecvInteractDoorNotify(interactDoorNotifyPacket);
				event->isComplete = true;
				break;
			}
			case S_CreateCubes:
			{
				S_CreateCubes_Packet createCubesPacket{ _gameNetwork->DeserializeVector<CubeDTO>(event->serializedPacketData), _gameNetwork->DeserializeVector<DoorDTO>(event->serializedPacketData) };
				RecvCreateCubes(createCubesPacket);
				event->isComplete = true;
				break;
			}
			case S_SpawnMonster:
			{
				S_SpawnMonster_Packet spawnMonsterPacket;
				FMemory::Memcpy(&spawnMonsterPacket, event->serializedPacketData.data(), sizeof(S_SpawnMonster_Packet));
				RecvSpawnMonster(spawnMonsterPacket);
				event->isComplete = true;
				break;
			}
			case S_TurnOnLantern:
			{
				S_TurnOnLantern_Packet turnOnLanternPacket;
				FMemory::Memcpy(&turnOnLanternPacket, event->serializedPacketData.data(), sizeof(S_TurnOnLantern_Packet));
				RecvTurnOnLantern(turnOnLanternPacket);
				event->isComplete = true;
				break;
			}
			case S_TurnOffLantern:
			{
				S_TurnOffLantern_Packet turnOffLanternPacket;
				FMemory::Memcpy(&turnOffLanternPacket, event->serializedPacketData.data(), sizeof(S_TurnOffLantern_Packet));
				RecvTurnOffLantern(turnOffLanternPacket);
				event->isComplete = true;
				break;
			}
		}
	}
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
		pos.z = (float)playerPawn->GetActorLocation().Z - 98.f;

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

void UMain::SendGetItem(int itemID, bool isTool, int playerID)
{
	if (_myID == 0 || itemID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world) return;

	_gameNetwork->SendGetItemPacket(itemID, isTool, playerID);
}

void UMain::SendDropItem(int playerID, bool isTool, int itemID)
{
	if (_myID == 0 || itemID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendDropItemPacket(itemID, isTool, playerID);
}

void UMain::SendChangeTool(int playerID, int toolID)
{
	if (_myID == 0 || toolID < 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendChangeToolPacket(playerID, toolID);
}

void UMain::SendInteractDoor(int playerID, int doorID)
{
	if (_myID == 0 || doorID < 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendInteractDoorPacket(playerID, doorID);
}

void UMain::SendUseTool(int playerID, int toolID, Rotation playerRotation)
{
	if (_myID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendUseToolPacket(playerID, toolID, playerRotation);
}

void UMain::SendEmotion(float angry, float disgust, float fear, float happy, float sad, float surprise, float neutral)
{
	if (_myID == 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendEmotionPacket(angry, disgust, fear, happy, sad, surprise, neutral);
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



void UMain::RecvAddObject(S_AddObject_Packet packet)
{
	if (packet.type == ObjectType::Player)
		AddPlayer(packet);
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

			FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z + 98.f);
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

			UE_LOG(LogTemp, Log, TEXT("My Player Spawned! [%d], %f, %f, %f"), packet.objectID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 98.f);
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
	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z + 98.f);
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
			item->SetItemType(ItemType::CardboardBox);
			UE_LOG(LogTemp, Log, TEXT("[Item] CardboardBox Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::GoldBar:
			item = world->SpawnActor<ABaseItem>(GoldBarClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::GoldBar);
			UE_LOG(LogTemp, Log, TEXT("[Item] GoldBar Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::RubberDuck:
			item = world->SpawnActor<ABaseItem>(RubberDuckClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::RubberDuck);
			UE_LOG(LogTemp, Log, TEXT("[Item] RubberDuck Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::PlasticCrate:
			item = world->SpawnActor<ABaseItem>(PlasticCrateClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::PlasticCrate);
			UE_LOG(LogTemp, Log, TEXT("[Item] PlasticCrate Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::Screw:
			item = world->SpawnActor<ABaseItem>(ScrewClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::Screw);
			UE_LOG(LogTemp, Log, TEXT("[Item] Screw Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::PirateHat:
			item = world->SpawnActor<ABaseItem>(PirateHatClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::PirateHat);
			UE_LOG(LogTemp, Log, TEXT("[Item] PirateHat Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::HardHat:
			item = world->SpawnActor<ABaseItem>(HardHatClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::HardHat);
			UE_LOG(LogTemp, Log, TEXT("[Item] HardHat Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::EngineCore:
			item = world->SpawnActor<ABaseItem>(EngineCoreClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::EngineCore);
			UE_LOG(LogTemp, Log, TEXT("[Item] EngineCore Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::ScrapMetal:
			item = world->SpawnActor<ABaseItem>(ScrapMetalClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::ScrapMetal);
			UE_LOG(LogTemp, Log, TEXT("[Item] ScrapMetal Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::EmptyCan:
			item = world->SpawnActor<ABaseItem>(EmptyCanClass, spawnLocation, spawnRotation);
			item->SetItemType(ItemType::EmptyCan);
			UE_LOG(LogTemp, Log, TEXT("[Item] EmptyCan Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		}

		item->SetItemID(id);
		item->SetIsTool(false);

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
		case ItemType::CUTLASS:
			tool = world->SpawnActor<ABaseItem>(CutlassClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 10), spawnRotation);
			tool->SetItemType(ItemType::CUTLASS);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Cutlass Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 10);
			break;
		case ItemType::Blaster:
			tool = world->SpawnActor<ABaseItem>(BlasterClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 10), spawnRotation);
			tool->SetItemType(ItemType::Blaster);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Blaster Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 10);
			break;
		case ItemType::Key:
			tool = world->SpawnActor<ABaseItem>(KeyClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
			tool->SetItemType(ItemType::Key);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Key Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
			break;
		case ItemType::Lantern:
			tool = world->SpawnActor<ABaseItem>(LanternClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
			tool->SetItemType(ItemType::Lantern);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Lantern Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}

		tool->SetItemID(id);
		tool->SetIsTool(true);

		// Spawn 후 Map에 등록
		_tools.Add(id, tool);
	});
}

void UMain::RecvDropItem(S_DropItem_Packet packet)
{
	int playerID = packet.playerID;
	int itemID = packet.itemID;
	bool isTool = packet.isTool;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		// MyPlayer라면 슬롯에서 삭제
		if (packet.playerID == _myID)
		{
			// 장비
			if (isTool)	
			{
				// 툴바에서 삭제
				_myPlayer->RemoveToolInToolBarByID(itemID);

				// 손에 들고 있으면 제거
				_myPlayer->UnequipTool(itemID);
			}
			else // 아이템
			{
				// 인벤에서 삭제
				_myPlayer->RemoveItemInInventoryByID(itemID);
			}
		}
		// OtherPlayer이고, 들고있는 도구라면 손에서 떼도록
		else
		{
			AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);
			if (foundPlayer && *foundPlayer)
			{
				if (isTool)
				{
					(*foundPlayer)->UnequipTool(itemID);
				}
			}
		}

		// 버린 위치에 스폰
		FVector spawnLocation(packet.itemPos.x, packet.itemPos.y, packet.itemPos.z);
		FRotator spawnRotation(0, 0, 0);	// 일단 yaw도 0으로 테스트

		// 장비
		if (isTool)
		{	
			ABaseItem* tool = nullptr;

			switch (packet.itemType)
			{
			case ItemType::CUTLASS:
				tool = world->SpawnActor<ABaseItem>(CutlassClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 10), spawnRotation);	// 임시 위치 보정
				tool->SetItemType(ItemType::CUTLASS);
				UE_LOG(LogTemp, Log, TEXT("[Tool] Cutlass Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 10);
				break;
			case ItemType::Blaster:
				tool = world->SpawnActor<ABaseItem>(BlasterClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 10), spawnRotation);
				tool->SetItemType(ItemType::Blaster);
				UE_LOG(LogTemp, Log, TEXT("[Tool] Blaster Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 10);
				break;
			case ItemType::Key:
				tool = world->SpawnActor<ABaseItem>(KeyClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				tool->SetItemType(ItemType::Key);
				UE_LOG(LogTemp, Log, TEXT("[Tool] Key Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::Lantern:
				tool = world->SpawnActor<ABaseItem>(LanternClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
				tool->SetItemType(ItemType::Lantern);
				UE_LOG(LogTemp, Log, TEXT("[Tool] Lantern Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
				break;
			}

			tool->SetItemID(itemID);
			tool->SetIsTool(true);
			_tools.Add(itemID, tool);
		}
		// 아이템
		else
		{
			ABaseItem* item = nullptr;

			switch (packet.itemType)
			{
			case ItemType::CardboardBox:
				item = world->SpawnActor<ABaseItem>(CardboardBoxClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
				item->SetItemType(ItemType::CardboardBox);
				UE_LOG(LogTemp, Log, TEXT("[Item] CardboardBox Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
				break;
			case ItemType::GoldBar:
				item = world->SpawnActor<ABaseItem>(GoldBarClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::GoldBar);
				UE_LOG(LogTemp, Log, TEXT("[Item] GoldBar Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::RubberDuck:
				item = world->SpawnActor<ABaseItem>(RubberDuckClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::RubberDuck);
				UE_LOG(LogTemp, Log, TEXT("[Item] RubberDuck Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::PlasticCrate:
				item = world->SpawnActor<ABaseItem>(PlasticCrateClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::PlasticCrate);
				UE_LOG(LogTemp, Log, TEXT("[Item] PlasticCrate Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::Screw:
				item = world->SpawnActor<ABaseItem>(ScrewClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::Screw);
				UE_LOG(LogTemp, Log, TEXT("[Item] Screw Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::PirateHat:
				item = world->SpawnActor<ABaseItem>(PirateHatClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::PirateHat);
				UE_LOG(LogTemp, Log, TEXT("[Item] PirateHat Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::HardHat:
				item = world->SpawnActor<ABaseItem>(HardHatClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::HardHat);
				UE_LOG(LogTemp, Log, TEXT("[Item] HardHat Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::EngineCore:
				item = world->SpawnActor<ABaseItem>(EngineCoreClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::EngineCore);
				UE_LOG(LogTemp, Log, TEXT("[Item] EngineCore Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::ScrapMetal:
				item = world->SpawnActor<ABaseItem>(ScrapMetalClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::ScrapMetal);
				UE_LOG(LogTemp, Log, TEXT("[Item] ScrapMetal Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			case ItemType::EmptyCan:
				item = world->SpawnActor<ABaseItem>(EmptyCanClass, (spawnLocation.X, spawnLocation.Y, spawnLocation + 30), spawnRotation);
				item->SetItemType(ItemType::EmptyCan);
				UE_LOG(LogTemp, Log, TEXT("[Item] EmptyCan Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
				break;
			}

			item->SetItemID(itemID);
			item->SetIsTool(false);
			_items.Add(itemID, item);
		}
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
	case ObjectType::Item:
		RemoveItem(packet);
	//case ObjectType::Tool:
	//	RemoveTool(packet);
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

		ABaseMonster** foundMonster = _monsters.Find(id);
		if (!foundMonster || !(*foundMonster))
		{
			UE_LOG(LogTemp, Log, TEXT("[Monster] Remove Failed... ID %llu Not found"), id);
			return;
		}

		ABaseMonster* monster = *foundMonster;

		// Map에서 제거
		_monsters.Remove(id);
		// 월드에서 제거
		monster->Destroy();

		UE_LOG(LogTemp, Log, TEXT("[Monster] Monster Removed!!! ID %llu, Name %s"), id, *monster->GetName());
	});
}

void UMain::RemoveItem(S_RemoveObject_Packet packet)
{
	// Map에서 제거 (월드에서는 애니메이션 중간에 지움)
	//_items.Remove(packet.objectID);
}

void UMain::RemoveTool(S_RemoveObject_Packet packet)
{
	// Map에서 제거
	//_tools.Remove(packet.objectID);
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

		FVector pos(packet.pos.x, packet.pos.y, packet.pos.z + 98.f);
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
		if (!GetWorld()) return;

		ABaseMonster** findMonster = _monsters.Find(packet.objectID);
		if (findMonster && *findMonster)
		{
			ABaseMonster* monster = (*findMonster);

			FVector pos(packet.pos.x, packet.pos.y, packet.pos.z + 30);
			FRotator rot(0, packet.rotation.yaw, 0);

			monster->SetTargetTransform(pos, rot);
		}
	});
}

void UMain::RecvUpdateObjectState(S_UpdateObjectState_Packet packet)
{
}

void UMain::RecvCreateCubes(S_CreateCubes_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [this, packet]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		// Cube
		for (int i = 0; i < packet.cubes.size(); ++i)
		{
			const CubeDTO& cube = packet.cubes[i];

			FVector pos(cube.pos.x, cube.pos.y, cube.pos.z);
			FRotator rot = DirToRotation(cube.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AStaticMeshActor* roomActor;
			switch (packet.cubes[i].type)
			{
			case CubeType::MainEntranceRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(MainEntranceRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] MainEntrance Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::GapRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(GapRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Gap Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::ApparatusRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ApparatusRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] ApparatusRoom Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::ServerRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(ServerRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Server Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::CabinetRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(CabinetRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Cabinet Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::StorageRoom_Rect:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_RectClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Rect Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::StorageRoom_Corner:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_ConerClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Coner Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::StorageRoom_Step:
				roomActor = world->SpawnActor<AStaticMeshActor>(StorageRoom_StepClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] StorageRoom_Step Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::YellowOfficeRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(YellowOfficeRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] YellowOffice Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::FactoryRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(FactoryRoomClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Factory Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::RailCatwalk:
				roomActor = world->SpawnActor<AStaticMeshActor>(RailCatwalkClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] RailCatwalk Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::PipedHallways_Line:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_LineClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] PipedHallways_Line Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::PipedHallways_Grid:
				roomActor = world->SpawnActor<AStaticMeshActor>(PipedHallways_GridClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] PipedHallways_Grid Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			case CubeType::Staircase:
				roomActor = world->SpawnActor<AStaticMeshActor>(StaircaseClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Staircase Room Spawned [%d] pos = %f, %f, %f, type = %d, dir = %d"), i, cube.pos.x, cube.pos.y, cube.pos.z, cube.type, cube.dir);
				break;
			}
		}

		// Wall or Door
		for (int i = 0; i < packet.doors.size(); ++i)
		{
			const DoorDTO& door = packet.doors[i];

			FVector pos(door.pos.x, door.pos.y, door.pos.z);
			FRotator rot = DirToRotation(door.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (door.doorType == DoorType::Door)
			{
				ABaseDoor* doorActor = world->SpawnActor<ABaseDoor>(DoorClass, pos, rot, params);
				doorActor->SetDoorState(packet.doors[i].state);
				doorActor->SetDoorID(packet.doors[i].id);
				doorActor->SetDoorRotation(packet.doors[i].state);	// 상태에 따라 문 각도 설정

				// Map에 추가
				_doors.Add(packet.doors[i].id, doorActor);

				UE_LOG(LogTemp, Log, TEXT("[Room] Door Spawned [%d] pos = %f, %f, %f, dir = %d"), i, door.pos.x, door.pos.y, door.pos.z, door.dir);
			}
			else if (door.doorType == DoorType::Wall)
			{
				AStaticMeshActor* wallActor = world->SpawnActor<AStaticMeshActor>(Wall_FillerClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Wall Spawned [%d] pos = %f, %f, %f, dir = %d"), i, door.pos.x, door.pos.y, door.pos.z, door.dir);
			}
		}
	});
}

void UMain::RecvAddItemToInventory(S_AddItemToInventory_Packet packet)
{
	int itemID = packet.itemID;
	UE_LOG(LogTemp, Log, TEXT("[RecvAddItemToInventory] ID: %d"), itemID);

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		if (packet.isTool)
		{
			ABaseItem** foundTool = _tools.Find(itemID);
			if (!foundTool || !(*foundTool))
			{
				UE_LOG(LogTemp, Log, TEXT("[Tool] item not found... ID %llu Not found"), itemID);
				return;
			}

			ABaseItem* tool = *foundTool;
			int32 toolIndex = _myPlayer->AddToolToToolBar(packet.itemType, itemID, packet.itemWeight);

			// 장비 줍기 애니메이션 재생 + 월드에서 장비 삭제
			_myPlayer->PlayPickUpAnimation(tool);
			// 툴바에 넣기
			if (toolIndex != -1)
			{
				if (UToolBarWidget* widget = Cast<UToolBarWidget>(_myPlayer->GetToolBarWidget()))
				{
					widget->SetSelectedIndex(toolIndex);
					_myPlayer->OnToolSelectionChanged();	// 손에 부착 및 서버로 패킷 전송
				}
			}
			// _tools에서 제거
			_tools.Remove(itemID);

			UE_LOG(LogTemp, Display, TEXT("[RecvAddItemToInventory] Tool PickedUp and To ToolBar"));
		}
		else
		{
			ABaseItem** foundItem = _items.Find(itemID);
			if (!foundItem || !(*foundItem))
			{
				UE_LOG(LogTemp, Log, TEXT("[Item] item not found... ID %llu Not found"), itemID);
				return;
			}

			ABaseItem* item = *foundItem;

			// 아이템 줍기 애니메이션 재생 + 월드에서 아이템 삭제
			_myPlayer->PlayPickUpAnimation(item);
			// 인벤에 넣기
			_myPlayer->AddItemToInventory(packet.itemType, itemID, packet.itemWeight);
			// _items에서 제거
			_items.Remove(itemID);

			UE_LOG(LogTemp, Display, TEXT("[RecvAddItemToInventory] Item PickedUp and To Inventory"));
		}		
	});
}

void UMain::RecvRemoveItemFromInventory(S_RemoveItemFromInventory_Packet packet)
{

}

void UMain::RecvItemPickupNotify(S_ItemPickupNotify_Packet packet)
{
	int itemID = packet.itemID;
	int playerID = packet.playerID;
	bool isTool = packet.isTool;
	ItemType itemType = packet.itemType;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		// Tool
		if (isTool)
		{

			ABaseItem** foundTool = _tools.Find(itemID);
			if (!foundTool || !(*foundTool))
			{
				UE_LOG(LogTemp, Log, TEXT("[Tool] item not found... ID %llu Not found"), itemID);
				return;
			}

			ABaseItem* tool = *foundTool;

			// Player
			AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);
			if (foundPlayer && *foundPlayer)
			{
				(*foundPlayer)->PlayPickUpAnimation(tool);

				// _tools에서 제거
				_tools.Remove(itemID);

				// 손에 Tool 부착
				(*foundPlayer)->UpdateTool(itemType);

				UE_LOG(LogTemp, Warning, TEXT("[Tool] OtherPlayer ID %llu Tool PickUp Animation!"), playerID);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("[Item] OtherPlayer ID %llu not found in map!"), playerID);

		}
		// Item
		else
		{

			ABaseItem** foundItem = _items.Find(itemID);
			if (!foundItem || !(*foundItem))
			{
				UE_LOG(LogTemp, Log, TEXT("[Item] item not found... ID %llu Not found"), itemID);
				return;
			}

			ABaseItem* item = *foundItem;

			// Player
			AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);
			if (foundPlayer && *foundPlayer)
			{
				(*foundPlayer)->PlayPickUpAnimation(item);

				// _items에서 제거
				_items.Remove(itemID);

				UE_LOG(LogTemp, Warning, TEXT("[Item] OtherPlayer ID %llu Item PickUp Animation!"), playerID);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("[Item] OtherPlayer ID %llu not found in map!"), playerID);
		}
	});
}

void UMain::RecvUpdateCurrentTool(S_UpdateCurrentTool_Packet packet)
{
	uint32 playerID = packet.playerID;
	ItemType itemType = packet.itemType;
	uint32 itemID = packet.itemID;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
		{
			UWorld* world = GetWorld();
			if (!world) return;

			// MyPlayer가 잘못된 도구를 들고있다면
			if (playerID == _myID)
			{
				APlayerController* PC = world->GetFirstPlayerController();
				if (PC)
				{
					AMyPlayer* myPlayer = Cast<AMyPlayer>(PC->GetPawn());
					if (myPlayer)
					{
						myPlayer->UpdateToolVisual();
						UE_LOG(LogTemp, Log, TEXT("[Tool] MyPlayer Tool Visual Updated."));
					}
				}
			}
			// OtherPlayer
			else
			{
				AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);
				if (foundPlayer && *foundPlayer)
				{
					(*foundPlayer)->UpdateTool(itemType);
					UE_LOG(LogTemp, Log, TEXT("[Tool] OtherPlayer ID %u Updated Tool to Type %d"), playerID, (int32)itemType);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[Tool] OtherPlayer ID %u not found in _otherPlayers map!"), playerID);
				}
			}
		});
}

void UMain::RecvUseTool(S_UseTool_Packet packet)
{
	int playerID = packet.playerID;
	ItemType toolType = packet.toolType;

	if (playerID == _myID)
		return;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		// OtherPlayer Animation
		AOtherPlayer** foundPlayer = _otherPlayers.Find(playerID);
		if (foundPlayer && *foundPlayer)
		{
			(*foundPlayer)->PlayUseToolAnimation(toolType);
		}
	});
}

void UMain::RecvSpawnParticle(S_SpawnParticle_Packet packet)
{
}

void UMain::RecvInteractDoorNotify(S_InteractDoorNotify_Packet packet)
{
	int doorID = packet.doorID;
	ObjectState state = packet.doorState;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		ABaseDoor** foundDoor = _doors.Find(doorID);
		if (foundDoor && *foundDoor)
		{
			(*foundDoor)->UpdateDoorState(state);
			UE_LOG(LogTemp, Log, TEXT("[Door] DoorID %d State Updated to %d"), doorID, (int)state);
		}
	});
}

void UMain::RecvSpawnMonster(S_SpawnMonster_Packet packet)
{
	if (_monsters.Contains(packet.id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster already spawned... object ID: %d"), packet.id);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, packet.rotation.yaw, 0);
	int id = packet.id;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world || !OtherPlayerClass)
			return;

		ABaseMonster* monsterActor = nullptr;
		switch (packet.type)
		{
		default:
		case MonsterType::None:
			monsterActor = world->SpawnActor<ABaseMonster>(TestMonsterClass, spawnLocation, spawnRotation);			
			break;
		case MonsterType::Spider:
			monsterActor = world->SpawnActor<ABaseMonster>(SpiderClass, spawnLocation, spawnRotation);
			break;
		}

		if (monsterActor)
		{
			_monsters.Add(id, monsterActor);
			monsterActor->SetTargetTransform(spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("Monster Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 30);
		}
		else
		{
			_monsters.Remove(id);
			UE_LOG(LogTemp, Error, TEXT("Monster Spawn Failed... ID [%d]"), id);
		}
	});
}

void UMain::RecvTurnOnLantern(S_TurnOnLantern_Packet packet)
{
}

void UMain::RecvTurnOffLantern(S_TurnOffLantern_Packet packet)
{
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

TArray<class ABaseItem*> UMain::GetAllScanableItems()
{
	TArray<ABaseItem*> CombinedList;

	for (auto& ItemPair : _items)
	{
		if (ItemPair.Value)
		{
			CombinedList.Add(ItemPair.Value);
		}
	}

	for (auto& ToolPair : _tools)
	{
		if (ToolPair.Value) 
		{
			CombinedList.Add(ToolPair.Value);
		}
	}

	return CombinedList;
}
