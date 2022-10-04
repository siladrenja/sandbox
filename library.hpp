#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctype.h>
#include <limits>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cwctype>
#include <type_traits>
#include <thread>
#include <regex>
#include <cstdio>
#include <stdint.h>

#include <iostream>

#define maxi64 0xEFFFFFFF

#pragma warning(disable:4146)


#ifndef yeet
#define yeet throw
#endif

#ifndef baby
#define baby std::exception
#endif


typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  i8u;
typedef uint16_t i16u;
typedef uint32_t i32u;
typedef uint64_t i64u;





namespace custom {
	//using namespace std;

	void ReplaceAllOccurances(std::string &a,std::string s, std::string t) {
		std::string::size_type n = 0;
		while ((n = a.find(s, n)) != std::string::npos) {
			a.replace(n, s.size(), t);
			n += t.size();
		}
	}



	bool invalidChar(wchar_t c) {
		return !(c >= 0 && c < 128);
	}




}





namespace extstd {

	template<typename T>
	class Range {
	public:

		struct Iterator {
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;  // or also value_type*
			using reference = T&;
			
			Iterator(value_type val, long long __Step) : m_ptr(val) { Step = __Step; }

			reference operator*() { return m_ptr; }
			pointer operator->() { return m_ptr; }

			// Prefix increment
			Iterator& operator++() {
				m_ptr+=Step; return *this; 
			}

			// Postfix increment
			Iterator operator++(int) { Iterator tmp = *this; m_ptr+=Step; return tmp;  }

			friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
			friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

		private:

			value_type m_ptr;
			long long Step;
		};

		Iterator begin() { if (Step > 0) return Iterator(low, Step); else return Iterator(high, Step); }
		Iterator end() { if (Step > 0) return Iterator(high, Step); else return Iterator(low, Step); }

		Range(T from, T to) {
			if (from < to) {
				low = from;
				high = to;
			} else {
				low = to;
				high = from;
			}
		}

		Range(T from, long long _step, T to) {
			Step = _step;

			if (from < to) {
				low = from;
				high = to;
				
			} else {
				low = to;
				high = from;
			}
		}
		~Range() {};

		inline bool isInRange(T num) {
			return(num >= low && num < high);
		}
	protected:
		T low, high;
		long long Step = 1;

	};

	template<typename T>
	bool operator==(T arg1, Range<T> arg2) {
		return arg2.isInRange(arg1);
	}
	template<typename T>

	bool operator==(Range<T> arg1, T arg2) {
		return arg1.isInRange(arg2);
	}

	template<typename T>
	class Uncertainty : public Range<T> {
	public:
		Uncertainty(T value, T _uncertainty) : Range<T>(value - _uncertainty, value + _uncertainty+1) {};
		
	};

	template<typename T>
	using Tolerance = Uncertainty<T>;

	template<typename T>
	bool operator==(T arg1, Uncertainty<T> arg2) {
		return arg2.isInRange(arg1);
	}
	template<typename T>

	bool operator==(Uncertainty<T> arg1, T arg2) {
		return arg1.isInRange(arg2);
	}

	template<typename T = std::string>
	T Read() {
		T a;
		std::cin >> a;
		return a;
	}

	template<typename ...arg >
	void Read(const char* eq, arg&... args ) {
		
		scanf_s(eq, &args...);
		return;
	}


	std::string ReadLine() {
		std::string a;
		std::getline(std::cin, a, '\n');
		return a;
	}

	
	template<typename T>
	void Write(const T& toWrite) {
		
		std::cout << toWrite;
	}
	template<typename T>
	void WriteLine(const T& toWrite) {

		std::cout << toWrite << '\n';
	}


	void Write(const std::string& toWrite) {

		std::cout << toWrite;
	}

	void WriteLine(const std::string& toWrite) {

		std::cout << toWrite << '\n';
	}

	namespace {
		template<typename T>
		void _1_FormatString(std::string& Eq, const size_t countFrom, T ar) {
			custom::ReplaceAllOccurances(Eq, (std::string("{") + std::to_string(countFrom) + "}"), std::to_string(ar));

		}

		template<typename T, typename... args>
		void _1_FormatString(std::string& Eq, const size_t countFrom, T ar, args... a) {
			custom::ReplaceAllOccurances(Eq, (std::string("{") + std::to_string(countFrom) + "}"), std::to_string(ar));

			for (unsigned long long i = countFrom + 1; i < Eq.size(); i++) {

				if ((Eq.find(std::string("{") + std::to_string(i) + "}") != std::string::npos)) {
					_1_FormatString(Eq, i, a...);
					break;
				}
			}
		}
	}
	template<typename... args>
	std::string FormatString(std::string _1_str, args...a) {
		_1_FormatString(_1_str, 0, a...);
		return _1_str;
	}

	template<typename... args>
	void Write(std::string Eq, args... a) {

		_1_FormatString(Eq, 0, a...);

	
		std::cout << Eq;
		return;
	}
	template<typename... args>
	void WriteLine(std::string Eq, args... a) {
		Write((Eq + '\n'), a...);
		return;
	}

	

	template<typename T>
	void Write(const std::vector<T>& toWrite, const char* delim) {
		std::cout << std::pair{ toWrite, delim };
	}
	template<typename T>
	void WriteLine(const std::vector<T>& toWrite, const char* delim) {
		std::cout << std::pair{ toWrite, delim } << '\n';
		
	}

	template<typename T>
	void Write(const std::vector<T>& toWrite, const std::string& delim) {
		std::cout << std::pair{ toWrite, delim.c_str() };
	}
	template<typename T>
	void WriteLine(const std::vector<T>& toWrite, const std::string& delim) {
		std::cout << std::pair{ toWrite, delim.c_str() } << '\n';

	}
}



template <typename T>
std::ostream& operator<< (std::ostream& _1_stream, const std::vector<T>& _1_in) {

	for (T _2_elem : _1_in) {
		_1_stream << _2_elem;
	}

	return _1_stream;
}




template <typename _1_T>
std::ostream& operator<< (std::ostream& _1_stream, std::pair<std::vector<_1_T>, const char*> _1_stru) {
	_1_stream << _1_stru.first[0];
	_1_stru.first.erase(_1_stru.first.begin());

	
	for (_1_T& _2_elem : _1_stru.first) {
		_1_stream << _1_stru.second << _2_elem ;
	}

	return _1_stream;
}

template <typename _1_T>
std::ostream& operator<< (std::ostream& _1_stream, const std::pair<_1_T*, _1_T*>& _1_stru) {
	
	_1_T* _pointer = _1_stru.first;
	while (_pointer != _1_stru.second) {
		_1_stream << *(_pointer++) << ' ';
	}

	return _1_stream;
}


#pragma region More Ints
using i128 = i64u[2];
using i256 = i64u[4];

#pragma endregion