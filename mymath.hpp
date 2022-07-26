#pragma once
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

#ifndef MATRIXPARALTRESHOLD
#define MATRIXPARALTRESHOLD 9
#endif

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

namespace math {
	template<typename T, size_t _1_SizeX, size_t _1_SizeY>
	class Matrix {
	public:
		Matrix() {
			_1_Val = new T[_1_SizeX * _1_SizeY];
		}

		Matrix(const T (**_3_in)) {
			_1_Val = new T[_1_SizeX * _1_SizeY];
			for (size_t _2_y = 0; _2_y < _1_SizeY; _2_y++) {
				for (size_t _2_x = 0; _2_x < _1_SizeX; _2_x++) {
					_1_Val[_2_y * _1_SizeX + _2_x] = _3_in[_2_x][_2_y];
				}
			}
		}

		Matrix(const T (_3_in[_1_SizeX][_1_SizeY])) {
			_1_Val = new T[_1_SizeX * _1_SizeY];
			for (size_t _2_y = 0; _2_y < _1_SizeY; _2_y++) {
				for (size_t _2_x = 0; _2_x < _1_SizeX; _2_x++) {
					_1_Val[_2_y * _1_SizeX + _2_x] = _3_in[_2_x][_2_y];
				}
			}
		}

		Matrix(const Matrix<T, _1_SizeX, _1_SizeY> &_3_in) {
			_1_Val = new T[_1_SizeX * _1_SizeY];
			for (unsigned long long _2_x = 0; _2_x < _1_SizeY * _1_SizeX; _2_x++) {
				*(_1_Val + _2_x) = *(_3_in._1_Val + _2_x);
			}
		}

		T* operator[] (size_t _2_index) {
			return _1_Val + (_2_index * _1_SizeX);
		}

		Matrix<T, _1_SizeX,_1_SizeY>& operator*= (T _2_scalar) {
			for (unsigned long long _2_i = 0; _2_i < _1_SizeX * _1_SizeY; _2_i++) {
				*(_1_Val + _2_i) *= _2_scalar;
			}
			return *this;
		}

		Matrix<T, _1_SizeX, _1_SizeY>  operator+(Matrix<T, _1_SizeX, _1_SizeY>& _2_second) {
			Matrix<T, _1_SizeX, _1_SizeY> temp;

			for (size_t _2_x = 0; _2_x < _1_SizeX; _2_x++) {
				for (size_t _2_y = 0; _2_y < _1_SizeY; _2_y++)
					temp[_2_x][_2_y] = (*this)[_2_x][_2_y] + _2_second[_2_x][_2_y];
			}

			return temp;

		}


		~Matrix() {
			delete _1_Val;
		}

		size_t Rows() { return _1_SizeY; }

		size_t Columns() { return _1_SizeX; }
		
	private:
		T *_1_Val;
	};

	template<typename T, size_t _1_SizeX, size_t _1_SizeY>
	Matrix<T, _1_SizeX, _1_SizeY> operator* (T _2_ind, Matrix<T, _1_SizeX, _1_SizeY> matr) {
		Matrix<T, _1_SizeX, _1_SizeY> temp;
		for (size_t _2_x = 0; _2_x < _1_SizeX; _2_x++) {
			for(size_t _2_y = 0; _2_y < _1_SizeY; _2_y++)
			temp[_2_x][_2_y] = (_2_ind * matr[_2_x][_2_y]);
		}
		return temp;
	}

	template<typename T, size_t _1_SizeX, size_t _1_SizeY>
	Matrix<T, _1_SizeX, _1_SizeY> operator* (Matrix<T, _1_SizeX, _1_SizeY> matr, T _2_ind) {
		Matrix<T, _1_SizeX, _1_SizeY> temp;
		for (size_t _2_x = 0; _2_x < _1_SizeX; _2_x++) {
			for (size_t _2_y = 0; _2_y < _1_SizeY; _2_y++)
				temp[_2_x][_2_y] = (_2_ind * matr[_2_x][_2_y]);
		}
		return temp;
	}

}

