// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OtherPlayer.h"
#include "Animation/AnimMontage.h"
#include "Blueprint/UserWidget.h"

#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMain;
class ABaseItem;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API AMyPlayer : public AOtherPlayer
{
	GENERATED_BODY()
	
protected:
	/** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

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

	// Use Tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* UseToolAction;

	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

public:
	AMyPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY()
	TSet<ABaseItem*> _nearInteractableItem;

	UPROPERTY()
	ABaseItem* _focusedItem;	// E 버튼을 띄울 아이템


	// 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _inventoryWidgetClass;

	UPROPERTY()
	UUserWidget* _inventoryWidgetInstance;

	void ToggleInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> _toolBarWidgetClass;

	UPROPERTY()
	UUserWidget* _toolBarWidgetInstance;


private:
	// 아이템 상호작용
	UFUNCTION()
	void OnItemOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnItemOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnItemDestroyed(AActor* destroyedItem);
	void CheckItemTrace();
	void SetFocusedItem(ABaseItem* newItem);
	void ClearFocusedItem();
	bool LineTrace(FHitResult& outHit) const;
	void Interact();
	void UseTool();

	// 위치 정보 Send 타이머
	float _movePacketSendTimer = 0.2f;	// 현재 남은 시간
	const float MOVE_PACKET_SEND_DELAY = 0.2f;	// 전송 간격

	// 상호작용 객체 확인 타이머
	float _interactionTimer = 0.1f;		// 현재 남은 시간
	const float INTERACTION_DELAY = 0.1f;	// 확인 간격

};
