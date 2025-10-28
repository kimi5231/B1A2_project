// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SocketGameInstance.generated.h"


UCLASS()
class B1A2_PROJECT_UNREAL_API USocketGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	/*UFUNCTION(BlueprintCallable)
	bool ConnectToServer(const FString& serverIp, int32 port);
	*/
	//UFUNCTION(BlueprintCallable);
	//void SendMsgToServer(const FString& message);

	//UFUNCTION(BlueprintCallable);
	//void RecvMsg();

	//UFUNCTION(BlueprintCallable);
	//void Disconnect();
//
//private:
//	SOCKET _clientSocket;
};
