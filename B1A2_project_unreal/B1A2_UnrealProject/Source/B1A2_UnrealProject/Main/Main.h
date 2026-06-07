#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Network/UnrealPackets.h"
#include "Network/Includes.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "Animation/AnimMontage.h"

#include "Main.generated.h"

class DataManager;
class GameNetwork;
class NetworkRunnable;
class EmotionExtractionRunnable;
class FRunnableThread;

class AOtherPlayer;
class AMyPlayer;
class ABaseItem;
class ABaseDoor;
class ABaseHatch;
class ABaseSellingMachine;
class ABaseMonster;

// 매초 저장되는 감정 데이터 구조체
USTRUCT(BlueprintType)
struct FEmotionRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float Timestamp; // 경과 시간

	UPROPERTY(BlueprintReadOnly)
	TArray<float> Scores; // 7가지 감정 수치
};

UCLASS()
class B1A2_UNREALPROJECT_API UMain : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void ConnectServer();

	UFUNCTION(BlueprintCallable)
	void ConnectOpenCV();

	UFUNCTION(BlueprintCallable)
	void LoadQuestData();

	// Base 설치 (한 번 설치 후 게임이 완전히 끝날 때까지 삭제 X)
	void CreateBase();

	// Send
	void ProcessSend(PacketID id, const void* packetData, int dataSize);

	void SendLocalPosition();
	void SendGetItem(int itemID, bool isTool, int playerID);
	void SendDropItem(int playerID, bool isTool, int itemID);
	void SendDropItemToSellingMachine(int itemID, int playerID, int sellingMachineID);
	void SendSellItem(int playerID, int sellingMachineID);
	void SendChangeTool(int playerID, int toolID);
	void SendInteractDoor(int playerID, int doorID);
	void SendUseTool(int playerID, int toolID, Rotation playerRotation);
	void SendUseKey(int playerID, int toolID, int doorID);
	void SendChangeEmotion(int playerID, Emotion emotion);
	void SendEmotionResult(float angryTime, float disgustTime, float fearTime, float happyTime, float sadTime, float surpriseTime, float neutralTime);
	void SendEndStage(bool result);
	void SendStartStage(bool result);
	void SendUseLantern(int playerID, int lanternID);
	void SendBuyItem(int playerID, ItemType itemType, int itemCount);
	void SendSubmitItem(int itemID, int playerID);
	void SendRequestQuestReward(bool isMain);
	void SendLogin(const std::vector<char>& id);
	void SendLogout();


	// Recv
	void Update();
	void ProcessRecv();
	
	void RecvLoginResult(S_LoginResult_Packet packet);
	void RecvCurrentRoomList(S_CurrentRoomList_Packet packet);
	void RecvCreateRoomResultList(S_CreateRoomResult_Packet packet);

	void RecvAddPlayer(S_AddPlayer_Packet packet);

	void RecvAddItem(S_AddItem_Packet packet);
	void RecvAddTool(S_AddItem_Packet packet);
	void RecvDropItem(S_DropItem_Packet packet);

	void RecvRemoveObject(S_RemoveObject_Packet packet);
	void RemovePlayer(S_RemoveObject_Packet packet);
	void RemoveMonster(S_RemoveObject_Packet packet);
	void RemoveItem(S_RemoveObject_Packet packet);
	void RemoveTool(S_RemoveObject_Packet packet);

	void RecvMoveObject(S_Move_Packet packet);
	void RecvMovePlayer(S_Move_Packet packet);
	void RecvMoveMonster(S_Move_Packet packet);

	void RecvUpdateObjectState(S_UpdateObjectState_Packet packet);
	void RecvUpdateStateMonster(S_UpdateObjectState_Packet packet);
	void RecvUpdateStateDoor(S_UpdateObjectState_Packet packet);
	void RecvUpdateStateSellingMachine(S_UpdateObjectState_Packet packet);

	void RecvCreateCubes(S_CreateCubes_Packet packet);
	void RecvAddItemToInventory(S_AddItemToInventory_Packet packet);
	void RecvRemoveItemFromInventory(S_RemoveItemFromInventory_Packet packet);
	void RecvItemPickupNotify(S_ItemPickupNotify_Packet packet);
	void RecvUpdateCurrentTool(S_UpdateCurrentTool_Packet packet);
	void RecvUseTool(S_UseTool_Packet packet);
	void RecvSpawnParticle(S_SpawnParticle_Packet packet);
	void RecvInteractDoorNotify(S_InteractDoorNotify_Packet packet);
	void RecvAddMonster(S_AddMonster_Packet packet);
	void RecvTurnOnLantern(S_TurnOnLantern_Packet packet);
	void RecvTurnOffLantern(S_TurnOffLantern_Packet packet);

	void RecvEndStage(S_EndStage_Packet packet);
	void RecvStartStage(S_StartStage_Packet packet);

	void RecvUpdateHp(S_UpdateHp_Packet packet);
	void RecvAddObstacle(S_AddObstacle_Packet packet);

	void RecvEmotionGameResult(S_EmotionGameResult_Packet packet);
	void RecvSellItemResult(S_SellItemResult_Packet packet);
	void RecvBuyItemResult(S_BuyItemResult_Packet packet);

	void RecvUpdateQuest(S_UpdateQuest_Packet packet);
	void RecvUpdateQuestProgress(S_UpdateQuestProgress_Packet packet);
	void RecvUpdateCredit(S_UpdateCredit_Packet packet);

	FRotator DirToRotation(Dir dir);

	// ID
	int GetMyID() { return _myID; }

	// 감정 관련
	void HandleNewEmotionData(const TArray<float>& emotionScores);

	int32 GetCurrentCredit() { return _currentCredit; }

public:
	// Base Class
	UPROPERTY(EditDefaultsOnly, Category = "Base")
	TSubclassOf<AStaticMeshActor> BaseClass;

	// Room Box Class
	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> MainEntranceRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> GapRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> ApparatusRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> ServerRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> CabinetRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> PipedHallways_GridClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> PipedHallways_LineClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> RailCatwalkClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> StaircaseClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> StorageRoom_ConerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> StorageRoom_RectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> StorageRoom_StepClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> YellowOfficeRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> 	FactoryRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> 	Wall_FillerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<ABaseDoor> DoorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<ABaseHatch> HatchClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<ABaseSellingMachine> SellingMachineClass;

	// 몬스터
	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<ABaseMonster> SpiderClass;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<ABaseMonster> EmotionGameClass;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<ABaseMonster> GhostClass;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<ABaseMonster> PollutionMonitorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<ABaseMonster> TrashCollectorClass;

	// Monster Montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* SpiderMontage;

	// Item
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> CardboardBoxClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> GoldBarClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> RubberDuckClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> PlasticCrateClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> ScrewClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> PirateHatClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> HardHatClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> EngineCoreClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> ScrapMetalClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> EmptyCanClass;

	// Tool
	UPROPERTY(EditDefaultsOnly, Category = "Tool")
	TSubclassOf<class ABaseItem> CutlassClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tool")
	TSubclassOf<class ABaseItem> BlasterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tool")
	TSubclassOf<class ABaseItem> KeyClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tool")
	TSubclassOf<class ABaseItem> LanternClass;

private:
	DataManager* _dataManager = nullptr;
	GameNetwork* _gameNetwork = nullptr;

	// FRunnbale
	NetworkRunnable* _recvRunnable = nullptr;
	FRunnableThread* _recvThread = nullptr;
	EmotionExtractionRunnable* _emotionExtractionRunnable = nullptr;
	FRunnableThread* _emotionExtractionThread = nullptr;

	// 패킷 처리 주기
	FTimerHandle _packetProcessTimerHandle; 
	FTimerHandle _sendPositionTimerHandle;  

	// 다른 플레이어
	UPROPERTY(EditAnywhere)
	TSubclassOf<AOtherPlayer> OtherPlayerClass;

	TMap<uint64, AOtherPlayer*> _otherPlayers;		// ID, Character*

	// 내 플레이어
	AMyPlayer* _myPlayer;
	int _myID{-1};

	// 몬스터
	TMap<uint64, ABaseMonster*> _monsters;

	// 아이템
	TMap<uint64, ABaseItem*> _items;
	// 장비
	TMap<uint64, ABaseItem*> _tools;

	// 큐브
	TMap<uint64, AStaticMeshActor*> _cubes;

	// 문
	TMap<uint64, ABaseDoor*> _doors;
	ABaseHatch* _hatch;

	// 판매기
	TMap<uint64, ABaseSellingMachine*> _sellingMachines;

	// 거미줄
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WebClass;

	TMap<uint64, AActor*> _webs;

	// MainEntrance가 한 번만 생성되도록 체크하는 플래그
	bool isMainEntranceAlreadySpawned = false;

	// 누적 데이터 저장
	UPROPERTY()
	TArray<FEmotionRecord> EmotionHistory;

	float _totalElapsedTime = 0.0f;
	int32 _lastSentEmotionIndex = -1; // 마지막으로 보낸 감정 인덱스

	int32 _currentCredit = 0;

public:
	// 스캔 시 맵에 있는 아이템 + 장비 반환
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<class ABaseItem*> GetAllScanableItems();
};
