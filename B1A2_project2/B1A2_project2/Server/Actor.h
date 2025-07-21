#pragma once

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	void SetActorInfo(int64 id, Vec2 pos);
	void SetActorInfo(Protocol::ActorInfo info) { _actorInfo = info; }
	Protocol::ActorInfo GetActorInfo() { return _actorInfo; }

	int32 GetId() { return _actorInfo.id(); }

protected:
	Protocol::ActorInfo _actorInfo;
};