#include "pch.h"
#include "GameNetwork.h"

int main()
{
	GameNetwork network;

	auto lastTick = std::chrono::steady_clock::now();

	while (true)
	{
		network.Update();

		auto now = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();

		if (duration >= 200)
		{
			lastTick = now;

			network.UpdateDummy();
		}
	}

	return 0;
}