#include "Processor.h"
#include "Manager.h"
#include <iostream>
#include <cassert>

namespace ik::cpp::task::workqueue {
	Processor::Processor(unsigned id, Manager* mgr) :
		manager(mgr),
		id(id),
		running(true),
		thrd(&Processor::loop, this)
	{
		thrd.detach();
	}

	Processor::~Processor()
	{
		running = false;
		std::lock_guard<std::mutex> lock(mtx);

		if (thrd.joinable())
			thrd.join();
	}

	void Processor::loop()
	{
		std::lock_guard<std::mutex> lock(mtx);

		while (running) {

			auto result = manager->getNextItem();
			
			if (result->isOk()) {
				result->unwrap()->execute();
				std::this_thread::yield();				
			}
			else {
				std::this_thread::yield();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));				
			}
		}
	}
}