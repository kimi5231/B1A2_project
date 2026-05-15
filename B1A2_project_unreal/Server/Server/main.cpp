#include "pch.h"
#include "Global.h"

int main(void)
{
	g_dataManager = new DataManager();
	g_framework = new ServerFramework();
	g_network = new ServerNetwork(g_framework);
	g_timer = new Timer();

	while (true)
	{
		g_framework->Update();
		g_network->Update();
	}

	return 0;
}