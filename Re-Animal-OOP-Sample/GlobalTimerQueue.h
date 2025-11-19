#pragma once
#include <queue>
#include <vector>
#include <mutex>
#include <thread>            // 추가: std::thread
#include "Singleton.h"
#include "TimeUtil.h"
#include "Worker.h"
#include <functional>

//using FuncPair = std::pair<Func, int64_t>; // Task, Time  Pair

struct FuncPair
{
	FuncPair(std::function<void()> func, int64_t t)
		: _func(std::move(func))
		, _t(t)
	{
		
	}
public:
	const int64_t GetTime() const
	{
		return _t;
	}

	std::function<void()> GetFunc()
	{
		return std::move(_func);
	}
private:
	std::function<void()> _func;
	int64_t _t;
};

struct compare
{
	bool operator()(const FuncPair* tp1, const FuncPair* tp2)
	{
		return tp1->GetTime() > tp2->GetTime();
	}
};



class GlobalTimerQueue : public Singleton<GlobalTimerQueue>
{
public:
	void Initialize();

public:
	template<typename Func>
	void Push(Func&& func, int64_t timeMs)
	{
		std::lock_guard<std::mutex> lock(_lock);
		_pq.push(new FuncPair {std::move(func), TimeUtil::GetCurrentTime_t() + timeMs });
	}

	decltype(auto) Pop()
	{
		std::lock_guard<std::mutex> lock(_lock);
		auto funcPair = _pq.top();
		if (IsPopable(funcPair))
		{
			_pq.pop();
			return std::move(funcPair->GetFunc());
		}
	}

	std::vector<std::function<void()>> PopAll()
	{
		std::vector<std::function<void()>> func_vec;
		std::lock_guard<std::mutex> lock(_lock);
		while (!_pq.empty())
		{
			auto funcPair = _pq.top();
			if (IsPopable(funcPair))
			{
				_pq.pop();
				func_vec.emplace_back(std::move(funcPair->GetFunc()));
			}
			else
			{
				break;
			}
		}
		return func_vec; // <-- 누락되어 있던 반환 추가
	}

	size_t Size()
	{
		return _pq.size();
	}

	bool Empty()
	{
		return _pq.empty();
	}

	FuncPair* Top()
	{
		return _pq.top();
	}

private:
	bool IsPopable(FuncPair* taskPair)
	{
		return (taskPair->GetTime() < TimeUtil::GetCurrentTime_t());
	}

private:
	std::thread _jobTimerThread;
	std::priority_queue<FuncPair*, std::vector<FuncPair*>, compare>	_pq;
	std::mutex														_lock;

};

