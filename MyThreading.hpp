#pragma once
#include <thread>
#include <atomic>
#include <queue>



namespace CustomThreading {
	// https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
	template <class T>
	class SafeQueue
	{
	public:
		SafeQueue(void)
			: q()
			, m()
			, c()
		{}

		~SafeQueue(void)
		{}

		// Add an element to the queue.
		void Add(T t)
		{
			std::lock_guard<std::mutex> lock(m);
			q.push(t);
			c.notify_one();
		}

		// Get the "front"-element.
		// If the queue is empty, wait till a element is avaiable.
		T Read(void)
		{
			std::unique_lock<std::mutex> lock(m);
			while (q.empty())
			{
				// release lock as long as the wait and reaquire it afterwards.
				c.wait(lock);
			}
			T val = q.front();
			q.pop();
			return val;
		}

	private:
		std::queue<T> q;
		mutable std::mutex m;
		std::condition_variable c;
	};

	namespace {
		void ListenerFoo() {

		}
	}
		
	template<typename Size, class ...args>
	class ThreadPool {
	public:
	protected:
		std::thread Threads[Size];
		SafeQueue<
	};
		
		
}

	
