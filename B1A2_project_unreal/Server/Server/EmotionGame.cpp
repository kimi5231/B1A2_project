#include "pch.h"
#include "EmotionGame.h"
#include "FSM.h"
#include "State.h"
#include "Global.h"
#include "BoundingBox.h"
#include "Room.h"
#include "Player.h"

EmotionGame::EmotionGame(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status 초기화
	_maxHP = 10000;
	_hp = _maxHP;
	_idleTime = 15.f;
	_playTime = 3.f;
	_releaseTime = 3.f;
	_damage = 25;
	_healValue = 7;
	_aggroRange = 500;

	// State Table
	_stateTable[IDLE] = TELEPORT;
	_stateTable[TELEPORT] = IDLE;
	_stateTable[GRAB] = PLAY;
	_stateTable[PLAY] = RELEASE;
	_stateTable[RELEASE] = TELEPORT;
}

EmotionGame::~EmotionGame()
{
}

void EmotionGame::Update(Room* room)
{
	Monster::Update(room);

	if(_loseCount == 3)
		SetState(DEAD);

	if (_state == IDLE)
	{
		const std::array<Player*, MAX_ROOM_PLAYER>& players = room->GetPlayers();
		for (auto& player : players)
		{
			/*if (player->GetObjectPoolState() == ObjectPoolState::Reusable)
				continue;*/

			BoundingBox aggroBox;
			aggroBox.SetBounds(_pos, _aggroRange, Front);

			// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
			if (CheckCollision(aggroBox, player->GetBoundingBox()))
			{
				_target = player;
				SetState(ObjectState::GRAB);
				return;
			}
		}
	}
}

bool EmotionGame::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _sumTime > _idleTime;
	case ObjectState::TELEPORT:
		return true;
	case ObjectState::GRAB:
		return true;
	case ObjectState::PLAY:
		return _sumTime > _playTime;
	case ObjectState::RELEASE:
		return _sumTime > _releaseTime;
	}
}

Emotion EmotionGame::SelectEmotion()
{
	std::uniform_int_distribution<int> selectEmotion(0, 2);
	Emotion emotion = static_cast<Emotion>(selectEmotion(gen));
	return emotion;
}

bool EmotionGame::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::TELEPORT:
		_fsm->ChangeState(g_teleportState, this);
		break;
	case ObjectState::GRAB:
		_fsm->ChangeState(g_grabState, this);
		break;
	case ObjectState::PLAY:
		_fsm->ChangeState(g_playState, this);
		break;
	case ObjectState::RELEASE:
		_fsm->ChangeState(g_releaseState, this);
		break;
	}

	return true;
}