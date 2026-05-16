#pragma once
#include "Packets.h"

class Room;

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();

public:
	// Recv
	void ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet);
	void ProcessMovePacket(C_Move_Packet packet);
	void ProcessGetItemPacket(SOCKET clientSocket, C_GetItem_Packet packet);
	void ProcessDropItemPacket(C_DropItem_Packet packet);
	void ProcessChangeToolPacket(C_ChangeTool_Packet packet);
	void ProcessUseToolPacket(C_UseTool_Packet packet);
	void ProcessUseKeyPacket(SOCKET clientSocket, C_UseKey_Packet packet);
	void ProcessInteractDoorPacket(C_InteractDoor_Packet packet);
	void ProcessEmotionPacket(C_Emotion_Packet packet);
	void ProcessUseLanternPacket(C_UseLantern_Packet packet);
	void ProcessStartStagePacket(C_StartStage_Packet packet);
	void ProcessEndStagePacket(C_EndStage_Packet packet);

public:
	Room* GetRoom() { return _room; }

private:
	Room* _room{};
};