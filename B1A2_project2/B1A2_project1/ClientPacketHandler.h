#pragma once

enum
{
	S_TEST = 1,
	S_EnterGame = 2,

	S_AddPlayer = 3,
	S_RemoveObject = 4,

	S_MyPlayer = 5,
};

class ClientPacketHandler
{
public:
	static void HandlePacket(ServerSessionRef session, BYTE* buffer, int32 len);

	// 받기
	static void Handle_S_TEST(BYTE* buffer, int32 len);
	static void Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_AddPlayer(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len);

	// 보내기
	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		assert(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};
