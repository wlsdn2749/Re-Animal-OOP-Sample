#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <utility>
#include <functional>
#include <exception>
#include <iostream>

class Worker : public std::enable_shared_from_this<Worker>{
public:
    template<typename F>
    void PushTask(F&& f)
    {
        std::lock_guard<std::mutex> lock(_lock);
        _taskQueue.emplace(std::forward<F>(f)); // _queue: std::queue<std::function<void()>>
    }

    void Run()
    {
        _thread = std::thread([this]() // shared_from_this는 실제 객체가 sharedptr일때 사용가능
            {
                try
                {
                    while (true)
                    {
                        this->ExecuteTask();
                    }
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Worker exception: " << e.what() << "\n";
                }
            });
    }
    void ExecuteTask()
    {       
  
        if (_taskQueue.empty()) return;

        std::function<void()> job;
        job = std::move(_taskQueue.front()); job();
        _taskQueue.pop();
        
    }

private:
    std::queue<std::function<void()>> _taskQueue;
    std::mutex _lock;
    std::thread _thread;
};