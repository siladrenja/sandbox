#pragma once
#include <list>

namespace extstd {
	template <typename a, class _Alloc = std::allocator<a>>
	class List : public std::list<a, _Alloc> {
	public:
		using std::list<a, _Alloc>::list;

		a& operator*() {
			return this->front();
		}

		a& operator[](size_t index) {
			auto l_front = this->begin();

			std::advance(l_front, index);
			return *l_front;
		}
	};
}