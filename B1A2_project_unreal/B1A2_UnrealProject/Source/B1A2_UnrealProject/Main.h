#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Network/Packets.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"

#include "Main.generated.h"

class GameNetwork;
class NetworkRunnable;
class EmotionExtractionRunnable;
class FRunnableThread;

class AOtherPlayer;
class AMyPlayer;

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

	// Recv
	void Update();
	void ProcessRecv();
	
	void RecvAddObject(S_AddObject_Packet packet);
	void AddPlayer(S_AddObject_Packet packet);
	void AddMonster(S_AddObject_Packet packet);
	void RecvMovePlayer(S_Move_Packet packet);
	void RecvUpdateObjectState(S_UpdateObjectState_Packet packet);
	void RecvCreateGameRoom(S_CreateGameRoom_Packet packet);

	FRotator DirToRotation(Dir dir);

public:
	// Room Box Class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> MainEntranceRoomClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> GapRoomClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> ApparatusRoomClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> ServerRoomClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> CabinetRoomClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> PipedHallways_GridClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> PipedHallways_LineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> RailCatwalkClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> StaircaseClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> StorageRoom_ConerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> StorageRoom_RectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> StorageRoom_StepClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> YellowOfficeRoomClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> 	FactoryRoomClass;

	// 몬스터
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> TestMonsterClass;

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
};
