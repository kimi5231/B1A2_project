#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"
#include "Player.h"
#include "Cube.h"
#include "Item.h"
#include "Tool.h"
#include "Door.h"
#include "Lantern.h"
#include "Obstacle.h"
#include "ServerNetwork.h"

ServerFramework::ServerFramework()
{
	// Room 생성
	_room = new Room();
	_room->Init();
}

ServerFramework::~ServerFramework()
{
	delete _room;
}

void ServerFramework::Update()
{
	_room->Update();
}

void ServerFramework::ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet)
{
	//GameObjectRef object = _room->GetGameObject(packet.type, packet.objectID);

	//object->SetState(packet.state);

	//// 자신을 제외한 모든 클라이언트에게 알리기
	//for (ClientRef client : _clients)
	//{
	//	if (client->player->GetID() != packet.objectID)
	//		SendUpdateObjectStatePacket(object, false, client->socket);
	//}
}

void ServerFramework::ProcessMovePacket(C_Move_Packet packet)
{
	//GameObjectRef object = _room->GetGameObject(packet.type, packet.objectID);

	//if (object == nullptr)
	//	return;

	//object->SetPos(packet.pos);
	//object->SetRotation(packet.rotation);
	//object->SetState(packet.state);

	//// 자신을 제외한 모든 클라이언트에게 알리기
	//for (ClientRef client : _clients)
	//{
	//	if (client->player->GetID() != packet.objectID)
	//		SendMovePacket(object, false, client->socket);
	//}
}

void ServerFramework::ProcessGetItemPacket(SOCKET clientSocket, C_GetItem_Packet packet)
{
	//// Player가 요청한 아이템이 얻을 수 있는 것인지 확인
	//ItemRef item = std::dynamic_pointer_cast<Item>(_room->GetGameObject(ObjectType::Item, packet.itemID));
	//if (item->GetObjectPoolState() != ObjectPoolState::InWorld)
	//	return;

	//// 아이템을 얻을 수 있는 조건인지 확인(거리)
	//
	//// 얻을 수 있는 아이템이라면 Player 인벤토리에 추가
	//PlayerRef player = std::dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//// 아이템이 제대로 추가되었다면
	//if (player->AddItemToInventory(packet.isTool, packet.itemID))
	//{
	//	// 획득한 아이템 ObjectPoolState 변경
	//	item->SetObjectPoolState(ObjectPoolState::InInventory);
	//	// ownerID 설정
	//	item->SetOwnerID(player->GetID());

	//	// 해당 Client에게 알리기
	//	SendAddItemToInventoryPacket(item, packet.isTool, false, clientSocket);

	//	// 다른 Client에게도 알리기
	//	for (ClientRef client : _clients)
	//	{
	//		if (client->socket != clientSocket)
	//			SendItemPickupNotifyPacket(item, player->GetID(), packet.isTool, false, client->socket);
	//	}
	//}
}

void ServerFramework::ProcessDropItemPacket(C_DropItem_Packet packet)
{
	//// Player 인벤토리에서 아이템 제거
	//PlayerRef player = dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//// 아이템이 제대로 제거되었다면
	//if (player->RemoveItemFromInventory(packet.isTool, packet.itemID))
	//{
	//	// 떨어뜨린 아이템 ObjectPoolState 변경
	//	ItemRef item = std::dynamic_pointer_cast<Item>(_room->GetGameObject(ObjectType::Item, packet.itemID));
	//	item->SetObjectPoolState(ObjectPoolState::InWorld);
	//	// ownerID 초기화
	//	item->SetOwnerID(-1);

	//	SendDropItemPacket(item, player, packet.isTool, true);
	//}
}

void ServerFramework::ProcessChangeToolPacket(C_ChangeTool_Packet packet)
{
	//PlayerRef player = dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));

	//// toolID가 0이면 도구를 들지 않는 것
	//if(packet.toolID == 0)
	//{
	//	player->SetCurrentTool(0);
	//	SendUpdateCurrentToolPacket(packet.playerID, packet.toolID, ItemType::None, true);
	//	return;
	//}

	//// Player 인벤토리에 해당 도구가 존재하는지 확인
	//if (player->ExistItem(true, packet.toolID))
	//{
	//	// 도구가 존재하면 해당 도구를 들도록 설정
	//	player->SetCurrentTool(packet.toolID);
	//	ItemRef item = std::dynamic_pointer_cast<Item>(_room->GetGameObject(ObjectType::Item, packet.toolID));
	//	SendUpdateCurrentToolPacket(packet.playerID, packet.toolID, item->GetItemType(), true);
	//}
}

void ServerFramework::ProcessUseToolPacket(C_UseTool_Packet packet)
{
	//// 요청된 도구가 Player가 들고 있는 도구가 맞는지 확인
	//PlayerRef player = dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//if (player->GetCurrentTool() == packet.toolID)
	//{
	//	// 도구 사용 처리
	//	player->SetRotation(packet.playerRotation);
	//	player->Attack(_room);

	//	// 도구 사용 알리기
	//	ToolRef tool = std::dynamic_pointer_cast<Tool>(_room->GetGameObject(ObjectType::Item, packet.toolID));
	//	SendUseToolPacket(packet.playerID, tool->GetItemType(), true);
	//}
}

void ServerFramework::ProcessUseKeyPacket(SOCKET clientSocket, C_UseKey_Packet packet)
{
	//// Player가 열쇠를 정말 가지고 있는지 확인
	//PlayerRef player = dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//// 가지고 있지 않으면 무시
	//if (!player->ExistItem(true, packet.toolID))
	//	return;

	//// 요청한 Door가 닫힌 상태인지 확인
	//DoorRef door = dynamic_pointer_cast<Door>(_room->GetGameObject(ObjectType::Door, packet.doorID));
	//// 이미 열린 상태면 무시
	//if (door->GetState() == ObjectState::OPEN)
	//	return;

	//// 요청한 Player가 열쇠를 사용할 수 있는 거리인지 확인
	//

	//// 사용 가능한 거리라면 Door State 변경
	//door->SetState(ObjectState::OPEN);

	//// Player 인벤토리에서 열쇠 제거
	//ItemRef item = dynamic_pointer_cast<Item>(_room->GetGameObject(ObjectType::Item, packet.toolID));
	//player->RemoveItemFromInventory(true, packet.toolID);

	//SendRemoveItemFromInventoryPacket(item, true, false, clientSocket);
	//SendUpdateObjectStatePacket(door, true);
}

void ServerFramework::ProcessInteractDoorPacket(C_InteractDoor_Packet packet)
{
	//// 요청한 Player와 Door가 상호작용 가능 거리인지 확인
	//PlayerRef player = dynamic_pointer_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//DoorRef door = dynamic_pointer_cast<Door>(_room->GetGameObject(ObjectType::Door, packet.doorID));

	//// 거리 확인 코드 추가하기

	//// 상호작용 가능하면 Door State 변경
	//if (door->GetState() == ObjectState::OPEN)
	//	door->SetState(ObjectState::CLOSE);
	//else
	//	door->SetState(ObjectState::OPEN);

	//SendInteractDoorNotifyPacket(packet.playerID, packet.doorID, door->GetState(), true);
}

void ServerFramework::ProcessEmotionPacket(C_Emotion_Packet packet)
{

}

void ServerFramework::ProcessUseLanternPacket(C_UseLantern_Packet packet)
{
	//// Player가 랜턴을 정말 가지고 있는지 확인
	//Player* player = dynamic_cast<Player>(_room->GetGameObject(ObjectType::Player, packet.playerID));
	//// 가지고 있지 않으면 무시
	//if (!player->ExistItem(true, packet.lanternID))
	//	return;

	//// 랜턴 배터리 확인
	//LanternRef lantern = dynamic_pointer_cast<Lantern>(_room->GetDoor(ObjectType::Item, packet.lanternID));
	//// 배터리가 없으면 무시
	//if (lantern->GetCurrentBattery() == 0)
	//	return;

	//// 랜턴 작동
	//if (lantern->IsOn())
	//{
	//	lantern->TurnOff();
	//	_room->RemoveProcessingItem(lantern->GetID());
	//}	
	//else
	//{
	//	lantern->TurnOn();
	//	_room->AddProcessingItem(lantern);
	//}
}

void ServerFramework::ProcessStartStagePacket(C_StartStage_Packet packet)
{
	//SendStartStagePacket(true);

	_room->StartStage();
}

void ServerFramework::ProcessEndStagePacket(C_EndStage_Packet packet)
{
	//SendEndStagePacket(true);

	//// Player들 처음 위치로 이동
	//std::array<PlayerRef, MAX_ROOM_PLAYER> players = _room->GetPlayers();
	//for (auto& player : players)
	//{
	//	player->SetPos({0, 0, 25});
	//	SendMovePacket(player, true);
	//}

	//_room->EndStage();
}