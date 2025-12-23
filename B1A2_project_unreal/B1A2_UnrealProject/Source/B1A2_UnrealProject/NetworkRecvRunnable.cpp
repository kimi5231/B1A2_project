// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkRecvRunnable.h"

NetworkRunnable::NetworkRunnable(SOCKET InSocket, TQueue<RecvData>& InOutputQueue, TQueue<SendData>& InInputQueue)
    : _clientSocket(InSocket)
    , _outputQueue(InOutputQueue)
    , _inputQueue(InInputQueue)
    , bShouldStop(false)
{
}

NetworkRunnable::~NetworkRunnable()
{
	
}

bool NetworkRunnable::Init()
{
	return true;
}

uint32 NetworkRunnable::Run()
{
    while (!bShouldStop)
    {
        ProcessSendLoop();

       TArray<uint8> PacketBuffer;
        if (ProcessRecvPacketBlocking(PacketBuffer))
        {
            // Recv 성공 -> 메인 스레드 큐에 데이터 추가
            _outputQueue.Enqueue({ PacketBuffer });
        }
    }
    return 0;
}

void NetworkRunnable::Exit()
{
}

void NetworkRunnable::StopThread()
{
    bShouldStop = true;
}

void NetworkRunnable::ProcessSendLoop()
{
    SendData Request;

    // 큐의 Send 요청 처리
    while (_inputQueue.Dequeue(Request))
    {
        const TArray<uint8>& SendBuffer = Request.DataBuffer;

        int32 BytesSent = 0;
        int32 TotalBytes = SendBuffer.Num();

        // 전체 데이터를 보낼 때까지 반복
        while (BytesSent < TotalBytes)
        {
            int32 RetVal = send(
                _clientSocket,
                (const char*)SendBuffer.GetData() + BytesSent,
                TotalBytes - BytesSent,
                0
            );

            if (RetVal == SOCKET_ERROR)
            {
                // 오류 처리
                UE_LOG(LogTemp, Error, TEXT("NetworkThread Send Failed. Error: %d"), WSAGetLastError());
                // bShouldStop = true; // 연결 끊김 처리
                return;
            }

            BytesSent += RetVal;
        }
    }
}

void NetworkRunnable::ProcessRecvLoop()
{
}

bool NetworkRunnable::ProcessRecvPacketBlocking(TArray<uint8>& OutPacketBuffer)
{
    // 패킷 크기
    int32 PacketSize;
    int32 RecvBytes = recv(_clientSocket, (char*)&PacketSize, sizeof(int32), MSG_WAITALL);

    // 스레드 중지 요청이 있었다면 종료
    if (bShouldStop) 
        return false; 

    if (RecvBytes <= 0) // 연결 끊김 또는 오류
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkThread Recv Size Failed. Connection closed or error: %d"), WSAGetLastError());
        bShouldStop = true;
        return false;
    }

    // 데이터
    if (PacketSize <= 0) return false;

    OutPacketBuffer.SetNumUninitialized(PacketSize);
    RecvBytes = recv(_clientSocket, (char*)OutPacketBuffer.GetData(), PacketSize, MSG_WAITALL);

    if (bShouldStop) return false;

    if (RecvBytes == PacketSize)
    {
        return true;
    }
    else
    {
        // 데이터 불일치 또는 부분 수신 오류
        UE_LOG(LogTemp, Error, TEXT("NetworkThread Recv Data Mismatch. Expected: %d, Received: %d"), PacketSize, RecvBytes);
        return false;
    }
}
