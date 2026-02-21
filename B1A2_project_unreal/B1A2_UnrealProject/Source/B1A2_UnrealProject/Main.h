#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Network/UnrealPackets.h"
#include "Network/Includes.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"

#include "Main.generated.h"

class GameNetwork;
class NetworkRunnable;
class EmotionExtractionRunnable;
class FRunnableThread;

class AOtherPlayer;
class AMyPlayer;
class ABaseItem;

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

	TArray<uint8> CreatePacket(PacketID id, const void* packetData, int dataSize);

	// Send
	void ProcessSend(PacketID id, const void* packetData, int dataSize);

	void SendLocalPosition();
	void SendGetItem(int itemID, int playerID);

	// Recv
	UFUNCTION(BlueprintCallable)	// 멀티 스레드 제거용 임시!!!
	void Update();
	void ProcessRecv();
	
	void RecvAddObject(S_AddObject_Packet packet);
	void AddPlayer(S_AddObject_Packet packet);
	void AddMonster(S_AddObject_Packet packet);

	void RecvAddItem(S_AddItem_Packet packet);
	
	void RecvRemoveObject(S_RemoveObject_Packet packet);
	void RemovePlayer(S_RemoveObject_Packet packet);
	void RemoveMonster(S_RemoveObject_Packet packet);
	void RemoveItem(S_RemoveObject_Packet packet);

	void RecvMoveObject(S_Move_Packet packet);
	void RecvMovePlayer(S_Move_Packet packet);
	void RecvMoveMonster(S_Move_Packet packet);

	void RecvUpdateObjectState(S_UpdateObjectState_Packet packet);
	void RecvCreateGameRoom(S_CreateGameRoom_Packet packet);

	FRotator DirToRotation(Dir dir);

	// ID
	int GetMyID() { return _myID; }

public:
	// Room Box Class
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> MainEntranceRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> GapRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> ApparatusRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> ServerRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> CabinetRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> PipedHallways_GridClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> PipedHallways_LineClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> RailCatwalkClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> StaircaseClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> StorageRoom_ConerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> StorageRoom_RectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> StorageRoom_StepClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> YellowOfficeRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> 	FactoryRoomClass;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TSubclassOf<AStaticMeshActor> 	Wall_FillerClass;

	// 몬스터
	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<AStaticMeshActor> TestMonsterClass;

	// Item
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class ABaseItem> CardboardBoxClass;

private:
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
	int _myID{};

	// 몬스터
	TMap<uint64, AStaticMeshActor*> _monsters;

	// 아이템
	TMap<uint64, ABaseItem*> _items;
};
