#pragma once
#include <thread>
#include <functional>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	// 쓰레드 생성 및 저장
	void Launch(std::function<void(void)> callback);
	// 가지고 있는 모든 쓰레드를 join
	void Join();

private:
	// Local Space
	static void InitTLS();
	static void DestroyTLS();

private:
	Mutex _lock;
	std::vector<std::thread> _threads;
};