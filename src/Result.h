#pragma once
#include "Item.h"

namespace ik::cpp::task::workqueue {
	class Result {
	public:
		Result() {};
		~Result() {};

		std::unique_ptr<Item> unwrap() {
			return std::move(item);
		}
		bool isOk() {
			return item != nullptr;
		}
		void setItem(std::unique_ptr<Item> val) {
			item = std::move(val);
		}

	private:
		std::unique_ptr<Item> item = { nullptr };
	};
}