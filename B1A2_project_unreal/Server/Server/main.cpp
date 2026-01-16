#include "pch.h"
#include "ServerFramework.h"
#include "DataManager.h"
#include "Global.h"

int main(void)
{
	g_dataManager = new DataManager();
	g_framework = new ServerFramework();

	while (true)
	{
		g_framework->Update();
	}

	return 0;
}