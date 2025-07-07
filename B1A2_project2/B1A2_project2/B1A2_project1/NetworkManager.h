#pragma once

class NetworkManager
{
	DECLARE_SINGLE(NetworkManager);

public:
	void Init();
	void Update();

	ServerSessionRef CreateSession();
	void SendPacket(SendBufferRef sendBuffer);

private:
	ClientServiceRef _service;
	ServerSessionRef _session;
};