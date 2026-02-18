// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OtherPlayer.h"
#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMain;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMyPlayer : public AOtherPlayer
{
	GENERATED_BODY()
	
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|IMC", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MouseLookAction;

	// Get Item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* GetItemAction;

public:
	AMyPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void CheckForInteractables();	// 상호작용 객체가 있는지 확인(아이템, 문 등)
	void GetItemByEKey();	//	E 키를 누르면 아이템 획득
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY()
	AActor* CurrentInteractableItem;

private:
	// 위치 정보 Send 타이머
	float _movePacketSendTimer = 0.2f;	// 현재 남은 시간
	const float MOVE_PACKET_SEND_DELAY = 0.2f;	// 전송 간격

	// 상호작용 객체 확인 타이머
	float _interactionTimer = 0.1f;		// 현재 남은 시간
	const float INTERACTION_DELAY = 0.1f;	// 확인 간격
};
