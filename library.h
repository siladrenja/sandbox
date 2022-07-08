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

#include <iostream>



#pragma warning(disable:4146)


#ifndef yeet
#define yeet throw
#endif

#ifndef baby
#define baby std::exception
#endif









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


	template<typename T = std::string>
	T Read() {
		T a;
		std::cin >> a;
		return a;
	}

	template<typename ...arg>
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
	void FormatString(std::string& Eq, const size_t countFrom, T ar) {
		custom::ReplaceAllOccurances(Eq,(std::string("{") + std::to_string(countFrom) + "}"), std::to_string(ar));

	}

	template<typename T, typename... args>
	void FormatString(std::string& Eq,  const size_t countFrom, T ar, args... a) {
		custom::ReplaceAllOccurances(Eq, (std::string("{") + std::to_string(countFrom) + "}"), std::to_string(ar));
	
		for (unsigned long long i = countFrom + 1; i < Eq.size(); i++) {
	
			if ((Eq.find(std::string("{") + std::to_string(i) + "}") != std::string::npos)) {
				FormatString(Eq, i, a...);
				break;
			}
		}
	}
	
	template<typename... args>
	void Write(std::string Eq, args... a) {
		for (unsigned long long i = 0; i < Eq.size(); i++) {
			
			if ((Eq.find(std::string("{") + std::to_string(i) + "}") != std::string::npos)) {
				FormatString(Eq, 0, a..., i);
				break;
			}
		}
	
		std::cout << Eq;
		return;
	}
	template<typename... args>
	void WriteLine(std::string Eq, args... a) {
		Write((Eq + '\n'), a...);
		return;
	}

	template<typename T>
	void WriteLine(const T& toWrite) {
		
		std::cout << toWrite << '\n';
	}
}

