#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include "Work/Manager.h"




class MyItem : public ik::cpp::task::Item {
public:

	void execute() override
	{
		int o = 0;
		//for (int j = 0; j < 50000000; j++) { // burn test - suprisingly fast
		for (int j = 0; j < 50000; j++) {
			o += j;
		}
		std::cout << o << std::endl;
	}
};

int main()
{
	ik::cpp::task::Manager mgr(std::thread::hardware_concurrency());

	for (int i = 0; i < 500; i++) {
		auto item = std::make_unique<MyItem>();
		mgr.addItem(std::move(item));
	}

	std::cout << mgr.getQueueSize() << std::endl;

	std::queue<int> queue;

	queue.push(1);
	queue.push(2);
	queue.push(3);
	std::cout << queue.front() << std::endl;
	queue.pop();
	std::cout << queue.front() << std::endl;
	queue.pop();
	std::cout << queue.front() << std::endl;
	queue.pop();

	std::cout << "end reached" << std::endl;

	
	mgr.lockUntilEmpty();
	mgr.stop();


	std::cout << "defo empty" << std::endl;

	return 0;
}