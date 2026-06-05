#include "Main.h"
#include "Thread/NetworkRecvRunnable.h"
#include "Thread/EmotionExtractionRunnable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayer.h"
#include "Player/OtherPlayer.h"
#include "Network/GameNetwork.h"
#include "Interactable/BaseItem.h"
#include "Interactable/Lantern.h"
#include "Interactable/BaseDoor.h"
#include "Interactable/BaseHatch.h"
#include "Interactable/BaseSellingMachine.h"
#include "Widget/ToolBarWidget.h"
#include "Monster/BaseMonster.h"
#include "Monster/BaseEmotionGame.h"
#include "Widget/EmotionResultWidget.h"
#include "Widget/ShopWidget.h"
#include "Widget/QuestWidget.h"

#define BUFSIZE	64

void UMain::Init()
{
	Super::Init();

	// 시작할 때 카메라 연결
	//ConnectOpenCV();
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

	//_emotionExtractionRunnable->Init();
}

void UMain::CreateBase()
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		FVector pos(0, 0, 0);
		FRotator rot(0, 0, 0);

		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AStaticMeshActor* BaseActor = world->SpawnActor<AStaticMeshActor>(BaseClass, pos, rot, params);
		UE_LOG(LogTemp, Log, TEXT("[Base] Base Spawned!"));
	});
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
		case S_LoginResult:
		{
			S_LoginResult_Packet loginResultPacket;
			FMemory::Memcpy(&loginResultPacket, event->serializedPacketData.data(), sizeof(S_LoginResult_Packet));
			RecvLoginResult(loginResultPacket);
			event->isComplete = true;
			break;
		}
		case S_AddPlayer:
		{
			S_AddPlayer_Packet addPlayerPacket;
			FMemory::Memcpy(&addPlayerPacket, event->serializedPacketData.data(), sizeof(S_AddPlayer_Packet));
			RecvAddPlayer(addPlayerPacket);
			event->isComplete = true;
			break;
		}
		case S_AddMonster:
		{
			S_AddMonster_Packet addMonsterPacket;
			FMemory::Memcpy(&addMonsterPacket, event->serializedPacketData.data(), sizeof(S_AddMonster_Packet));
			RecvAddMonster(addMonsterPacket);
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
		case S_AddObstacle:
		{
			S_AddObstacle_Packet addobsraclePacket;
			FMemory::Memcpy(&addobsraclePacket, event->serializedPacketData.data(), sizeof(S_AddObstacle_Packet));
			RecvAddObstacle(addobsraclePacket);
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
		case S_Move:
		{
			S_Move_Packet movePacket;
			FMemory::Memcpy(&movePacket, event->serializedPacketData.data(), sizeof(S_Move_Packet));
			RecvMoveObject(movePacket);
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
		case S_CreateCubes:
		{
			unsigned short packetSize;
			memcpy(&packetSize, event->serializedPacketData.data(), sizeof(unsigned short));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned short) + sizeof(PacketID));
			S_CreateCubes_Packet createCubesPacket{ packetSize, S_CreateCubes, _gameNetwork->DeserializeVector<CubeDTO>(event->serializedPacketData), _gameNetwork->DeserializeVector<DoorDTO>(event->serializedPacketData), _gameNetwork->DeserializeVector<SellingMachineDTO>(event->serializedPacketData) };
			RecvCreateCubes(createCubesPacket);
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
		{
			S_UseTool_Packet useToolPacket;
			FMemory::Memcpy(&useToolPacket, event->serializedPacketData.data(), sizeof(S_UseTool_Packet));
			RecvUseTool(useToolPacket);
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
		case S_InteractDoorNotify:
		{
			S_InteractDoorNotify_Packet interactDoorNotifyPacket;
			FMemory::Memcpy(&interactDoorNotifyPacket, event->serializedPacketData.data(), sizeof(S_InteractDoorNotify_Packet));
			RecvInteractDoorNotify(interactDoorNotifyPacket);
			event->isComplete = true;
			break;
		}
		case S_SellItemResult:
		{
			unsigned short packetSize;
			memcpy(&packetSize, event->serializedPacketData.data(), sizeof(unsigned short));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned short) + sizeof(PacketID));
			unsigned char sellingMachineID;
			memcpy(&sellingMachineID, event->serializedPacketData.data(), sizeof(unsigned char));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned char));
			unsigned char playerID;
			memcpy(&playerID, event->serializedPacketData.data(), sizeof(unsigned char));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned char));
			unsigned short remainCredit;
			memcpy(&remainCredit, event->serializedPacketData.data(), sizeof(unsigned short));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned short));
			unsigned short collectCredit;
			memcpy(&collectCredit, event->serializedPacketData.data(), sizeof(unsigned short));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned short));
			unsigned short currentCredit;
			memcpy(&currentCredit, event->serializedPacketData.data(), sizeof(unsigned short));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(unsigned short));
			ObjectState sellingMachineState;
			memcpy(&sellingMachineState, event->serializedPacketData.data(), sizeof(ObjectState));
			event->serializedPacketData.erase(event->serializedPacketData.begin(), event->serializedPacketData.begin() + sizeof(ObjectState));

			S_SellItemResult_Packet sellItemResultPacket{ packetSize, S_SellItemResult, sellingMachineID, playerID, remainCredit, collectCredit, currentCredit, sellingMachineState, _gameNetwork->DeserializeVector<char>(event->serializedPacketData) };
			RecvSellItemResult(sellItemResultPacket);
			event->isComplete = true;
			break;
		}
		case S_BuyItemResult:
		{
			S_BuyItemResult_Packet buyItemResultPacket;
			FMemory::Memcpy(&buyItemResultPacket, event->serializedPacketData.data(), sizeof(S_BuyItemResult_Packet));
			RecvBuyItemResult(buyItemResultPacket);
			event->isComplete = true;
			break;
		}
		case S_UpdateHp:
		{
			S_UpdateHp_Packet updateHpPacket;
			FMemory::Memcpy(&updateHpPacket, event->serializedPacketData.data(), sizeof(S_UpdateHp_Packet));
			RecvUpdateHp(updateHpPacket);
			event->isComplete = true;
			break;
		}
		case S_EmotionGameResult:
		{
			S_EmotionGameResult_Packet emotionGameResultPacket;
			FMemory::Memcpy(&emotionGameResultPacket, event->serializedPacketData.data(), sizeof(S_EmotionGameResult_Packet));
			RecvEmotionGameResult(emotionGameResultPacket);
			event->isComplete = true;
			break;
		}
		case S_SpawnParticle:
		{
			S_SpawnParticle_Packet spawnParticlePacket;
			FMemory::Memcpy(&spawnParticlePacket, event->serializedPacketData.data(), sizeof(S_SpawnParticle_Packet));
			RecvSpawnParticle(spawnParticlePacket);
			event->isComplete = true;
			break;
		}
		case S_StartStage:
		{
			S_StartStage_Packet startStagePacket;
			FMemory::Memcpy(&startStagePacket, event->serializedPacketData.data(), sizeof(S_StartStage_Packet));
			RecvStartStage(startStagePacket);
			event->isComplete = true;
			break;
		}
		case S_EndStage:
		{
			S_EndStage_Packet endStagePacket;
			FMemory::Memcpy(&endStagePacket, event->serializedPacketData.data(), sizeof(S_EndStage_Packet));
			RecvEndStage(endStagePacket);
			event->isComplete = true;
			break;
		}
		case S_UpdateQuest:
		{
			S_UpdateQuest_Packet updateQuestPacket;
			FMemory::Memcpy(&updateQuestPacket, event->serializedPacketData.data(), sizeof(S_UpdateQuest_Packet));
			RecvUpdateQuest(updateQuestPacket);
			event->isComplete = true;
			break;
		}
		case S_UpdateQuestProgress:
		{
			S_UpdateQuestProgress_Packet updateQuestProgressPacket;
			FMemory::Memcpy(&updateQuestProgressPacket, event->serializedPacketData.data(), sizeof(S_UpdateQuestProgress_Packet));
			RecvUpdateQuestProgress(updateQuestProgressPacket);
			event->isComplete = true;
			break;
		}
		case S_UpdateCredit:
		{
			S_UpdateCredit_Packet updateCreditPacket;
			FMemory::Memcpy(&updateCreditPacket, event->serializedPacketData.data(), sizeof(S_UpdateCredit_Packet));
			RecvUpdateCredit(updateCreditPacket);
			event->isComplete = true;
			break;
		}
		}
	}
}

void UMain::RecvLoginResult(S_LoginResult_Packet packet)
{
}

void UMain::ProcessSend(PacketID id, const void* packetData, int dataSize)
{
}

void UMain::SendLocalPosition()
{
	if (_myID == -1)
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
	if (_myID == -1 || itemID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world) return;

	_gameNetwork->SendGetItemPacket(itemID, isTool, playerID);
}

void UMain::SendDropItem(int playerID, bool isTool, int itemID)
{
	if (_myID == -1 || itemID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendDropItemPacket(itemID, isTool, playerID);
}

void UMain::SendDropItemToSellingMachine(int itemID, int playerID, int sellingMachineID)
{
	if (_myID == -1 || itemID == -1 || sellingMachineID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendDropItemToSellingMachinePacket(itemID, playerID, sellingMachineID);
}

void UMain::SendSellItem(int playerID, int sellingMachineID)
{
	if (_myID == -1 || sellingMachineID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendSellItemPacket(playerID, sellingMachineID);
}

void UMain::SendChangeTool(int playerID, int toolID)
{
	if (_myID == -1 || toolID < 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendChangeToolPacket(playerID, toolID);
}

void UMain::SendInteractDoor(int playerID, int doorID)
{
	if (_myID == -1 || doorID < 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendInteractDoorPacket(playerID, doorID);
}

void UMain::SendUseTool(int playerID, int toolID, Rotation playerRotation)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendUseToolPacket(playerID, toolID, playerRotation);
}

void UMain::SendUseKey(int playerID, int toolID, int doorID)
{
	if (_myID == -1 || doorID < 0)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendUseKeyPacket(playerID, toolID, doorID);
}

void UMain::SendChangeEmotion(int playerID, Emotion emotion)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendChangeEmotionPacket(playerID, emotion);
}

void UMain::SendEmotionResult(float angry, float disgust, float fear, float happy, float sad, float surprise, float neutral)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendEmotionResultPacket(angry, disgust, fear, happy, sad, surprise, neutral);
}

void UMain::SendEndStage(bool result)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendEndStagePacket();
}

void UMain::SendStartStage(bool result)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendStartStagePacket();
}

void UMain::SendUseLantern(int playerID, int lanternID)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendUseLanternPacket(playerID, lanternID);
}

void UMain::SendBuyItem(int playerID, ItemType itemType, int itemCount)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendBuyItemPacket(playerID, itemType, itemCount);
}

void UMain::SendSubmitItem(int itemID, int playerID)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendSubmitItemPacket(itemID, playerID);
}

void UMain::SendRequestQuestReward(bool isMain)
{
	if (_myID == -1)
		return;

	UWorld* world = GetWorld();
	if (!world)
		return;

	_gameNetwork->SendRequestQuestRewardPacket(isMain);
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

void UMain::RecvAddPlayer(S_AddPlayer_Packet packet)
{
	if (_myID == -1)
	{
		// 자신의 ID 설정
		_myID = packet.id;

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

			UE_LOG(LogTemp, Log, TEXT("[Player] My Player Spawned! [%d], %f, %f, %f"), packet.id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z + 98.f);
		});
		return;
	}

	if (packet.id == _myID)
		return;

	// 이미 존재하는 객체인지 확인
	if (_otherPlayers.Contains(packet.id))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Player] Other Player already spawned... object ID: %d"), packet.id);
		return;
	}

	// 다른 플레이어 Spawn
	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z + 98.f);
	FRotator spawnRotation(0, packet.rotation.yaw, 0);
	int id = packet.id;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world || !OtherPlayerClass)
			return;

		AOtherPlayer* player = world->SpawnActor<AOtherPlayer>(OtherPlayerClass, spawnLocation, spawnRotation);

		if (player)
		{
			_otherPlayers.Add(id, player);
			UE_LOG(LogTemp, Log, TEXT("[Player] Other Player Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}
		else
		{
			_otherPlayers.Remove(id);
			UE_LOG(LogTemp, Error, TEXT("[Player] Other Spawn Failed... ID [%d]"), id);
		}
	});
}

void UMain::RecvAddItem(S_AddItem_Packet packet)
{
	if (_items.Contains(packet.id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item already spawned... object ID: %d"), packet.id);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, 0, 0);
	int id = packet.id;
	int cost = packet.cost;

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
		item->SetCost(cost);
		item->InitScanInfoWidget();

		// Spawn 후 Map에 등록
		_items.Add(id, item);	
	});
}

void UMain::RecvAddTool(S_AddItem_Packet packet)
{
	if (_tools.Contains(packet.id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tool already spawned... object ID: %d"), packet.id);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, 0, 0);
	int id = packet.id;
	int cost = packet.cost;

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
			tool = world->SpawnActor<ABaseItem>(KeyClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
			tool->SetItemType(ItemType::Key);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Key Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case ItemType::LANTERN:
			tool = world->SpawnActor<ABaseItem>(LanternClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
			tool->SetItemType(ItemType::LANTERN);
			UE_LOG(LogTemp, Log, TEXT("[Tool] Lantern Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}

		tool->SetItemID(id);
		tool->SetIsTool(true);
		tool->SetCost(cost);
		tool->InitScanInfoWidget();

		// Spawn 후 Map에 등록
		_tools.Add(id, tool);
	});
}

void UMain::RecvDropItem(S_DropItem_Packet packet)
{
	int playerID = packet.playerID;
	int itemID = packet.itemID;
	bool isTool = packet.isTool;
	int cost = packet.cost;
	int lanternBattery = packet.laternBattery;

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
				if (packet.itemType == ItemType::LANTERN)
				{
					_myPlayer->SetCurrentBattery(0.0f); // 배터리 0으로 초기화 (UI 표시)
					_myPlayer->SetIsLanternOn(false);	// 조명 끄기
				};

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
				tool = world->SpawnActor<ABaseItem>(KeyClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
				tool->SetItemType(ItemType::Key);
				UE_LOG(LogTemp, Log, TEXT("[Tool] Key Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
				break;
			case ItemType::LANTERN:
				tool = world->SpawnActor<ABaseItem>(LanternClass, (spawnLocation.X, spawnLocation.Y, spawnLocation), spawnRotation);
				tool->SetItemType(ItemType::LANTERN);

				// 여기서 Lanter의 배터리를 설정해줘야 함!!!!!!!!!
				//

				UE_LOG(LogTemp, Log, TEXT("[Tool] Lantern Spawned! [%d], %f, %f, %f"), itemID, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
				break;
			}

			tool->SetItemID(itemID);
			tool->SetIsTool(true);
			tool->SetCost(0);	// tool의 cost는 0
			tool->InitScanInfoWidget();

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
			item->SetCost(cost);
			item->InitScanInfoWidget();

			_items.Add(itemID, item);
		}
	});
}

void UMain::RecvRemoveObject(S_RemoveObject_Packet packet)
{
	switch (packet.type)
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
	int id = packet.id;

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
	int id = packet.id;

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
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		FVector pos(packet.pos.x, packet.pos.y, packet.pos.z + 98.f);
		FRotator rot(0, packet.rotation.yaw, 0);

		// MyPlayer인 경우
		if (packet.id == _myID)
		{
			if (_myPlayer)
			{
				_myPlayer->SetPlayerLocation(pos, rot); 
				_myPlayer->SetPlayerState(packet.state);

				UE_LOG(LogTemp, Display, TEXT("[Player] My Player [%d] Move Packet %f, %f"), packet.id, packet.pos.x, packet.pos.y);
			}
			return; // 내 캐릭터 처리가 끝났으므로 종료
		}

		// OtherPlayer인 경우
		AOtherPlayer** findPlayer = _otherPlayers.Find(packet.id);
		if (findPlayer && *findPlayer)
		{
			AOtherPlayer* player = (*findPlayer);
			player->SetPlayerLocation(pos, rot);
			player->SetPlayerState(packet.state);

			UE_LOG(LogTemp, Display, TEXT("[Player] Other Player [%d] Move Packet %f, %f"), packet.id, packet.pos.x, packet.pos.y);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[Player] Other Player [%d] not found"), packet.id);
		}
	});
}

void UMain::RecvMoveMonster(S_Move_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (!GetWorld()) return;

		ABaseMonster** findMonster = _monsters.Find(packet.id);
		if (findMonster && *findMonster)
		{
			ABaseMonster* monster = (*findMonster);

			FVector pos(packet.pos.x, packet.pos.y, packet.pos.z);
			FRotator rot(0, packet.rotation.yaw, 0);

			monster->SetTargetTransform(pos, rot);
		}
	});
}

void UMain::RecvUpdateObjectState(S_UpdateObjectState_Packet packet)
{
	if (packet.type == ObjectType::Monster)
		RecvUpdateStateMonster(packet);
	else if (packet.type == ObjectType::Door)
		RecvUpdateStateDoor(packet);
	else if (packet.type == ObjectType::SellingMachine)
		RecvUpdateStateSellingMachine(packet);
}

void UMain::RecvUpdateStateMonster(S_UpdateObjectState_Packet packet)
{
	// 상태 별 애니메이션 재생(지금은 Spider 몽타주만 재생!!)
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (!GetWorld()) return;

		ABaseMonster** findMonster = _monsters.Find(packet.id);
		if (findMonster && *findMonster)
		{
			ABaseMonster* monster = (*findMonster);

			// EmotionGame이 Grab 상태라면 모니터 바꾸기
			if (packet.state == ObjectState::GRAB)
			{
				// EmotionGame 몬스터로 캐스팅
				ABaseEmotionGame* emotionGame = Cast<ABaseEmotionGame>(monster);

				// 캐스팅 성공시 카운트다운 시작하여 내부적으로 모니터 3 - 2 - 1로 변경
				if (emotionGame)
				{
					UE_LOG(LogTemp, Warning, TEXT("[EmotionGame] Monster Grabbed Player! Starting Countdown..."));
					emotionGame->StartGrabCountdown();
				}
			}

			// Skeletal Mesh가 있는 몬스터라면, 컴포넌트 찾기
			USkeletalMeshComponent* meshComp = monster->FindComponentByClass<USkeletalMeshComponent>();

			if (meshComp)
			{
				UAnimInstance* AnimInstance = meshComp->GetAnimInstance();

				if (AnimInstance)
				{
					FName name = NAME_None;

					// 패킷 상태에 따른 섹션 이름 결정
					switch (packet.state)
					{
					case ObjectState::ATTACK:
						name = FName("Attack");
						break;
					case ObjectState::HIT:
						name = FName("Hit");
						break;
						/*case ObjectState::DIE:
							name = FName("Die");
							break;*/
					}

					// 유효한 섹션이 결정된 경우에만 재생
					if (!name.IsNone())
					{
						if (!AnimInstance->Montage_IsPlaying(SpiderMontage))
						{
							// 몽타주가 실행 중이 아니면 새로 시작
							AnimInstance->Montage_Play(SpiderMontage, 1.0f);
							AnimInstance->Montage_JumpToSection(name, SpiderMontage);
						}
						else
						{
							// 이미 재생 중이면 해당 섹션으로 즉시 점프
							AnimInstance->Montage_JumpToSection(name, SpiderMontage);
						}
					}
				}
			}
		}
	});
}

void UMain::RecvUpdateStateDoor(S_UpdateObjectState_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		ABaseDoor** foundDoor = _doors.Find(packet.id);

		if (foundDoor && *foundDoor)
		{
			(*foundDoor)->UpdateDoorState(packet.state);
		}
	});
}

void UMain::RecvUpdateStateSellingMachine(S_UpdateObjectState_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		ABaseSellingMachine** foundMachine = _sellingMachines.Find(packet.id);

		if (foundMachine && *foundMachine)
		{
			(*foundMachine)->UpdateMachineState(packet.state);
		}
	});
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

			if (cube.type == CubeType::MainEntranceRoom && isMainEntranceAlreadySpawned)
			{
				UE_LOG(LogTemp, Warning, TEXT("MainEntranceRoom already exists. Skipping spawn."));
				continue;
			}

			FVector pos(cube.pos.x, cube.pos.y, cube.pos.z);
			FRotator rot = DirToRotation(cube.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AStaticMeshActor* roomActor;
			switch (packet.cubes[i].type)
			{
			case CubeType::MainEntranceRoom:
				roomActor = world->SpawnActor<AStaticMeshActor>(MainEntranceRoomClass, pos, rot, params);
				isMainEntranceAlreadySpawned = true;	// 플래그 설정
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

			_cubes.Add(i, roomActor);
			UE_LOG(LogTemp, Log, TEXT("[Cube] Saved Cube [%d] to _cubes map"), i);
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
			else if (door.doorType == DoorType::Hatch)
			{
				ABaseHatch* hatchActor = world->SpawnActor<ABaseHatch>(HatchClass, pos, rot, params);
				hatchActor->SetHatchState(packet.doors[i].state);
				hatchActor->SetHatchID(packet.doors[i].id);
				hatchActor->SetHatchRotation(packet.doors[i].state);

				_hatch = hatchActor;

				UE_LOG(LogTemp, Log, TEXT("[Room] Hatch Spawned [%d] pos = %f, %f, %f, dir = %d"), i, door.pos.x, door.pos.y, door.pos.z, door.dir);
			}
			else if (door.doorType == DoorType::Wall)
			{
				AStaticMeshActor* wallActor = world->SpawnActor<AStaticMeshActor>(Wall_FillerClass, pos, rot, params);
				UE_LOG(LogTemp, Log, TEXT("[Room] Wall Spawned [%d] pos = %f, %f, %f, dir = %d"), i, door.pos.x, door.pos.y, door.pos.z, door.dir);
			}
		}

		for (int i = 0; i < packet.sellingMachines.size(); ++i)
		{
			const SellingMachineDTO& sm = packet.sellingMachines[i];

			FVector pos(sm.pos.x, sm.pos.y, sm.pos.z);
			FRotator rot = DirToRotation(sm.dir);

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ABaseSellingMachine* smActor;
			smActor = world->SpawnActor<ABaseSellingMachine>(SellingMachineClass, pos, rot, params);

			smActor->SetMachineID(sm.id);
			smActor->SetMachineState(sm.state);
			smActor->SetMaxCredit(sm.creditLimit);
			smActor->SetLeverLength(sm.state);	// 상태에 따라 레버 위치 설정

			_sellingMachines.Add(packet.sellingMachines[i].id, smActor);
			UE_LOG(LogTemp, Log, TEXT("[Room] SellingMachine Spawned [%d] pos = %f, %f, %f, dir = %d, creditLimit = %d"), packet.sellingMachines[i].id, sm.pos.x, sm.pos.y, sm.pos.z, sm.dir, sm.creditLimit);
		}
	});
}

void UMain::RecvAddItemToInventory(S_AddItemToInventory_Packet packet)
{
	int itemID = packet.id;
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
			int32 toolIndex = _myPlayer->AddToolToToolBar(packet.itemType, itemID, packet.weight, 0);	// 장비는 팔지 않으므로 0으로 설정

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

			// 랜턴일 경우 배터리 초기화
			if (packet.itemType == ItemType::LANTERN)
			{
				ALantern* lantern = Cast<ALantern>(tool);
				if (lantern)
				{
					// 바닥에 있던 랜턴의 배터리 잔량
					_myPlayer->SetCurrentBattery(lantern->GetBattery());
				}
			}

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
			_myPlayer->AddItemToInventory(packet.itemType, itemID, packet.weight, item->GetCost());
			// _items에서 제거
			_items.Remove(itemID);

			UE_LOG(LogTemp, Display, TEXT("[RecvAddItemToInventory] Item PickedUp and To Inventory"));
		}		
	});
}

void UMain::RecvRemoveItemFromInventory(S_RemoveItemFromInventory_Packet packet)
{
	int32 itemID = packet.id;
	bool isTool = packet.isTool;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (!_myPlayer)
		{
			UE_LOG(LogTemp, Warning, TEXT("[RecvRemoveItemFromInventory] MyPlayer is null!"));
			return;
		}
		
		// 장비 - 들고있는 열쇠 제거
		if (isTool)
		{
			if (UToolBarWidget* toolbar = Cast<UToolBarWidget>(_myPlayer->GetToolBarWidget()))
			{
				toolbar->RemoveToolByID(itemID);
				_myPlayer->OnToolSelectionChanged();

				UE_LOG(LogTemp, Display, TEXT("[RecvRemoveItemFromInventory] Tool %d removed from ToolBar"), itemID);
			}
		}
		// 아이템
		else
		{
			// 인벤에서 삭제
			_myPlayer->RemoveItemInInventoryByID(itemID);

			UE_LOG(LogTemp, Display, TEXT("[RecvRemoveItemFromInventory] Tool %d removed from Inventory"), itemID);
		}
	});
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

		// ID가 0이면 hatch
		if (doorID == 0)
		{
			_hatch->UpdateHatchState(state);
			UE_LOG(LogTemp, Log, TEXT("[Hatch] Hatch ID %d State Updated to %d"), doorID, (int)state);
		}
		// 나머지 아이디는 door
		else
		{
			ABaseDoor** foundDoor = _doors.Find(doorID);
			if (foundDoor && *foundDoor)
			{
				(*foundDoor)->UpdateDoorState(state);
				UE_LOG(LogTemp, Log, TEXT("[Door] DoorID %d State Updated to %d"), doorID, (int)state);
			}
		}
	});
}

void UMain::RecvAddMonster(S_AddMonster_Packet packet)
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
		switch (packet.monsterType)
		{
		default:
		case MonsterType::Spider:
			monsterActor = world->SpawnActor<ABaseMonster>(SpiderClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("Spider Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case MonsterType::EmotionGame:
			monsterActor = world->SpawnActor<ABaseMonster>(EmotionGameClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("EmotionGame Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case MonsterType::Ghost:
			monsterActor = world->SpawnActor<ABaseMonster>(GhostClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("Ghost Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case MonsterType::TrashCollector:
			monsterActor = world->SpawnActor<ABaseMonster>(TrashCollectorClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("TrashCollector Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		case MonsterType::PollutionMonitor:
			monsterActor = world->SpawnActor<ABaseMonster>(PollutionMonitorClass, spawnLocation, spawnRotation);
			UE_LOG(LogTemp, Log, TEXT("PollutionMonitor Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
			break;
		}

		if (monsterActor)
		{
			_monsters.Add(id, monsterActor);
			monsterActor->SetTargetTransform(spawnLocation, spawnRotation);
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
	// 랜턴 킴
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world) return;

		AOtherPlayer* targetPlayer = nullptr;

		if (packet.playerID == _myID)
		{
			targetPlayer = _myPlayer;
		}
		else
		{
			AOtherPlayer** findPlayer = _otherPlayers.Find(packet.playerID);
			if (findPlayer && *findPlayer)
			{
				targetPlayer = *findPlayer;
			}
		}

		if (targetPlayer)
		{
			// 현재 장착된 도구를 가져와 ALantern으로 캐스팅
			ALantern* lantern = Cast<ALantern>(targetPlayer->GetAttacthedToolActor());
			if (lantern)
			{
				// 패킷 데이터 변환 (unsigned char -> float)
				float range = static_cast<float>(packet.laternRange);
				float angle = packet.laternAngle;

				lantern->UpdateLantern(true, range * 200);	// 임시로 범위 늘림
			}

			// MyPlayer 전용 추가 로직 (잔량 동기화 및 상태 변수)
			if (packet.playerID == _myID && _myPlayer)
			{
				_myPlayer->SetIsLanternOn(true);
				_myPlayer->SetCurrentBattery(static_cast<float>(packet.laternBattery));

				UE_LOG(LogTemp, Display, TEXT("[MyPlayer] Lantern ON. Battery: %d"), packet.laternBattery);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("[OtherPlayer] ID %d Lantern ON"), packet.playerID);
			}
		}
	});
}

void UMain::RecvTurnOffLantern(S_TurnOffLantern_Packet packet)
{
	// 랜턴 끔
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world) return;

		AOtherPlayer* targetPlayer = nullptr;

		if (packet.playerID == _myID)
		{
			targetPlayer = _myPlayer;
		}
		else
		{
			AOtherPlayer** findPlayer = _otherPlayers.Find(packet.playerID);
			if (findPlayer && *findPlayer)
			{
				targetPlayer = *findPlayer;
			}
		}

		if (targetPlayer)
		{
			ALantern* lantern = Cast<ALantern>(targetPlayer->GetAttacthedToolActor());
			if (lantern)
			{
				lantern->UpdateLantern(false, 0.f);
			}

			if (packet.playerID == _myID && _myPlayer)
			{
				_myPlayer->SetIsLanternOn(false);
				_myPlayer->SetCurrentBattery(static_cast<float>(packet.laternBattery));

				UE_LOG(LogTemp, Display, TEXT("[MyPlayer] Lantern OFF. Battery: %d"), packet.laternBattery);
			}
		}
	});
}

void UMain::RecvEndStage(S_EndStage_Packet packet)
{
	// 연출 ~~~
	// 방 닫기 ~~~
}

void UMain::RecvStartStage(S_StartStage_Packet packet)
{
	// 기지(현재는 MainEntrance) 빼고 큐브, 문 다 지우기
	AsyncTask(ENamedThreads::GameThread, [this, packet]()
	{
		// Cube 제거
		for (auto It = _cubes.CreateIterator(); It; ++It)
		{
			AStaticMeshActor* CubeActor = It.Value();

			if (CubeActor && CubeActor->IsValidLowLevel())
			{
				// MainEntrance는 지우지 않음
				if (CubeActor->GetClass() == MainEntranceRoomClass)
				{
					continue;
				}

				// 월드에서 액터 삭제
				CubeActor->Destroy();
			}

			// 맵에서 제거
			It.RemoveCurrent();
		}

		// Door & Wall 제거
		for (auto It = _doors.CreateIterator(); It; ++It)
		{
			ABaseDoor* DoorActor = It.Value();

			if (DoorActor && DoorActor->IsValidLowLevel())
			{
				DoorActor->Destroy();
			}

			// 맵에서 제거
			It.RemoveCurrent();
		}
	});
}

void UMain::RecvUpdateHp(S_UpdateHp_Packet packet)
{
	int id = packet.playerID;
	float hp = packet.hp;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (id != _myID)
			return;

		_myPlayer->SetCurrentHp(hp);

		UE_LOG(LogTemp, Log, TEXT("[Stat] Local HP Updated to: %f"), hp);
	});
}

void UMain::RecvAddObstacle(S_AddObstacle_Packet packet)
{
	if (_webs.Contains(packet.id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Web already spawned... object ID: %d"), packet.id);
		return;
	}

	FVector spawnLocation(packet.pos.x, packet.pos.y, packet.pos.z);
	FRotator spawnRotation(0, 0, 0);
	int id = packet.id;

	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		UWorld* world = GetWorld();
		if (!world) return;

		AActor* webActor = world->SpawnActor<AActor>(WebClass, spawnLocation, spawnRotation);

		if (webActor)
		{
			_webs.Add(id, webActor);
			webActor->SetActorLocation(spawnLocation);
			UE_LOG(LogTemp, Log, TEXT("Web Spawned! [%d], %f, %f, %f"), id, spawnLocation.X, spawnLocation.Y, spawnLocation.Z);
		}
		else
		{
			_webs.Remove(id);
			UE_LOG(LogTemp, Display, TEXT("Web Spawn Failed... ID [%d]"), id);
		}
	});
}

void UMain::RecvEmotionGameResult(S_EmotionGameResult_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (!GetWorld()) return;

		// 1. 플레이어 hp 수정
		if (_myID == packet.playerID)
		{
			if (_myPlayer)
				_myPlayer->SetCurrentHp(packet.playerHP);
		}

		// 2. 몬스터 디스플레이 변경(몬스터가 낸 감정 2초 -> Win Lose Draw 결과 3초 -> Idle)
		ABaseMonster** findMonster = _monsters.Find(packet.monsterID);
		if (findMonster && *findMonster)
		{
			ABaseEmotionGame* emotionMonster = Cast<ABaseEmotionGame>(*findMonster);
			if (emotionMonster)
			{
				FString emotionString = TEXT("Idle");
				switch (packet.monsterEmotion)
				{
				case Emotion::Happy:   emotionString = TEXT("Happy"); break;
				case Emotion::Sad:     emotionString = TEXT("Sad"); break;
				case Emotion::Neutral: emotionString = TEXT("Neutral"); break;
				}

				FString resultString = TEXT("Idle");
				switch (packet.result)
				{
				case EmotionGameResult::Win:  resultString = TEXT("Win"); break;
				case EmotionGameResult::Lose: resultString = TEXT("Lose"); break;
				case EmotionGameResult::Draw: resultString = TEXT("Draw"); break;
				}

				// 모니터 출력
				emotionMonster->PlayGameResultSequence(emotionString, resultString);
			}
		}
	});
}

void UMain::RecvSellItemResult(S_SellItemResult_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		if (!GetWorld()) return;

		int32 machineID = packet.sellingMachineID;
		
		if (_sellingMachines.Contains(machineID))
		{
			ABaseSellingMachine* machine = _sellingMachines[machineID];
			if (machine)
			{
				// 올려놨던 아이템 가격 초기화, 위젯 갱신
				machine->ResetPendingCredit();

				// 상태는 바꾸지 않고 레버 업 -> 3초 대기 -> 레버 다운 연출
				machine->PlaySellAnimation();

				UE_LOG(LogTemp, Log, TEXT("[SellingMachine] Machine ID %d: Credit Updated to %d. Playing 3s Animation."),
					packet.sellingMachineID, packet.currentCredit);
			}
		}

		// 월드 & 맵에서 아이템 제거
		for (char id : packet.itemIDs)
		{
			uint64 itemID = static_cast<uint64>(id);

			if (_items.Contains(itemID))
			{
				ABaseItem* itemActor = _items[itemID];
				if (itemActor)
				{
					// 월드에서 액터 삭제
					itemActor->Destroy();
					UE_LOG(LogTemp, Log, TEXT("[SellingMachine] Item ID %lld Destroyed from World."), itemID);
				}

				// 맵에서 제거
				_items.Remove(itemID);
			}
		}

		// 플레이어 크레딧(공용) 변경, Shop에 연결된 값도 갱신
		_currentCredit = packet.currentCredit;
		_myPlayer->GetShopWidget()->SetCurrentCredit(packet.currentCredit);
		_myPlayer->GetShopWidget()->UpdateUI();
		UE_LOG(LogTemp, Display, TEXT("[Sell] Recv Sell Item Result, currentCredit %d"), packet.currentCredit);
	});
}

void UMain::RecvBuyItemResult(S_BuyItemResult_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		// 현재 크레딧 변경
		_currentCredit = packet.currentCredit;

		// 위젯 변수 업데이트
		_myPlayer->GetShopWidget()->SetCurrentCredit(packet.currentCredit);
		_myPlayer->GetShopWidget()->UpdateUI();

		UE_LOG(LogTemp, Display, TEXT("[Buy] Recv Buy Item Result, currentCredit %d"), packet.currentCredit);
	});
}

void UMain::RecvUpdateCredit(S_UpdateCredit_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		// 현재 크레딧 변경
		_currentCredit = packet.currentCredit;

		// 위젯 변수 업데이트
		_myPlayer->GetShopWidget()->SetCurrentCredit(packet.currentCredit);
		_myPlayer->GetShopWidget()->UpdateUI();

		UE_LOG(LogTemp, Display, TEXT("[Credit] Recv Update Credit, currentCredit %d"), packet.currentCredit);
	});
}

void UMain::RecvUpdateQuest(S_UpdateQuest_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		bool isMain = packet.isMain;
		int questID = packet.questID;
		int goalCount = packet.goalCount;
		ItemType type = packet.itemType;
		int deadLine = packet.deadLine;

		_myPlayer->GetQuestWidget()->HandleUpdateQuest(isMain, questID, goalCount, type, deadLine);
	});
}

void UMain::RecvUpdateQuestProgress(S_UpdateQuestProgress_Packet packet)
{
	AsyncTask(ENamedThreads::GameThread, [=, this]()
	{
		bool isMain = packet.isMain;
		int currentCount = packet.currentCount;

		_myPlayer->GetQuestWidget()->HandleUpdateQuestProgress(isMain, currentCount);
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

void UMain::HandleNewEmotionData(const TArray<float>& emotionScores)
{	if (!_myPlayer)
			return;
	
	if (emotionScores.Num() < 7) 
		return;
	
	// 게임 결과 최종 계산 용
	_totalElapsedTime += 1.f;
	FEmotionRecord newRecord;
	newRecord.Timestamp = _totalElapsedTime;
	newRecord.Scores = emotionScores;
	EmotionHistory.Add(newRecord);

	// 현재 프레임에서 가장 높은 감정 찾기
	int32 maxIndex = 0;
	float maxScore = -1.f;
	for (int i = 0; i < 7; ++i)
	{
		if (emotionScores[i] > maxScore)
		{
			maxScore = emotionScores[i];
			maxIndex = i;
		}
	}

	// 감정이 바뀔 때만
	if (maxIndex != _lastSentEmotionIndex)
	{
		// UI 이모지 변경
		UEmotionResultWidget* EmotionWidget = Cast<UEmotionResultWidget>(_myPlayer->GetEmotionResultWidget());
		if (EmotionWidget)
			EmotionWidget->SetEmotion(maxIndex);

		// 서버로 감정 Send
		Emotion highestEmotion = static_cast<Emotion>(maxIndex);	// 가장 높은 감정
		SendChangeEmotion(_myID, highestEmotion);

		// 마지막 전송 상태 갱신
		_lastSentEmotionIndex = maxIndex;
		UE_LOG(LogTemp, Warning, TEXT("[Emotion] State Changed to index [%d]. Packet Sent!"), maxIndex);
	}
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
