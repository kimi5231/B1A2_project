#include "pch.h"
#include "ServerFramework.h"

int main(void)
{
	// ServerFramework »ı¼º
	ServerFramework* framework = new ServerFramework();

	while (true)
	{
		framework->Update();
	}

	return 0;
}