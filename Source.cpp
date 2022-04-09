#include "CustomString.hpp"
#include <iostream>

using namespace std;

int main() {
	
	try {
		//extstd::experimental::massInt a;
		//a.SetVal(950);

		//cout << a.toString();
		using namespace extstd;

		String str1 = "Hello";
		String str2;
		
		str2 = "world!";
		cout << str1 + str2.toUpper();


		system("PAUSE");
	} catch (std::exception exc) {
		cout << exc.what();
	}
}