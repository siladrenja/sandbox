#pragma once
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#include <MyIntrinsics.h>

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
	namespace {
		uint32_t AvailableIntrin = 0;

	}
	
	template<size_t Size_X, size_t Size_Y, typename T, bool EnableIntrinsics = false>
	class BasicMatrix {
	public:
		~BasicMatrix() {
		}
		BasicMatrix(T DefaultValue = (T)0) {
			std::fill(_1_MatrixData, _1_MatrixData + Size_X * Size_Y, DefaultValue);

			if (AvailableIntrin == 0) {
				AvailableIntrin = GetIntrinsics();
			}
		}
		BasicMatrix(T InMatrix[Size_Y][Size_X]) {
			if (AvailableIntrin == 0) {
				AvailableIntrin = GetIntrinsics();
			}
			for (unsigned long long i = 0; i < Size_Y; i++) {
				for (unsigned long long j = 0; j < Size_X; j++) {
					_1_MatrixData[i * Size_X + j] = InMatrix[i][j];
				}
			}

			
		}

		BasicMatrix(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& copyMatrix) {
			if (AvailableIntrin == 0) {
				AvailableIntrin = GetIntrinsics();
			}
			std::copy(copyMatrix._1_MatrixData, copyMatrix._1_MatrixData + Size_X * Size_Y, _1_MatrixData);
		}

		T* operator[](size_t N) {
			return (_1_MatrixData + N * Size_X);
		}

		BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> operator+(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& oper) {
			BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> temp;
			if (!EnableIntrinsics || !(AvailableIntrin & (INTRIN_AVX2 || INTRIN_AVX || INTRIN_AVX_512BW || INTRIN_AVX_512F))) {
				

				for (unsigned long long i = 0; i < Size_X * Size_Y; i++) {
					temp._1_MatrixData[i] = _1_MatrixData[i] + oper._1_MatrixData[i];
				}

				return temp;
			} else if (AvailableIntrin & (INTRIN_AVX_512BW || INTRIN_AVX_512F)) {

				return temp;
			}
		}

		BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& operator+=(BasicMatrix<Size_X,Size_Y, T, EnableIntrinsics>& oper) {

			for (unsigned long long i = 0; i < Size_X * Size_Y; i++) {
				 _1_MatrixData[i] += oper._1_MatrixData[i];
			}

			return *this;
		}

		BasicMatrix<Size_Y, Size_X, T, EnableIntrinsics> Transpose() {
			T temp[Size_X][ Size_Y];
			for (unsigned long long i = 0; i < Size_Y; i++) {
				for (unsigned long long j = 0; j < Size_X; j++) {
					temp[i][j] = _1_MatrixData[i * Size_X + j];
				}
			}

			return BasicMatrix<Size_Y, Size_X, T, EnableIntrinsics>(temp);
		}


		//not recommended to temper with
		T* GetRawData() {
			return _1_MatrixData;
		}

	protected:
		//elem = Ycoord * Size_X + Xcoord;
		T _1_MatrixData[Size_X * Size_Y];

	};


#pragma region matrix operators
	template<size_t Size_X, size_t Size_Y, typename T, bool EnableIntrinsics = false>
	BasicMatrix<Size_X, Size_Y, T, true> operator* (long long num, BasicMatrix<Size_X, Size_Y, T, true> mat) {
		T* matrixData = mat.GetRawData();

		

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
