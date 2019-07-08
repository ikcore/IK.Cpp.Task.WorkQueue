#pragma once

#include "Item.h"
#include <thread>
#include <mutex>

namespace ik::cpp::task
{
	class Manager;
	class Processor {
	private:
		Manager* manager;
		unsigned id;
		std::thread thrd;
		std::mutex mtx;

	public:
		Processor(unsigned id, Manager* mgr);
		~Processor();
		void loop();
		bool running;
	};
}
