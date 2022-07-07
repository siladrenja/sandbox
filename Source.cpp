#include "CustomString.hpp"
#include "library.h"
#include "WindowsSpecificExtentions.hpp"
#include <iostream>
#include "MyLinkedList.h"
#include "MyThreading.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace extstd;
using namespace CustomThreading;

void TestFunc(const int& arg) {
	for (int i = arg; i < 1000; i++) WriteLine(i);
	return;
}

void Test(int a) {
	return;
}



int main() {
	
	try {
		int a;

		a = Read<int>();

		Write("{0}", a);
	} catch (baby exc) {
		Write(exc.what());
	}
}