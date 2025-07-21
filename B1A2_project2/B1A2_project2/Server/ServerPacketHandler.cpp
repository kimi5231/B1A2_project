#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Player.h"
#include "GameSession.h"
#include "GameRoom.h"

void ServerPacketHandler::HandlePacket(GameSessionRef session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case C_Move:
		Handle_C_Move(session, buffer, len);
		break;
	default:
		break;
	}
}

void ServerPacketHandler::Handle_C_Move(GameSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::C_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	GameRoomRef room = session->gameRoom.lock();
	if (room)
		room->Handle_C_Move(pkt);
}

SendBufferRef ServerPacketHandler::Make_S_EnterGame()
{
	Protocol::S_EnterGame pkt;

	pkt.set_success(true);
	pkt.set_accountid(0);

	return MakeSendBuffer(pkt, S_EnterGame);
}

SendBufferRef ServerPacketHandler::Make_S_AddObject(const Protocol::S_AddObject& pkt)
{
	return MakeSendBuffer(pkt, S_AddObject);
}

SendBufferRef ServerPacketHandler::Make_S_RemoveObject(const Protocol::S_RemoveObject& pkt)
{
	return MakeSendBuffer(pkt, S_RemoveObject);
}

SendBufferRef ServerPacketHandler::Make_S_MyPlayer(const PlayerRef& player)
{
	Protocol::S_MyPlayer pkt;

	Protocol::ActorInfo* actorInfo = pkt.mutable_actor();
	Protocol::ObjectInfo* objectInfo = pkt.mutable_object();

	*actorInfo = player->GetActorInfo();
	*objectInfo = player->GetObjectInfo();

	return MakeSendBuffer(pkt, S_MyPlayer);
}

SendBufferRef ServerPacketHandler::Make_S_Move(const Protocol::ActorInfo& actor, const Protocol::ObjectInfo& object)
{
	Protocol::S_Move pkt;

	Protocol::ActorInfo* actorInfo = pkt.mutable_actor();
	Protocol::ObjectInfo* objectInfo = pkt.mutable_object();
	
	*actorInfo = actor;
	*objectInfo = object;

	return MakeSendBuffer(pkt, S_Move);
}