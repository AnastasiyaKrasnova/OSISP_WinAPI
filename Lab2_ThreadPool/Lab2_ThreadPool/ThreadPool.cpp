#include "ThreadPool.h"


ThreadPool::ThreadPool(std::size_t numThreads) {
	start(numThreads);
}

ThreadPool::~ThreadPool() {
	stop();
}

//template<class T, class... Args>

/*std::string ThreadPool::getCurrentTimeData_()
{
	time_t seconds = time(NULL);
	tm* timeInfo = localtime_s(&seconds);
	std::string result = asctime(timeInfo);
	return result;
}*/

int ThreadPool::threadsCount()
{
	return _threadsCount;
}

void ThreadPool::start(std::size_t numThreads) {
	for (auto i = 0; i < numThreads; i++) {
		mThreads.emplace_back([=] {
			while (true) {
				Task task;
				{
					std::unique_lock<std::mutex> lock{ mEventMutex };
					mEventVar.wait(lock, [=] {return isStopping || !mTasks.empty(); });
					if (isStopping && mTasks.empty()) break;
					task = std::move(mTasks.front());
					mTasks.pop();
				}
				task();
			}

			});
	}
}
void ThreadPool::stop() {
	{
		std::unique_lock<std::mutex> lock{ mEventMutex };
		isStopping = true;
	}
	mEventVar.notify_all();
	for (auto& thread : mThreads) {
		thread.join();
	}
}

