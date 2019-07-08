#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "Item.h"
#include "Processor.h"
#include "Result.h"

namespace ik::cpp::task {
	class Manager {
	private:
		std::vector< std::unique_ptr<Processor>> processors;
		std::queue<std::unique_ptr<Item>> queue;
		std::mutex mtx;
		int numThreads;

	public:

		Manager(int numThreads) : numThreads(numThreads)
		{
			for (int i = 0; i < numThreads; i++)
				processors.push_back(std::make_unique<Processor>(i, this));
		}
		~Manager() {
			stop();
		}

		size_t getQueueSize()
		{
			std::lock_guard<std::mutex> lock(mtx);
			return queue.size();
		}

		void addItem(std::unique_ptr<Item> item)
		{
			std::lock_guard<std::mutex> lock(mtx);
			queue.push(std::move(item));
		}

		std::unique_ptr<Result> getNextItem()
		{
			std::lock_guard<std::mutex> lock(mtx);
			std::unique_ptr<Result> result = std::make_unique<Result>();
			if (queue.size())

			{
				result->setItem(std::move(queue.front()));
				queue.pop();				
			}
			return std::move(result);
		}

		void lockUntilEmpty()
		{
			while (getQueueSize())
				std::this_thread::yield();
		}

		void stop()
		{
			std::lock_guard<std::mutex> lock(mtx);
			for (int i = 0; i < numThreads; i++)
				processors[i].get()->running = false;
		}
	};
}