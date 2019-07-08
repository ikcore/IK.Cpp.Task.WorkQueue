#pragma once
#include <iostream>

namespace ik::cpp::task
{
	class Item {
	public:
		virtual void execute() {
			std::cout << "exec item" << std::endl;
		};
	};
}