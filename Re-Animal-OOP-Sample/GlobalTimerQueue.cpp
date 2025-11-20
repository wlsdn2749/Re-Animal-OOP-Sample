#include "GlobalTimerQueue.h"
#include "Executor.h"

void GlobalTimerQueue::Initialize()
{
	_jobTimerThread = std::thread([]()
		{
			while (true)
			{
				auto f_vec = GlobalTimerQueue::Instance().PopAll();
				for (const auto& f : f_vec)
				{
					if (f)
						f();
				}
			}
		});
}