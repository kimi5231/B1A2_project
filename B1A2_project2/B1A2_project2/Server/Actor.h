#pragma once

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	void SetActorInfo(int64 id, Vec2 pos);
	void SetActorInfo(Protocol::ActorInfo info) { _info = info; }
	Protocol::ActorInfo GetActorInfo() { return _info; }

	int32 GetId() { return _info.id(); }

private:
	Protocol::ActorInfo _info;
};