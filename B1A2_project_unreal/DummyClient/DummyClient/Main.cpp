#include "pch.h"
#include "GameNetwork.h"

struct DummyPlayer
{
	SOCKET socket;
	int id;
	Vector pos;
};

int main()
{
	GameNetwork network;

	while (true)
	{
		std::vector<char> id;
		id.push_back('T');
		id.push_back('e');
		id.push_back('s');
		id.push_back('t');
		network.SendLoginPacket(id);
		network.Update();
	}
}