#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"

std::unique_ptr<ThreadManager> GThreadManager = std::make_unique<ThreadManager>();
