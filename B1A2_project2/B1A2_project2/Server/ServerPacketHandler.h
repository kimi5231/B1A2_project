#pragma once
// Protocol 종류
enum
{
	S_TEST = 1,
	S_EnterGame = 2,

	S_AddObject = 3,
	S_RemoveObject = 4,

	S_MyPlayer = 5,

	C_Move = 6,
	S_Move = 7,
};

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(GameSessionRef session, BYTE* buffer, int32 len);

	// 수신
	static void Handle_C_Move(GameSessionRef session, BYTE* buffer, int32 len);

	// 송신
	static SendBufferRef Make_S_EnterGame();
	static SendBufferRef Make_S_AddObject(const Protocol::S_AddObject& pkt);
	static SendBufferRef Make_S_RemoveObject(const Protocol::S_RemoveObject& pkt);
	static SendBufferRef Make_S_MyPlayer(const PlayerRef& player);
	static SendBufferRef Make_S_Move(const Protocol::ActorInfo& actor, const Protocol::ObjectInfo& object);

public:
	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = std::make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		assert(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};