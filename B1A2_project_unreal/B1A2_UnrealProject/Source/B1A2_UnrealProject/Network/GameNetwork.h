#pragma once
#include "Includes.h"

class GameNetwork
{
public:
	GameNetwork();
	~GameNetwork();

public:
	void Update();
	
private:
	void ProcessRecv();
	void ProcessUDPRecv();

public:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);

	template <class T>
	std::vector<T> DeserializeVector(std::vector<char>& data);

public:
	void SendLoginPacket(const std::vector<char>& id);
	void SendLogoutPacket();
	void SendCreateRoomPacket();
	void SendEnterRoomPacket(char roomID);
	void SendExitRoomPacket();
	void SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state);
	void SendUpdateObjectStatePacket(int id, ObjectType type, ObjectState state);
	void SendGetItemPacket(int itemID, bool isTool, int playerID);
	void SendDropItemPacket(int itemID, bool isTool, int playerID);
	void SendDropItemToSellingMachinePacket(int itemID, int playerID, int sellingMachineID);
	void SendChangeToolPacket(int playerID, int toolID);
	void SendUseToolPacket(int playerID, int toolID, Rotation playerRotation);
	void SendUseKeyPacket(int playerID, int toolID, int doorID);
	void SendUseLanternPacket(int playerID, int lanternID);
	void SendInteractDoorPacket(int playerID, int doorID);
	void SendSellItemPacket(int playerID, int sellingMachineID);
	void SendBuyItemPacket(int playerID, ItemType itemType, int itemCount);
	void SendChangeEmotionPacket(int playerID, Emotion emotion);
	void SendEmotionResultPacket(float angryTime, float disgustTime, float fearTime, float happyTime, float sadTime, float surpriseTime, float neutralTime);
	void SendStartStagePacket();
	void SendEndStagePacket();
	void SendSubmitItemPacket(int itemID, int playerID);
	void SendRequestQuestRewardPacket(bool isMain);
	void SendVoiceDataPacket(short clientID, char playerID, int sequenceNumber, std::vector<char>& audioData);

public:
	std::vector<NetworkEventRef>& GetRecvEvents() { return _recvEvents; }

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _clientSocket{};
	SOCKET _udpSocket{};

	sockaddr_in _serverAddr;

	std::vector<NetworkEventRef> _recvEvents;
	std::vector<NetworkEventRef> _sendEvents;
	std::vector<NetworkEventRef> _unpSendEvents;

	std::mutex _recvMutex;
	std::mutex _sendMutex;
	std::mutex _udpSendMutex;
};

template<class T>
inline std::vector<char> GameNetwork::SerializePOD(const T& pod)
{
	std::vector<char> serializedData(sizeof(pod));
	memcpy(serializedData.data(), &pod, sizeof(pod));

	return serializedData;
}

template<class T>
inline std::vector<char> GameNetwork::SerializeVector(const std::vector<T>& vector)
{
	int size = vector.size();

	std::vector<char> serializedData(sizeof(int) + vector.size() * sizeof(T));
	memcpy(serializedData.data(), &size, sizeof(int));
	memcpy(serializedData.data() + sizeof(int), vector.data(), size * sizeof(T));

	return serializedData;
}

template<class T>
inline std::vector<T> GameNetwork::DeserializeVector(std::vector<char>& data)
{
	int size;
	memcpy(&size, data.data(), sizeof(int));
	data.erase(data.begin(), data.begin() + sizeof(int));

	std::vector<T> vector(size);
	memcpy(vector.data(), data.data(), size * sizeof(T));
	data.erase(data.begin(), data.begin() + size * sizeof(T));

	return vector;
}