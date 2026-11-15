#pragma once
#include <sqlext.h> 

class DBManager
{
public:
	DBManager();
	~DBManager();

public:
	void Update();
	void AddWork(DBWork work);

public:
	void ProcessExistID(DBWork work);

private:
	SQLHENV _henv;
	SQLHDBC _hdbc;
	SQLHSTMT _hstmt;

	std::mutex _mutex;
	std::deque<DBWork> _workList;
};