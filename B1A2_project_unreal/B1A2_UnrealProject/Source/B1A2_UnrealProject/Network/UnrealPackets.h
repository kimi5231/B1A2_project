#pragma once

// 언리얼 전용
UENUM(BlueprintType)
enum class EMoveState : uint8
{
	MOVE_STATE_IDLE UMETA(DisplayName = "Idle"),
	MOVE_STATE_RUN  UMETA(DisplayName = "Run"),
	MOVE_STATE_JUMP UMETA(DisplayName = "Jump")
};