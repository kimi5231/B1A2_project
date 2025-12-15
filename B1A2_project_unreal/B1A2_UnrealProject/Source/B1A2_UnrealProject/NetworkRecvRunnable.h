// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <winsock2.h>
#include "Main.h"

/**
 * 
 */
class B1A2_UNREALPROJECT_API NetworkRunnable : public FRunnable
{
public:
    NetworkRunnable(SOCKET InSocket, TQueue<RecvData>& InOutputQueue, TQueue<SendData>& InInputQueue);
    virtual ~NetworkRunnable();

    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Exit() override;

    void StopThread();

private:
    void ProcessSendLoop();
    void ProcessRecvLoop();

    bool ProcessRecvPacketBlocking(TArray<uint8>& OutPacketBuffer);

private:
    SOCKET _clientSocket;

    // Recv -> 메인 스레드
    TQueue<RecvData>& _outputQueue;
    // 메인 -> Send 스레드 
    TQueue<SendData>& _inputQueue;

    // 스레드 종료 플래그
    FThreadSafeBool bShouldStop;

    // 송수신 처리 버퍼
    TArray<uint8> RecvBuffer;
    int32 BytesToRecv = 0;
    int32 CurrentRecvOffset = 0;
};
