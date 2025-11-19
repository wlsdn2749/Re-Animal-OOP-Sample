#include "GlobalTimerQueue.h"
#include "Executor.h"

void GlobalTimerQueue::Initialize()
{
	_jobTimerThread = std::thread([]()
		{
			while (true)
			{
				auto task_vec = GlobalTimerQueue::Instance().PopAll();
				for (const auto& task : task_vec)
				{
					if (task)
						Executor::GetExecutor().Post(task);
				}
			}
		});
}