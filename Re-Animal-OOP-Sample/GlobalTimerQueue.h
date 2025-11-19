#pragma once
#include "UserDBTask.h"
#include <queue>
#include <vector>
#include <mutex>
#include <thread>            // 추가: std::thread
#include "Singleton.h"
#include "TimeUtil.h"
#include "Worker.h"

class UserDBTask;

using TaskPair = std::pair<UserDBTask*, int64_t>; // Task, Time  Pair

struct compare
{
	bool operator()(const TaskPair* tp1, const TaskPair* tp2)
	{
		return (*tp1).second > (*tp2).second;
	}
};



class GlobalTimerQueue : public Singleton<GlobalTimerQueue>
{
public:
	void Initialize()
	{
		_jobTimerThread = std::thread([]()
			{
				while (true)
				{
					auto task_vec = GlobalTimerQueue::Instance().PopAll();
					for (const auto& task : task_vec)
					{
						/*if (task)
							GetExecutor().Post(task->GetUserey(), task);*/
					}
				}
			});
	}

public:
	void Push(UserDBTask* task, int64_t timeMs)
	{
		std::lock_guard<std::mutex> lock(_lock);
		_pq.push(new TaskPair{ task, TimeUtil::GetCurrentTime_t() + timeMs });
	}

	UserDBTask* Pop()
	{
		std::lock_guard<std::mutex> lock(_lock);
		auto taskPair = _pq.top();
		if (IsPopable(taskPair))
		{
			_pq.pop();
			return taskPair->first;
		}

		return nullptr;
	}

	std::vector<UserDBTask*> PopAll()
	{
		std::vector<UserDBTask*> task_vec;
		std::lock_guard<std::mutex> lock(_lock);
		while (!_pq.empty())
		{
			auto taskPair = _pq.top();
			if (IsPopable(taskPair))
			{
				_pq.pop();
				task_vec.emplace_back(taskPair->first);
			}
			else
			{
				break;
			}
		}
		return task_vec; // <-- 누락되어 있던 반환 추가
	}

	size_t Size()
	{
		return _pq.size();
	}

	bool Empty()
	{
		return _pq.empty();
	}

	TaskPair* Top()
	{
		return _pq.top();
	}

private:
	bool IsPopable(TaskPair* taskPair)
	{
		return (taskPair->first && taskPair->second < TimeUtil::GetCurrentTime_t());
	}

private:
	std::thread _jobTimerThread;
	std::priority_queue<TaskPair*, std::vector<TaskPair*>, compare>	_pq;
	std::mutex														_lock;

};

