#pragma once
#include <thread>
#include "BaseTask.h"
#include <queue>
#include <mutex>
#include <utility>

class Worker : public std::enable_shared_from_this<Worker>
{
public:
	Worker()
	{
		Start();
	}

	virtual ~Worker()
	{
		
	}

public:
	void Start();
	void Execute();
	void PushTask(BaseTask* task);
	BaseTask* PopTask();

private:
	std::thread				_thread;
	std::queue<BaseTask*>	_taskQueue;
	std::mutex				_lock;
};

