#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Player.h"

void ServerPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	default:
		break;
	}
}

SendBufferRef ServerPacketHandler::Make_S_TEST(uint64 id, uint32 hp, uint16 attack, vector<BuffData> buffs)
{
	Protocol::S_TEST pkt;

	pkt.set_id(id);
	pkt.set_hp(hp);
	pkt.set_attack(attack);

	{
		Protocol::BuffData* data = pkt.add_buffs();
		data->set_buffid(100);
		data->set_remaintime(1.2f);
		{
			data->add_victims(10);
		}
	}
	{
		Protocol::BuffData* data = pkt.add_buffs();
		data->set_buffid(200);
		data->set_remaintime(2.2f);
		{
			data->add_victims(20);
		}
	}

	return MakeSendBuffer(pkt, S_TEST);
}

SendBufferRef ServerPacketHandler::Make_S_EnterGame()
{
	Protocol::S_EnterGame pkt;

	pkt.set_success(true);
	pkt.set_accountid(0);

	return MakeSendBuffer(pkt, S_EnterGame);
}

SendBufferRef ServerPacketHandler::Make_S_AddPlayer(const Protocol::S_AddPlayer& pkt)
{
	return MakeSendBuffer(pkt, S_AddPlayer);
}

SendBufferRef ServerPacketHandler::Make_S_MyPlayer(const PlayerRef& player)
{
	Protocol::S_MyPlayer pkt;

	Protocol::ActorInfo* actorInfo = pkt.mutable_actor();
	Protocol::ObjectInfo* objectInfo = pkt.mutable_object();
	Protocol::PlayerStat* playerStat = pkt.mutable_stat();

	*actorInfo = player->GetActorInfo();
	*objectInfo = player->GetObjectInfo();
	*playerStat = player->GetStat();

	return MakeSendBuffer(pkt, S_MyPlayer);
}