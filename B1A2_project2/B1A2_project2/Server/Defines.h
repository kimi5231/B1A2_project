#pragma once

#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance()			\
	{										\
		static classname s_instance;		\
		return &s_instance;					\
	}

#define GET_SINGLE(classname)	classname::GetInstance()

// Object State
#define IDLE				ObjectState::OBJECT_STATE_TYPE_IDLE
#define MOVE				ObjectState::OBJECT_STATE_TYPE_MOVE
#define DUCK_DOWN			ObjectState::OBJECT_STATE_TYPE_DUCK_DOWN
#define DUCK_DOWN_MOVE		ObjectState::OBJECT_STATE_TYPE_DUCK_DOWN_MOVE
#define JUMP				ObjectState::OBJECT_STATE_TYPE_JUMP
#define CLOSE_ATTACK		ObjectState::OBJECT_STATE_TYPE_CLOSE_ATTACK
#define LONG_ATTACK			ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK
#define LONG_ATTACK_LENGTH	ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK_LENGTH
#define LONG_ATTACK_WIDTH	ObjectState::OBJECT_STATE_TYPE_LONG_ATTACK_WIDTH
#define THRUST				ObjectState::OBJECT_STATE_TYPE_THRUST
#define BACK_STEP			ObjectState::OBJECT_STATE_TYPE_BACK_STEP
#define SLASH_WAVE			ObjectState::OBJECT_STATE_TYPE_SLASH_WAVE
#define SKILL_READY			ObjectState::OBJECT_STATE_TYPE_SKILL_READY
#define SKILL_WAITING		ObjectState::OBJECT_STATE_TYPE_SKILL_WAITING
#define SKILL_END			ObjectState::OBJECT_STATE_TYPE_SKILL_END
#define HANG				ObjectState::OBJECT_STATE_TYPE_HANG
#define RELEASE				ObjectState::OBJECT_STATE_TYPE_RELEASE
#define HIT					ObjectState::OBJECT_STATE_TYPE_HIT
#define DEAD				ObjectState::OBJECT_STATE_TYPE_DEAD
#define CHASE				ObjectState::OBJECT_STATE_TYPE_CHASE
#define ROAMING				ObjectState::OBJECT_STATE_TYPE_ROAMING
#define DASH				ObjectState::OBJECT_STATE_TYPE_DASH
#define RETURN				ObjectState::OBJECT_STATE_TYPE_RETURN
#define RETURN_IDLE			ObjectState::OBJECT_STATE_TYPE_RETURN_IDLE
#define PROJECTILE_FALL		ObjectState::OBJECT_STATE_TYPE_PROJECTILE_FALL
#define CRYSTAL_CREATION	ObjectState::OBJECT_STATE_TYPE_CRYSTAL_CREATION
#define MONSTER_CREATION	ObjectState::OBJECT_STATE_TYPE_MONSTER_CREATION
#define TELEPORT			ObjectState::OBJECT_STATE_TYPE_TELEPORT
#define CUT_SEVERELY		ObjectState::OBJECT_STATE_TYPE_CUT_SEVERELY
#define ON					ObjectState::OBJECT_STATE_TYPE_ON
#define ON2					ObjectState::OBJECT_STATE_TYPE_ON2
#define READY				ObjectState::OBJECT_STATE_TYPE_READY
#define OFF					ObjectState::OBJECT_STATE_TYPE_OFF

// Direction
#define DIR_LEFT	Dir::DIR_TYPE_LEFT
#define DIR_RIGHT	Dir::DIR_TYPE_RIGHT
#define DIR_UP		Dir::DIR_TYPE_UP
#define DIR_DOWN	Dir::DIR_TYPE_DOWN