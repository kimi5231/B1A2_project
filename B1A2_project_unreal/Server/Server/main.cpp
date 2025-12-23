#include "pch.h"
#include "ServerFramework.h"
#include "Global.h"

int main(void)
{
	while (true)
	{
		g_framework->Update();
	}

	return 0;
}