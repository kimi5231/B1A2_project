#pragma once
#include <mutex>
#include <atomic>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

// 표준 사용 안 하고 직접 구현 할 수도 있기 때문에 이렇게 사용함. 직접 구현할 시에는 std::~ 부분을 지우면 됨.
// 일단 주석 처리
//template<typename T>
//using Atomic = std::atomic<T>;
//using Mutex = std::mutex;
//using CondVar = std::condition_variable;
//using UniqueLock = std::unique_lock<std::mutex>;
//using LockGuard = std::lock_guard<std::mutex>;