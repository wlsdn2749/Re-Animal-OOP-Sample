#pragma once
#include "Executor.h"
#include "DBManager.h"
#include <cmath>
#include <atomic>

class User : public std::enable_shared_from_this<User>
{

public:
    inline static std::atomic<int32_t> s_globalUserId{ 0 };

    User()
    {
        // 변경: atomic 안전하게 증가시키고 load로 Size()와 계산
        int32_t id = s_globalUserId.fetch_add(1, std::memory_order_relaxed);
        _id = id;
        _threadKey = static_cast<int32_t>(id % static_cast<int32_t>(Executor::GetExecutor().Size()));

		Post([this]() // TODO: shared_from_this로 교체
			{
				this->Update();
			}, 1000); // 1초뒤 호출
    }

public:
	int32_t GetThreadKey()
	{
		return _threadKey;
	}

	int32_t GetId()
	{
		return _id;
	}

public:
	void Update();
	virtual void OnUpdate();

public:
	template<typename F>
	void Post(F&& f)
	{
		Executor::GetExecutor().Post(GetThreadKey(), f);
	}

	template<typename F>
	void Post(F&& f, int64_t t)
	{
		Executor::GetExecutor().PostDelay(GetThreadKey(), t, f);
	}

	template<typename F>
	void Post(int32_t id, F&& f)
	{
		Executor::GetExecutor().Post(id, f);
	}

	template<typename F>
	void Post(int32_t id, F&& f, int64_t t)
	{
		Executor::GetExecutor().PostDelay(id, t, f); // 시그니처 순서 변경 todo
	}

	template<typename T, typename... Args>
	void PostDBTask(Args&&... args)
	{
		// DB I/O 스레드 쪽으로 토스 실행하도록
		DBManager::Instance().Post<T>(shared_from_this(), std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	void PostDBTaskDelay(int64_t t, Args&&... args)
	{
		// DB I/O 스레드 쪽으로 토스 실행하도록
		DBManager::Instance().PostDelay<T>(t, shared_from_this(), std::forward<Args>(args)...);
	}

public:
	bool AddExp(size_t amount)		{ _exp += static_cast<uint32_t>(amount); return true; }
	bool AddLevel(size_t amount)	{ _level += static_cast<uint32_t>(amount); return true; }
	bool AddMoney(size_t amount)	{ _money += static_cast<uint32_t>(amount); return true; }

	uint32_t GetExp()				{ return _exp; }
	uint32_t GetLevel()				{ return _level; }
	uint32_t GetMoney()				{ return _money; }
									  
	void ChangeThreadKey()
	{
		auto before_threadKey = _threadKey;
		if(_threadKey == 1) 
			_threadKey = 0;
		else 
			_threadKey = 1;

		std::cout << "---------------------------------스레드 이동 ----------------------------------------------------" << std::endl;
		std::cout << "이전 Threadkey " << before_threadKey << " 현재 ThreadKey " << _threadKey << std::endl;
		std::cout << "---------------------------------스레드 이동 ----------------------------------------------------" << std::endl;


	}

private:
	uint32_t _exp{};
	uint32_t _level{};
	uint32_t _money{};

private:
	int32_t _threadKey{};
	int32_t _id;
};

