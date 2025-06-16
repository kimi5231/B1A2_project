#include "pch.h"
#include "Actor.h"

Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::SetActorInfo(int64 id, float x, float y)
{
	Protocol::ActorInfo info;

	info.set_id(id);
	info.set_posx(x);
	info.set_posy(y);

	_info = info;
}