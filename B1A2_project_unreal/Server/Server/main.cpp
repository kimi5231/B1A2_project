#include "pch.h"
#include "Global.h"

int main(void)
{
	g_dataManager = new DataManager();
	g_framework = new ServerFramework();
	g_timer = new Timer();

	while (true)
	{
		g_framework->Update();
		g_timer->Update();
	}

	return 0;
}