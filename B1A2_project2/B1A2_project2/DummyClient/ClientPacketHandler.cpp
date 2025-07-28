#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	// 패킷 헤더 읽기
	br >> header;

	// 헤더 id에 따라 처리
	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}
}

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_TEST pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	uint64 id = pkt.id();
	uint32 hp = pkt.hp();
	uint16 attack = pkt.attack();

	std::cout << "ID: " << id << " HP : " << hp << " ATT : " << attack << std::endl;

	for (int32 i = 0; i < pkt.buffs_size(); i++)
	{
		const Protocol::BuffData& data = pkt.buffs(i);
		std::cout << "BuffInfo : " << data.buffid() << " " << data.remaintime() << std::endl;
	}
}