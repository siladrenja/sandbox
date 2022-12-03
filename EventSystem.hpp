#pragma once
#include <functional>
#include <iostream>
#include <thread>

namespace EventSystem {
	template <typename... args>
	class Event {
	public:
		Event() {
			//functions = (std::function<void(args...)>*) std::malloc(sizeof(std::function<void(args...)>) * 2);
		}

		~Event() {
			if (functions != 0)delete[] functions;
		}

		Event& operator+=(std::function<void(args...)> foo) {
			std::function<void(args...)>* temp = functions;
			functions = new std::function<void(args...)>[sz+1];
			std::copy(temp, temp + sz, functions);
			functions[sz++] = foo;
			if(temp!=0 && temp != functions)delete[] temp;
			return *this;
		}

		void Invoke(args ...ar) {
			for (size_t i = 0; i < sz; i++) {
				functions[i](ar...);
			}
		}


	private:
		std::function<void(args...)>* functions = 0;
		size_t sz = 0;
	};
}