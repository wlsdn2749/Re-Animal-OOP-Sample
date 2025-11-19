#pragma once
#include "Executor.h"
#include "Singleton.h"
#include <utility>
#include <exception>
#include <concepts>   // 추가: std::derived_from

class DBManager : public Singleton<DBManager>
{

public:
    template<typename T, typename... Args> requires std::derived_from<T, BaseTask> // T는 TaskType 
    void Post(Args&&... args)
    {
        // 여기서 Task 생성
        auto* task = new T(std::forward<Args>(args));
        auto threadId = task->GetThreadId(); // 변경: auto* -> auto

        // DB I/O 스레드에서 작업 실행
        Executor::GetIoExecutor().Post(threadId, [&task]()
            {   
                try
                {
                    task->Execute(); // DB 작업 실행 ... 이미 실행결과가 저장되어있음

                    // 결과 얻어내고 유저 스레드 쪽으로 전달
                    auto userThreadId = task->GetUserKey();

                    Executor::GetExecutor().Post(userThreadId, [&task]()
                        {
                            task->Apply();
                        });
                }
                catch (const std::exception& e)
                {
                    ;
                }
            }
        );

    }
};

