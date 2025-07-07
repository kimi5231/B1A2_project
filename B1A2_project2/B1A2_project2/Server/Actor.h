#pragma once

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	void SetActorInfo(int64 id, float x, float y);
	Protocol::ActorInfo GetActorInfo() { return _info; }

	int64 GetId() { return _info.id(); }

private:
	Protocol::ActorInfo _info;
};