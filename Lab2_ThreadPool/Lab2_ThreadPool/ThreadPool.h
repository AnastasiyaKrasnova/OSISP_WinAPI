#pragma once
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <string>
#include <vector>
#include <queue>
#include "Logger.h"

class ThreadPool
{
public:

	explicit ThreadPool(std::size_t numThreads);
	~ThreadPool()  noexcept;

	Logger log;
	using Task = std::function<void()>;
	int _threadsCount = { 1 };
	int threadsCount();

	template<class Func, class... Args>
	auto addTask(Func&& func, Args&&...args) ->std::future<typename std::result_of<Func(Args...)>::type>
	{
		{
			std::unique_lock<std::mutex> lock{ mEventMutex };
				using returnType = typename std::result_of<Func(Args...)>::type;
				auto wrapper = std::make_shared< std::packaged_task<returnType()> >([func, args...]() { return func(args...); });
				if (mTasks.size() + 1 <= mThreads.size()) {
					mTasks.emplace([=] {(*wrapper)(); });
					mEventVar.notify_one();
					log.logTaskAdding(mTasks.size());
					return wrapper->get_future();
				}
				else {
					log.logTaskAddingError();
					printf("All threads are busy...\n");
					return wrapper->get_future();
			}	
		}
	}

private:
	std::vector<std::thread> mThreads;
	std::condition_variable mEventVar;
	std::mutex mEventMutex;
	std::queue<Task> mTasks;
	bool isStopping = false;

	void start(std::size_t numThreads);
	void stop();
};
