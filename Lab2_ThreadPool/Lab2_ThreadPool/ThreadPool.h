#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <string>
#include <vector>
#include <queue>
class ThreadPool
{
public:
	using Task = std::function<void()>;
	int _threadsCount = { 1 };

	explicit ThreadPool(std::size_t numThreads);
	~ThreadPool()  noexcept;

	int threadsCount();

	template<class Func, class... Args>
	auto addTask(Func&& func, Args&&...args) ->std::future<typename std::result_of<Func(Args...)>::type>
	{
		using returnType = typename std::result_of<Func(Args...)>::type;
		auto wrapper = std::make_shared< std::packaged_task<returnType()> >(
			[func, args...]() { return func(args...); });
		{
			std::unique_lock<std::mutex> lock{ mEventMutex };
			mTasks.emplace([=] {
				(*wrapper)();
				});
		}
		mEventVar.notify_one();
		return wrapper->get_future();
	}

private:

	std::vector<std::thread> mThreads;
	std::condition_variable mEventVar;
	std::mutex mEventMutex;
	std::queue<Task> mTasks;
	bool isStopping = false;

	void start(std::size_t numThreads);
	void stop();
	//std::string getCurrentTimeData_();
};
