#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadCount)
{
    mThreadCount = threadCount;
    mThreads = new HANDLE[mThreadCount];

    InitializeCriticalSection(&mCriticalSection);
    InitializeConditionVariable(&mConditionVariable);
    InitializeConditionVariable(&mConditionVariableTaskFinished);
    mConsum = true;
    for (int i = 0; i < mThreadCount; i++)
        mThreads[i] = CreateThread(NULL, 0, ThreadStart, (void*)this, 0, NULL);
}


DWORD WINAPI ThreadPool::ThreadStart(LPVOID threadParameters) 
{
    ThreadPool* referenceToThis = (ThreadPool*)threadParameters;
    return referenceToThis->ThreadMain();
}

DWORD ThreadPool::ThreadMain() 
{
    do
    {
        Task currentTask;
        EnterCriticalSection(&mCriticalSection);

        while (mTasks.size() == 0 && mConsum)
            SleepConditionVariableCS(&mConditionVariable, &mCriticalSection, INFINITE);

        if (!mConsum)
        {
            LeaveCriticalSection(&mCriticalSection);
            return 0;
        }
        currentTask = mTasks.front();
        mTasks.pop_front();

        LeaveCriticalSection(&mCriticalSection);
        currentTask();
        WakeConditionVariable(&mConditionVariableTaskFinished);
    } while (mConsum);

    return 0;
}

ThreadPool::~ThreadPool()
{
    mConsum = false;
    WakeAllConditionVariable(&mConditionVariable);
    WaitForMultipleObjects(mThreadCount, mThreads, true, INFINITE);
    DeleteCriticalSection(&mCriticalSection);
}