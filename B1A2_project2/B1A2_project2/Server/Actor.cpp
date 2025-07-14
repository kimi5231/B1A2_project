#include "pch.h"
#include "Actor.h"

Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::SetActorInfo(int64 id, Vec2 pos)
{
	Protocol::ActorInfo info;

	info.set_id(id);
	info.set_posx(pos.x);
	info.set_posy(pos.y);

	_info = info;
}