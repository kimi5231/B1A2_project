#include "pch.h"
#include "Global.h"
#include "ServerFramework.h"

int main(void)
{
	g_dataManager = new DataManager();
	ServerFramework* framework = new ServerFramework();
	g_network = new ServerNetwork(framework);
	g_timer = new Timer();

	while (true)
	{
		framework->Update();
		g_network->Update();
	}

	return 0;
}