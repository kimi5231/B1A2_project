#pragma once
class DBManager
{
public:
	DBManager();
	~DBManager();

public:
	void Update();

private:
	std::deque<int> _workList;
};