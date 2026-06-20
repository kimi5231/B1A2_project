#pragma once

#include "Network/UnrealPackets.h"
#include "Network/Includes.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "Animation/AnimMontage.h"
#include <atomic>

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

class UPlayerMicComponent;

class UNiagaraSystem;

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
	void ProcessSendFinalEmotion();	// 최종 감정 데이터 계산 후 서버 전송 후 변수 초기화

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
	void SendCreateRoom();
	void SendEnterRoom(char roomID);

	// Recv
	void Update();
	void ProcessRecv();
	
	void RecvSignupResult(S_SignupResult_Packet packet);
	void RecvLoginResult(S_LoginResult_Packet packet);
	void RecvCurrentRoomList(S_CurrentRoomList_Packet packet);
	void RecvCreateRoomResultList(S_CreateRoomResult_Packet packet);
	void RecvEnterRoomResultList(S_EnterRoomResult_Packet packet);

	void RecvAddPlayer(S_AddPlayer_Packet packet);

	void RecvAddItem(S_AddItem_Packet packet);
	void RecvAddTool(S_AddItem_Packet packet);
	void RecvDropItem(S_DropItem_Packet packet);

	void RecvRemoveObject(S_RemoveObject_Packet packet);
	void RemovePlayer(S_RemoveObject_Packet packet);
	void RemoveMonster(S_RemoveObject_Packet packet);
	void RemoveItem(S_RemoveObject_Packet packet);
	void RemoveObstacle(S_RemoveObject_Packet packet);
	void RemoveDoor(S_RemoveObject_Packet packet);
	void RemoveSellingMachine(S_RemoveObject_Packet packet);

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
	void RecvGameOver(S_GameOver_Packet packet);

	void RecvUpdateHp(S_UpdateHp_Packet packet);
	void RecvAddObstacle(S_AddObstacle_Packet packet);

	void RecvEmotionGameResult(S_EmotionGameResult_Packet packet);
	void RecvSellItemResult(S_SellItemResult_Packet packet);
	void RecvBuyItemResult(S_BuyItemResult_Packet packet);

	void RecvUpdateQuest(S_UpdateQuest_Packet packet);
	void RecvUpdateQuestProgress(S_UpdateQuestProgress_Packet packet);
	void RecvUpdateCredit(S_UpdateCredit_Packet packet);
	void RecvUpdateTimer(S_UpdateTimer_Packet packet);

	void RecvVoiceData(S_VoiceData_Packet packet);

	FRotator DirToRotation(Dir dir);

	// ID
	int GetMyID() { return _myID; }

	// 감정 관련
	void HandleNewEmotionData(const TArray<float>& emotionScores);

	int32 GetCurrentCredit() { return _currentCredit; }

private:
	// 맵 로드가 완료됐을 때, C_EnterGame을 송신하기 위한 콜백 함수
	void OnLevelLoadComplete(UWorld* loadedWorld);

	// 메뉴에서 게임 레벨로 전환 중인지 여부
	std::atomic<bool> _bIsLoadingGameLevel{ false };

private:
	UPROPERTY()
	UPlayerMicComponent* MicCaptureComponent;

	// 내 마이크 캡처 시 호출될 콜백 함수
	void OnLocalVoiceCaptured(const TArray<uint8>& RawBytes);

public:
	// Dies Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraSystem* DieEffect;

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
	TSubclassOf<ABaseHatch> HatchClass;		// 상호작용 가능 Hatch

	UPROPERTY(EditDefaultsOnly, Category = "Cube")
	TSubclassOf<AStaticMeshActor> BaseHatchClass;	// 상호작용 안 되는 Hatch

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* TrashCollectorMontage;

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

	DataManager* GetDataManager() { return _dataManager; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	TSoftObjectPtr<UWorld> MainGameLevel;

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
	int _clientID{ -1 };

	// 몬스터
	UPROPERTY()
	TMap<uint64, ABaseMonster*> _monsters;

	// 아이템
	UPROPERTY()
	TMap<uint64, ABaseItem*> _items;
	// 장비
	UPROPERTY()
	TMap<uint64, ABaseItem*> _tools;

	// 큐브
	UPROPERTY()
	TArray<AStaticMeshActor*> _cubes;

	// 문
	UPROPERTY()
	TMap<uint64, ABaseDoor*> _doors; // id > 0

	// Wall
	UPROPERTY()
	TArray<AStaticMeshActor*> _walls;

	// Hatch
	UPROPERTY()
	ABaseHatch* _hatch;	// id == 0
	UPROPERTY()
	AStaticMeshActor* _baseHatch;

	// 상호작용 없는 hatch(스테이지 시작 전, 스테이지 끝나고)
	UPROPERTY()
	AStaticMeshActor* _baseActor = nullptr;

	// 판매기
	UPROPERTY()
	TMap<uint64, ABaseSellingMachine*> _sellingMachines;

	// 거미줄
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WebClass;

	UPROPERTY()
	TMap<uint64, AActor*> _webs;

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

	// EndStage 패킷 받으면 띄울 Game Result 패킷
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UGameResultWidget> GameResultWidgetClass;
};
