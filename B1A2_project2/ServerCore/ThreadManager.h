#pragma once

#include <thread>
#include <functional>

/*------------------
	ThreadManager
-------------------*/

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void	Launch(std::function<void(void)> callback);
	void	Join();

private:
	static void InitTLS();
	static void DestroyTLS();

private:
	std::mutex			_lock;
	std::vector<std::thread>	_threads;
};


