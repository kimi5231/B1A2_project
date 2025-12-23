#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Packets.h"
#include "GameFramework/Character.h"

#include "Main.generated.h"

class NetworkRunnable;
class FRunnableThread;

// Recv: Recv -> 게임
struct RecvData
{
	TArray<uint8> DataBuffer;
};

// Send: 게임 -> Send
struct SendData
{
	TArray<uint8> DataBuffer;
};

UCLASS()
class B1A2_UNREALPROJECT_API UMain : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	void GameTick();

	TArray<uint8> CreatePacket(PacketID id, const void* packetData, int dataSize);

	// Send
	bool ProcessSend(PacketID id, const void* packetData, int dataSize);
	
	void SendLocalPosition();

	// Recv
	void ProcessRecv();
	
	void RecvAddObject(int id, Vector initLocation, Rotation initRotation);
	void RecvMovePlayer(int id, Vector location, Rotation rotation);

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> OtherPlayerClass;

private:
	// FRunnbale
	NetworkRunnable* _networkRunnable = nullptr;
	FRunnableThread* _networkThread = nullptr;

	// 패킷 Queue
	TQueue<RecvData> _receivedQueue;
	TQueue<SendData> _sendQueue;

	// 패킷 처리 주기
	FTimerHandle _packetProcessTimerHandle; 
	FTimerHandle _sendPositionTimerHandle;  

	// 다른 플레이어
	UPROPERTY()
	TMap<int32, ACharacter*> _otherPlayers;		// ID, Character*

	int _myID{};
};
