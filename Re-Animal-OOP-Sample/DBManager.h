#pragma once
#include "Executor.h"
#include "Singleton.h"
#include <utility>
#include <exception>
#include <concepts>   // 추가: std::derived_from
#include "BaseTask.h"

class DBManager : public Singleton<DBManager>
{

public:
    template<typename T, typename... Args> requires std::derived_from<T, BaseTask> // T는 TaskType 
    void Post(Args&&... args)
    {
        auto task = std::make_shared<T>(std::forward<Args>(args)...);
        auto threadId = task->GetUserKey();

        Executor::GetIoExecutor().Post(threadId, [task]() // 복사 캡처
            {
                try
                {
                    auto result = task->Execute();
                    std::cout << "DB 실행 결과 " << (result ? "True" : "False") << std::endl;

                    auto userThreadId = task->GetUserKey();

                    Executor::GetExecutor().Post(userThreadId, [task]() // 복사 캡처
                        {
                            task->Apply();
                        });
                }
                catch (const std::exception& e)
                {
                    std::cerr << "DBManager Exception: " << e.what() << "\n";
                }
            });
    }

    template<typename T, typename... Args>// requires std::derived_from<T, BaseTask> // T는 TaskType 
    void PostDelay(int64_t t, Args&&... args)
    {
        auto task = new T(std::forward<Args>(args)...);
        auto threadId = task->GetUserKey();

        Executor::GetIoExecutor().PostDelay(threadId, t, [task]() // 복사 캡처
            {
                try
                {
                    auto result = task->Execute();
                    std::cout << "DB 실행 결과 " << (result ? "True" : "False") << std::endl;

                    auto userThreadId = task->GetUserKey();

                    Executor::GetExecutor().Post(userThreadId, [task]() // 복사 캡처
                        {
                            task->Apply();
                        });
                }
                catch (const std::exception& e)
                {
                    std::cerr << "DBManager Exception: " << e.what() << "\n";
                }
            });
    }
};

