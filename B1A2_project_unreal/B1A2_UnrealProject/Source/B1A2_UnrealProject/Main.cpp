#include "Main.h"
#include <winsock2.h>
#include <ws2tcpip.h>

SOCKET _clientSocket;

#define BUFSIZE	64

void UMain::Init()
{
	Super::Init();

	WSADATA wsa;

	// 扩加 檬扁拳
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (nRet != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("WSAStartup Failed..."));
		return;
	}

	// 家南 积己
	_clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// socket -> WSASocket
	if (_clientSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Socket..."));
		return;
	}

	SOCKADDR_IN stServerAddr;
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(9000);
	stServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// connect
	nRet = connect(_clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket Error..."));
		return;
	}

	Async(EAsyncExecution::Thread, [this]()
		{
			while (true)
			{
				UWorld* world = GetWorld();
				if (!world) continue;

				APlayerController* player = world->GetFirstPlayerController();
				if (!player) continue;

				APawn* pawn = player->GetPawn();
				if (!pawn) continue;

				FVector pos = pawn->GetActorLocation();

				char buf[BUFSIZE];
				sprintf_s(buf, sizeof(buf), "%.2f %.2f %.2f", pos.X, pos.Y, pos.Z);

				// 单捞磐 傈价
				int retval = send(_clientSocket, buf, (int)strlen(buf), 0);
				if (retval == SOCKET_ERROR)
				{
					UE_LOG(LogTemp, Error, TEXT("send() failed"));
					break;
				}

				UE_LOG(LogTemp, Display, TEXT("[Send] Player Pos: %f, %f, %f"), pos.X, pos.Y, pos.Z);

				FPlatformProcess::Sleep(0.5f);
			}
		});
}

void UMain::Shutdown()
{
	closesocket(_clientSocket);
	UE_LOG(LogTemp, Log, TEXT("Connection Closed..."));

	WSACleanup();

	Super::Shutdown();
}