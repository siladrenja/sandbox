#pragma once
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#include <MyIntrinsics.hpp>
#include <vector>

#ifndef ull
#define ull unsigned long long
#endif

#ifndef MATRIXPARALTRESHOLD
#define MATRIXPARALTRESHOLD 9
#endif

namespace custom {
	inline double nthRoot(int A, int N) {
		return pow(N, 1.0 / A);
	}
}


namespace math {
	template<typename T>
	T sum(T val) {
		return val;
	}
	template<typename T, class... args>
	T sum(T val, args ...arg) {
		return val + sum(arg);
	}


	
	template<size_t Size_X, size_t Size_Y, typename T, bool EnableIntrinsics = false>
	class BasicMatrix {
	public:
		~BasicMatrix() {
		}
		BasicMatrix(T DefaultValue = (T)0) {
			std::fill(_1_MatrixData, _1_MatrixData + Size_X * Size_Y, DefaultValue);

		}
		BasicMatrix(T InMatrix[Size_Y][Size_X]) {

			for (unsigned long long i = 0; i < Size_Y; i++) {
				for (unsigned long long j = 0; j < Size_X; j++) {
					_1_MatrixData[i * Size_X + j] = InMatrix[i][j];
				}
			}


		}

		BasicMatrix(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& copyMatrix) {

			std::copy(copyMatrix._1_MatrixData, copyMatrix._1_MatrixData + Size_X * Size_Y, _1_MatrixData);
		}

		T* operator[](size_t N) {
			return (_1_MatrixData + N * Size_X);
		}

		BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> operator+(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& oper) {
			BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> temp;
			if (!EnableIntrinsics || !(GetIntrinsics() & (INTRIN_AVX2 || INTRIN_AVX || INTRIN_AVX_512BW || INTRIN_AVX_512F))) {


				for (unsigned long long i = 0; i < Size_X * Size_Y; i++) {
					temp._1_MatrixData[i] = _1_MatrixData[i] + oper._1_MatrixData[i];
				}

				return temp;
			} else if (GetIntrinsics & (INTRIN_AVX_512BW || INTRIN_AVX_512F)) {

				return temp;
			}
		}

		BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& operator+=(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& oper) {

			for (unsigned long long i = 0; i < Size_X * Size_Y; i++) {
				_1_MatrixData[i] += oper._1_MatrixData[i];
			}

			return *this;
		}

		BasicMatrix<Size_Y, Size_X, T, EnableIntrinsics> Transpose() {
			T temp[Size_X][Size_Y];
			for (unsigned long long i = 0; i < Size_Y; i++) {
				for (unsigned long long j = 0; j < Size_X; j++) {
					temp[i][j] = _1_MatrixData[i * Size_X + j];
				}
			}

			return BasicMatrix<Size_Y, Size_X, T, EnableIntrinsics>(temp);
		}



		//not recommended to temper with
		//T* GetRawData() {
		//	return &(_1_MatrixData[0]);
		//}
		T* GetRawData() { return 0; }
	protected:
		//elem = Ycoord * Size_X + Xcoord;
		T _1_MatrixData[Size_X * Size_Y];

	};


#pragma region matrix * scalar
	template<size_t Size_X, size_t Size_Y, typename T>
	BasicMatrix<Size_X, Size_Y, T, true> operator* (T num, const BasicMatrix<Size_X, Size_Y, T, true>& mat) {
		BasicMatrix<Size_X, Size_Y, T, true> temp;
		std::copy(mat.GetRawData(), mat.GetRawData() + (Size_X * Size_Y), temp.GetRawData());

		MulRow(num, temp.GetRawData, Size_X * Size_Y);

		return temp;
	}

	template<size_t Size_X, size_t Size_Y, typename T>
	BasicMatrix<Size_X, Size_Y, T, true> operator* (const BasicMatrix<Size_X, Size_Y, T, true>& mat, T num) {
		BasicMatrix<Size_X, Size_Y, T, true> temp;
		std::copy(mat.GetRawData(), mat.GetRawData() + (Size_X * Size_Y), temp.GetRawData());

		MulRow(num, temp.GetRawData, Size_X * Size_Y);

		return temp;
	}

	template<size_t Size_X, size_t Size_Y, typename T>
	BasicMatrix<Size_X, Size_Y, T, true>& operator*= (BasicMatrix<Size_X, Size_Y, T, true>& mat, T num) {
		T* matrixData = mat.GetRawData();
		MulRow(num, matrixData, Size_X * Size_Y);
		return mat;
	}


#pragma endregion






	template<typename T, bool EnableIntrinsics = false>
	class BasicVector3 : public BasicMatrix<1, 3, T, EnableIntrinsics> {
	public:
		

		T& X() {
			return this->_1_MatrixData[0];
		}

		T& Y() {
			return this->_1_MatrixData[1];
		}

		T& Z() {
			return this->_1_MatrixData[2];

		}

		struct { T X, Y, Z; } GetPoint() {
			return { this->_1_MatrixData[0], this->_1_MatrixData[1], this->_1_MatrixData[2]};
		}
	private:
		

	};

	using Vector3 = BasicVector3<float, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrix = BasicMatrix<Size_X, Size_Y, float, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixi = BasicMatrix<Size_X, Size_Y, int, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixu = BasicMatrix<Size_X, Size_Y, unsigned, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixull = BasicMatrix<Size_X, Size_Y, unsigned long long, true>;

}
#pragma region matrix *= matrix
template<size_t x, size_t y, size_t x2, typename T, bool optim>
math::BasicMatrix<x2, y, T, optim> mulNoOptim(math::BasicMatrix<x, y, T, optim>& mat1, math::BasicMatrix<x2, x, T, optim>& mat2) {
	math::BasicMatrix<x2, y, T, optim> temp;

	for (size_t i = 0; i < x2; ++i)
		for (size_t j = 0; j < y; ++j)
			for (size_t k = 0; k < x; ++k) {
				temp[i][j] += mat1[k][i] * mat2[j][k];
			}
	return temp;

}

template<size_t X, typename T,
	typename = std::enable_if_t<X == 32 / sizeof(T)>
>
math::BasicMatrix<X, X, T, true>& operator*= (math::BasicMatrix<X, X, T, true>& mat, math::BasicMatrix<X, X, T, true>& mat2) {
	if ((GetIntrinsics() & INTRIN_AVX2)) {
		auto row = mgather(mat.GetRawData(), 32 / sizeof(T));
		std::vector rows(32 / sizeof(T), row);
		auto col = mload(mat2.GetRawData());
		std::vector cols(32 / sizeof(T), col);
		for (size_t i = 1; i < 32 / sizeof(T); i++) {
			rows[i] = mgather(mat[0] + i, 32 / sizeof(T));
			cols[i] = mload(mat2[i]);
		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < 32 / sizeof(T); i++) {
			for (size_t j = 0; j < 32 / sizeof(T); j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} else if (GetIntrinsics() & INTRIN_SSE4_2) {
		auto row = m128gather(mat.GetRawData(), X);
		std::vector rows(X, row);
		row = m128gather(mat.GetRawData() + X * (X/2), X);
		std::vector rows2(X, row);

		auto col = m128load(mat2.GetRawData());
		std::vector cols(X, col);
		col = m128load(mat2.GetRawData()+(X/2));
		std::vector cols2(X, col);

		for (size_t i = 1; i < X; i++) {
			rows[i] = m128gather(mat[0] + i, X);
			rows2[i] = m128gather(mat[0] + i + X*(X/2), X);

			cols[i] = m128load(mat2[i]);
			cols[i] = m128load(mat2[i]+ (X/2));

		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < 32 / sizeof(T); i++) {
			for (size_t j = 0; j < 32 / sizeof(T); j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]) + msumsave(rows2[i] * cols2[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} else {
		math::BasicMatrix<32 / sizeof(T), 32 / sizeof(T), T, true> temp = mulNoOptim<32 / sizeof(T), 32 / sizeof(T), 32 / sizeof(T), T, true>(mat, mat2);
		std::copy(temp.GetRawData(), temp.GetRawData() + (32 / sizeof(T)) * (32 / sizeof(T)), mat.GetRawData());
	}
	return mat;
}




#pragma endregion

#pragma region matrix*matrix
template<size_t X, size_t Y, size_t X2, typename T>
math::BasicMatrix<X2, Y, T, false>& operator* (math::BasicMatrix<X, Y, T, false>& mat, math::BasicMatrix<X2, X, T, false>& mat2) {
	return mulNoOptim<X, Y, X2, T, false>(mat, mat2);
}
#pragma endregion