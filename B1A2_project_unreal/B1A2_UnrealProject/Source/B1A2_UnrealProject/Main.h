#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Packets.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"

#include "Main.generated.h"

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
	void RecvMovePlayer(int id, Vector location, Rotation rotation);

public:
	// Other Player Class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> OtherPlayerClass;

	// Room Box Class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStaticMeshActor> GameRoomClass;

private:
	// FRunnbale
	NetworkRunnable* _recvRunnable = nullptr;
	FRunnableThread* _recvThread = nullptr;

	// 패킷 처리 주기
	FTimerHandle _packetProcessTimerHandle; 
	FTimerHandle _sendPositionTimerHandle;  

	// 다른 플레이어
	UPROPERTY(EditAnywhere)
	TSubclassOf<AOtherPlayer> _otherPlayerClass;

	UPROPERTY()
	TMap<int32, AOtherPlayer*> _otherPlayers;		// ID, Character*

	// 내 플레이어
	UPROPERTY()
	AMyPlayer* _myPlayer;

	int _myID{};
};
