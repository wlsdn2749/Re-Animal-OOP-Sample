#pragma once
#include "Executor.h"
#include "DBManager.h"
#include <atomic>

class User
{

public:
    inline static std::atomic<uint32_t> s_globalUserId{ 0 };

    User()
    {
        // 변경: atomic 안전하게 증가시키고 load로 Size()와 계산
        uint32_t id = s_globalUserId.fetch_add(1, std::memory_order_relaxed);
        _id = id;
        _threadKey = static_cast<uint32_t>(id % static_cast<uint32_t>(Executor::GetExecutor().Size()));
    }

public:
	uint32_t GetThreadKey()
	{
		return _threadKey;
	}

	uint32_t GetId()
	{
		return _id;
	}

public:
	void Post()
	{

	}

	template<typename T, typename... Args>
	void PostDBTask(Args&&... args)
	{
		// DB I/O 스레드 쪽으로 토스 실행하도록
		DBManager::Instance().Post<T>(std::forward<Args>(args));
	}

public:
	bool AddExp(size_t amount)		{ _exp += static_cast<uint32_t>(amount); return true; }
	bool AddLevel(size_t amount)	{ _level += static_cast<uint32_t>(amount); return true; }
	bool AddMoney(size_t amount)	{ _money += static_cast<uint32_t>(amount); return true; }

	uint32_t GetExp()				{ return _exp; }
	uint32_t GetLevel()				{ return _level; }
	uint32_t GetMoney()				{ return _money; }
									  


private:
	uint32_t _exp{};
	uint32_t _level{};
	uint32_t _money{};

private:
	uint32_t _threadKey{};
	uint32_t _id;
};

