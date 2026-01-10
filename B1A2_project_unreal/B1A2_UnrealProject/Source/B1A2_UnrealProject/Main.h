#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Network/Packets.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"

#include "Main.generated.h"

class GameNetwork;
class NetworkRunnable;
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

	TArray<uint8> CreatePacket(PacketID id, const void* packetData, int dataSize);

	// Send
	void ProcessSend(PacketID id, const void* packetData, int dataSize);

	void SendLocalPosition();
	// Recv
	void Update();
	void ProcessRecv();
	
	void RecvAddObject(S_AddObject_Packet addObjectPacket);
	void RecvCreateGameRoom(S_CreateGameRoom_Packet packet);
	void RecvMovePlayer(S_Move_Packet packet);
	void RecvUpdateObjectState(S_UpdateObjectState_Packet packet);

public:
	// Room Box Class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> GameRoomClass;

private:
	GameNetwork* _gameNetwork = nullptr;

	// FRunnbale
	NetworkRunnable* _recvRunnable = nullptr;
	FRunnableThread* _recvThread = nullptr;

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
};
