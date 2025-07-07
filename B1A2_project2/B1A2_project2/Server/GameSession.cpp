#include "pch.h"
#include "GameSession.h"
#include "GameRoom.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));

	Send(ServerPacketHandler::Make_S_EnterGame());

	// 게임 입장
	GRoom->EnterRoom(GetSessionRef());
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));

	// 게임 퇴장
	GRoom->LeaveRoom(GetSessionRef());
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);
	cout << "Packet ID : " << header.id << "Size : " << header.size << endl;
}

void GameSession::OnSend(int32 len)
{
	cout << "OnSend Len = " << len << endl;
}