#include "pch.h"
#include "Global.h"
#include "ServerFramework.h"

void DBWorkerThread()
{
	while (true)
	{
		g_dbManager->Update();
	}
}

int main(void)
{
	g_dataManager = new DataManager();
	g_dbManager = new DBManager();
	ServerFramework* framework = new ServerFramework();
	g_network = new ServerNetwork(framework);
	g_timer = new Timer();

	// DB Thread
	std::thread dbThread(DBWorkerThread);

	while (true)
	{
		framework->Update();
		g_network->Update();
		g_timer->Update();
	}

	return 0;
}