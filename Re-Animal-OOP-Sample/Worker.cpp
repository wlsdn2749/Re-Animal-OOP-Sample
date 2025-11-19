#include "Worker.h"
#include <thread>

void Worker::Start()
{
	_thread = std::thread([self = shared_from_this()]()
		{
			while (true)
			{
				self->Execute();

				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
		});
}

void Worker::Execute()
{
	auto* task = PopTask();
	task->Execute();
}

void Worker::PushTask(BaseTask* task)
{
	std::lock_guard<std::mutex> lock(_lock);
	_taskQueue.push(task);
}

BaseTask* Worker::PopTask()
{
	auto* task = _taskQueue.front(); _taskQueue.pop();
	return task;
}
