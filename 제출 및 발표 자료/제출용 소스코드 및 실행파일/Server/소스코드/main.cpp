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

void WorkerThread()
{
	while (true)
	{
		g_network->Update();
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
	std::thread workerThread(WorkerThread);

	while (true)
	{
		framework->Update();
		g_timer->Update();
	}

	return 0;
}