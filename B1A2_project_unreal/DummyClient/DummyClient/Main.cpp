#include "pch.h"
#include "GameNetwork.h"

int main()
{
	GameNetwork network;

	while (true)
	{
		network.Update();
		network.UpdateDummy();
	}
}