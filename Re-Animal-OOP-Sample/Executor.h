#pragma once
#include <vector>
#include <cstdint>
#include <concepts>
#include <type_traits>
#include <utility>
#include "Worker.h"
#include "GlobalTimerQueue.h"

class Executor
{
public:
	inline static Executor& GetExecutor()
	{
		static Executor s_executor(2);
		return s_executor;
	}

	inline static Executor& GetIoExecutor()
	{
		static Executor s_ioExecutor(2);
		return s_ioExecutor;
	}
	
public:
	Executor(size_t count)
	{
		_workers.reserve(count);

		for (int i = 0; i < count; ++i)
		{
			auto* worker = new Worker();
			worker->Run();
			_workers.emplace_back(worker);
		}
	}

public:
	template<typename F>
	void Post(F&& f)
	{
		Post(0, std::forward<F>(f));
	}

	template<typename F> //requires std::derived_from<F, BaseTask>
	void Post(int32_t threadId, F&& f)
	{
		auto* worker = _workers[threadId];
		
		worker->PushTask(std::forward<F>(f));
	}

	template<typename F> //requires std::derived_from<std::remove_pointer_t<F>, BaseTask>
	void PostDelay(int32_t threadId, int64_t t, F&& f)
	{
		GlobalTimerQueue::Instance().Push(f, t);
	}

public:
	const size_t Size()
	{
		return _workers.size();
	}

private:
	std::vector<Worker*> _workers;
};

