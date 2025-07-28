#pragma once

#define USE_MANY_LOCKS(count)	Mutex _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	WRITE_LOCK_IDX(idx)		LockGuard writeLockGuard_##idx(_locks[idx]);
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))
#define len16(arr)		static_cast<int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)		static_cast<int32>(sizeof(arr)/sizeof(arr[0]))