#include <functional>
#include <vector>
#include <iostream>
#include <future>
#include <thread>
#include <condition_variable>
#include <queue>

class ThreadPool {
public:
	using Task = std::function<void()>;

	explicit ThreadPool(std::size_t numThreads) {
		start(numThreads);
	}
	~ThreadPool() {
		stop();
	}

	template<class T>
	auto addTask(T task)->std::future<decltype(task())>
	{
		auto wrapper = std::make_shared < std::packaged_task<decltype(task())()>>(std::move(task));
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

	void start(std::size_t numThreads) {
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
	void stop() noexcept {
		{
			std::unique_lock<std::mutex> lock{ mEventMutex };
			isStopping = true;
		}
		mEventVar.notify_all();
		for (auto& thread : mThreads) {
			thread.join();
		}

	}
};

int main(){
	ThreadPool pool(36);
	auto f1=pool.addTask([] {
		return 1;
		});
	auto f2 = pool.addTask([] {
		return 2;
		});
	std::cout << (f1.get() + f2.get()) << std::endl;
	return 0;
}