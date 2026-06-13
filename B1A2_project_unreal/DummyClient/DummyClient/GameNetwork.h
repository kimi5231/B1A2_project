#pragma once
class GameNetwork
{
public:
	GameNetwork();
	~GameNetwork();

public:
	void Update();
	
private:
	void ProcessRecv();

public:
	template <class T >
	std::vector<char> SerializePOD(const T& pod);

	template <class T >
	std::vector<char> SerializeVector(const std::vector<T>& vector);

	template <class T>
	std::vector<T> DeserializeVector(std::vector<char>& data);

public:
	void SendLoginPacket(const std::vector<char>& id);
	void SendCreateRoomPacket();
	void SendEnterRoomPacket(char roomID);
	void SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state);
	void SendStartStagePacket();
	void SendEndStagePacket();

public:
	std::vector<NetworkEventRef>& GetRecvEvents() { return _recvEvents; }

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _clientSocket{};

	std::vector<NetworkEventRef> _recvEvents;
	std::vector<NetworkEventRef> _sendEvents;

	std::mutex _recvMutex;
	std::mutex _sendMutex;
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