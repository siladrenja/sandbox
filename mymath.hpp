#pragma once
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

namespace custom {
	inline double nthRoot(int A, int N) {
		return pow(N, 1.0 / A);
	}
}

namespace mathPars {
	using namespace std;

	char OpenBrackets[] = { '(', '{', '[' };
	char CloseBrackets[] = { ')', '}', ']' };


	string toreplace[] = { "sin", "cos", "tan", "a$s","a$c" , "a$t", " ", "pi", "abs", "sqrt", "arc$c" };
	string replacewith[] = { "$s", "$c", "$t", "$e", "$b", "$d", "", "3.14159265", "$a" , "$r", "$b" };

	char functions[] = { 's', 'c', 't', 'e', 'b', 'd', 'a', 'r' }; // $s, s = sine, c = cosine, t = tan, e = asin, b= acos, atan

	double(*foo[])(double) = { sin, cos, tan, asin, acos, atan, abs, sqrt };

	int T = 0;
	int M = 0;


	double getNextNumber(string expression, int startposition) {
		int i = startposition;
		int N = 0;
		for (; startposition < expression.length(); startposition++) {
			if (isdigit(expression[startposition]) || (!isdigit(expression[startposition - 1]) && expression[startposition] == '-')) {

			} else if (expression[startposition] == '.') {
				N++;
			} else if (expression[startposition] == ',') {
				expression[startposition] == '.';
				N++;
			} else if (N > 1) {
				throw std::invalid_argument("Segmentation Fault. Expression contains multiple decimal dots in a same number");
			} else {
				startposition--;
				break;
			}
		}


		T = startposition;
		return stod(expression.substr(i, startposition - i + 1));
	}


	double getPrevNumber(string expression, int startposition) {
		int i = startposition;
		int N = 0;
		for (; startposition >= 0; startposition--) {
			if (isdigit(expression[startposition]) || (startposition == 0 && expression[startposition] == '-')) {

			} else if (expression[startposition] == '.') {
				N++;
			} else if (expression[startposition] == ',') {
				expression[startposition] == '.';
				N++;
			} else if (N > 1) {
				throw std::invalid_argument("Segmentation Fault. Expression contains multiple decimal dots in a same number");
			} else {

				break;
			}
		}
		startposition++;
		M = startposition;
		return stod(expression.substr(startposition, i - startposition + 1));
	}

	void ReplaceAbs(string& expression) {
		int absCount = 0;
		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '|') {
				absCount++;
			}
		}

		if ((absCount % 2) != 0) {
			throw invalid_argument("Segmentation Fault. Unbalanced absolute brackets");
		}

		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '|') {
				expression.replace(i, 1, "$a(");
			}

			if (expression[expression.length() - i] == '|') {
				expression[expression.length() - i] = ')';
			}
		}
	}

	//2+31+5
	double pars(string expression) {
		int k = 0;
		bool openBrackets = false;

		int begin = 1;
		int end = 0;

		for (int i = 0; i < sizeof(toreplace) / sizeof(toreplace[0]); i++) {
			auto a = [ a = expression, s = toreplace[i], t = replacewith[i]](std::string a, std::string s, std::string t) {
			//(, std::string , std::string) {
				std::string::size_type n = 0;
				while ((n = a.find(s, n)) != std::string::npos) {
					a.replace(n, s.size(), t);
					std::string b;
					
					n += t.size();
				}
			
		};
		}

		ReplaceAbs(expression);

		for (int i = 0; i < expression.length(); i++) {
			char a = expression[i];
			if (std::find(std::begin(OpenBrackets), std::end(OpenBrackets), a) != std::end(OpenBrackets)) {
				k++;

			} else if (std::find(std::begin(CloseBrackets), std::end(CloseBrackets), a) != std::end(CloseBrackets)) {
				k--;
			}

			if (k == 0 && !openBrackets) {
				begin++;

			} else if (k > 0) {
				end++;
				openBrackets = true;
			} else if (k < 0) {
				throw std::invalid_argument("Invalid brackets");
			} else if (k == 0 && openBrackets) {
				openBrackets = false;

				expression.replace(begin - 1, end + 1, to_string(pars(expression.substr(begin, end - 1))));
				i = -1;
				//begin = begin + end+3;
				begin = 1;
				end = 0;
			}
		}
		//sin((3*2)/(5+7))
		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '$') {
				if (expression[i + 2] != '-') {
					for (int j = 0; j < sizeof(functions) / sizeof(functions[0]); j++) {
						if (expression[i + 1] == functions[j]) {
							double temp = foo[j](getNextNumber(expression, i + 2));
							expression.replace(i, T - i, to_string((temp)));
							break;
						}
					}
				} else {
					for (int j = 0; j < sizeof(functions) / sizeof(functions[0]); j++) {
						if (expression[i + 1] == functions[j]) {
							double temp = foo[j](getNextNumber(expression, i + 2));
							expression.replace(i, T - i, to_string((temp)));
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '^') {
				double a = pow(getPrevNumber(expression, i - 1), getNextNumber(expression, i + 1));
				expression.replace(M, T - M, to_string((a)));
				i = 0;

			} else if (expression[i] == '~') {
				double a = custom::nthRoot((int)getPrevNumber(expression, i - 1), (int)getNextNumber(expression, i + 1));
				expression.replace(M, T - M, to_string((a)));
				i = 0;
			}
		}

		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '*') {
				double a = getPrevNumber(expression, i - 1) * getNextNumber(expression, i + 1);
				expression.replace(M, T - M, to_string((a)));
				i = 0;

			} else if (expression[i] == '/') {
				double a = getPrevNumber(expression, i - 1) / getNextNumber(expression, i + 1);
				expression.replace(M, T - M, to_string((a)));
				i = 0;
			}
		}

		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '+') {
				double a = getPrevNumber(expression, i - 1) + getNextNumber(expression, i + 1);
				expression.replace(M, T - M, to_string((a)));
				i = 0;

			} else if (expression[i] == '-') {
				if ((i > 0) ? (!isdigit(expression[i - 1])) : true) {

				} else {
					double a = getPrevNumber(expression, i - 1) - getNextNumber(expression, i + 1);
					expression.replace(M, T - M, to_string((a)));
					i = 0;
				}
			}
		}

		return stod(expression);

	}


}