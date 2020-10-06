#pragma once
#include<time.h>
#include <Windows.h>
#include<list>
#include<functional>
#include <future>

using namespace std;

class ThreadPool
{
public:
    using Task = std::function<void()>;
    ThreadPool(int threadCount = 0);

    template<class Func, class... Args>
    auto addTask(Func&& func, Args&&...args) ->std::future<typename std::result_of<Func(Args...)>::type>
    {
        
        using returnType = typename std::result_of<Func(Args...)>::type;
        auto wrapper = std::make_shared< std::packaged_task<returnType()> >([func, args...]() { return func(args...); });
        if (mTasks.size() == mThreadCount) overFlow = true;
        if (!overFlow) {
            EnterCriticalSection(&mCriticalSection);
            mTasks.push_back([=] {(*wrapper)(); });
            mNumberOfTasksNotFinished++;
            LeaveCriticalSection(&mCriticalSection);
            WakeConditionVariable(&mConditionVariable);
            return wrapper->get_future();
        }
        else {
            printf("All threads are busy...\n");
            return wrapper->get_future();
        }
        
    }

    ~ThreadPool();

private:
    static DWORD WINAPI ThreadStart(LPVOID threadParameters);
    DWORD ThreadMain();
    list<Task> mTasks;
    HANDLE* mThreads;
    int mThreadCount;
    CRITICAL_SECTION mCriticalSection;
    CONDITION_VARIABLE mConditionVariable;
    CONDITION_VARIABLE mConditionVariableTaskFinished;
    int mNumberOfTasksNotFinished;
    bool mConsum;
    bool overFlow = false;
};