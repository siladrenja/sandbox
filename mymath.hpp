#pragma once
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#include <MyIntrinsics.hpp>
#include <vector>



#ifndef MATRIX_DETERMINANT_PARALEL_TRESHOLD
#define MATRIX_DETERMINANT_PARALEL_TRESHOLD 6
#endif

namespace custom {
	inline double nthRoot(int A, int N) {
		return pow(N, 1.0 / A);
	}
}


namespace math {
	template<typename T>
	T sum(const T* val, size_t sz) {
		T _sum = 0;
		for (; sz > 0; sz--) {
			_sum += val[sz - 1];
		}
		return _sum;
	}

	template<typename T>
	T sum(const std::vector<T>& _in) {
		T _sum = 0;

		for (const T& val : _in) {
			_sum += val;
		}

		return _sum;
	}
	


	
	template<size_t Size_X, size_t Size_Y, typename T, bool EnableIntrinsics = false>
	class BasicMatrix {
	public:
		
		BasicMatrix(T DefaultValue = (T)0) {
			_1_MatrixData = new T[Size_X * Size_Y];
			std::fill(_1_MatrixData, _1_MatrixData + Size_X * Size_Y, DefaultValue);

		}
		BasicMatrix(T InMatrix[Size_Y][Size_X]) {
			_1_MatrixData = new T[Size_X * Size_Y]; 

			for (unsigned long long i = 0; i < Size_Y; i++) {
				for (unsigned long long j = 0; j < Size_X; j++) {
					_1_MatrixData[i * Size_X + j] = InMatrix[i][j];
				}
			}


		}

		BasicMatrix(T InArray[Size_X * Size_Y]) {
			_1_MatrixData = new T[Size_X * Size_Y]; 

			std::copy(InArray, InArray + Size_X * Size_Y, _1_MatrixData);
		}

		BasicMatrix(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& copyMatrix) {
			_1_MatrixData = new T[Size_X * Size_Y];

			std::copy(copyMatrix._1_MatrixData, copyMatrix._1_MatrixData + Size_X * Size_Y, _1_MatrixData);
		}
		~BasicMatrix() {
			delete _1_MatrixData;
		}
		T* operator[](size_t N) const {
			return _1_MatrixData + N * Size_X;
		}

		BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> operator+(BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics>& oper) {
			BasicMatrix<Size_X, Size_Y, T, EnableIntrinsics> temp;
			if (!EnableIntrinsics || !(GetIntrinsics() & (INTRIN_AVX2 || INTRIN_AVX || INTRIN_AVX_512BW || INTRIN_AVX_512F))) {


				for (unsigned long long i = 0; i < Size_X * Size_Y; i++) {
					temp._1_MatrixData[i] = _1_MatrixData[i] + oper._1_MatrixData[i];
				}

				return temp;
			} else if (GetIntrinsics() & (INTRIN_AVX_512BW || INTRIN_AVX_512F)) {

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
		T* GetRawData() const {
			return _1_MatrixData;
		}

		void ResetDeterminant() {
			determinant = 0;
		}

		friend T det(const math::BasicMatrix<Size_X, Size_X, T, EnableIntrinsics>& mat);
	
	protected:
		//elem = Ycoord * Size_X + Xcoord;
		T *_1_MatrixData;

		T determinant = 0;

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


#pragma region matrix Transformations
	template<size_t FirstRow, size_t LastRow, size_t X, size_t Y, typename T, bool Optim, typename = std::enable_if_t<FirstRow < LastRow>>
	BasicMatrix<X, Y-(LastRow - FirstRow + 1), T, Optim> removeColumns(const BasicMatrix<X,Y, T, Optim>& mat) {
		T temp[X * Y - (LastRow - FirstRow + 1)];

		if(FirstRow != 0)
		std::copy(mat.GetRawData(), mat.GetRawData() + (FirstRow * Y), temp);

		if(LastRow < X-1)
		std::copy(mat.GetRawData() + (LastRow + 1) * Y, mat.GetRawData() + X * Y, temp + (FirstRow * Y));

		return BasicMatrix<X, Y - (LastRow - FirstRow + 1), T, Optim>(temp);
	}


	template< size_t X, size_t Y, typename T, bool Optim>
		BasicMatrix<X-1, Y - 1, T, Optim> removeCross(const BasicMatrix<X, Y, T, Optim>& mat, size_t _x, size_t _y) {
			BasicMatrix<X - 1, Y - 1, T, Optim> temp;
			char reduceX = 0, reduceY = 0;
			for (size_t x = 0; x < X; x++) {
				for (size_t y = 0; y < Y; y++) {
					if (x = _x) { reduceX = 1; continue; };
					if (y = _y) { reduceY = 1; continue; };

					temp[x-reduceX][y-reduceY] = mat[x][y];
				}
			}

			return temp;
		}
#pragma endregion

	template<typename T, bool EnableIntrinsics = false>
	struct BasicVector2 {
	public:
	public:
		T X, Y;
		BasicVector2() {}
		BasicVector2(const T& _X, const T& _Y) {
			X = _X;
			Y = _Y;
		}

		BasicVector2(const BasicVector2& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
		}

		BasicVector2& operator=(const BasicVector2& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
			return *this;
		}

	private:
	};

	template<typename T, bool EnableIntrinsics = false>
	struct BasicVector3 {
	public:
		T X, Y, Z;
		BasicVector3() {}
		BasicVector3(T _X, T _Y, T _Z) {
			X = _X;
			Y = _Y;
			Z = _Z;
		}

		BasicVector3(const BasicVector3& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
			Z = CopyConst.Z;
		}

		BasicVector3& operator=(const BasicVector3& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
			Z = CopyConst.Z;
			return *this;
		}

	private:
	};

	template<typename T, bool EnableIntrinsics = false>
	struct BasicVector4 {
	public:
		T X, Y, Z, W;
		BasicVector4() {}
		BasicVector4(T _X, T _Y, T _Z, T _W) {
			X = _X;
			Y = _Y;
			Z = _Z;
			W = _W;
		}

		BasicVector4(const BasicVector4& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
			Z = CopyConst.Z;
			W = CopyConst.W;

		}

		BasicVector4& operator=(const BasicVector4& CopyConst) {
			X = CopyConst.X;
			Y = CopyConst.Y;
			Z = CopyConst.Z;
			W = CopyConst.W;
			return *this;
		}

	private:
	};

	using Vector4 = BasicVector4<float, true>;
	using Vector3 = BasicVector3<float, true>;
	using Vector2 = BasicVector2<float, true>;
	


	template<size_t Size_X, size_t Size_Y>
	using Matrix = BasicMatrix<Size_X, Size_Y, float, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixd = BasicMatrix<Size_X, Size_Y, double, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixi = BasicMatrix<Size_X, Size_Y, int, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixu = BasicMatrix<Size_X, Size_Y, unsigned, true>;

	template<size_t Size_X, size_t Size_Y>
	using Matrixull = BasicMatrix<Size_X, Size_Y, unsigned long long, true>;



#pragma region determinants
	template<size_t X, typename T, bool optim>
	inline T det(const math::BasicMatrix<2, 2, T, optim>& mat) {
		return (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);
	}

	

	template<size_t X, typename T, bool optim>
	T det(const math::BasicMatrix<X, X, T, optim>& mat) {
		if (mat.determinant != 0)return mat.determinant;

		switch (X >= MATRIX_DETERMINANT_PARALEL_TRESHOLD) {
		case true:
		{
			std::vector<std::thread> threads(X, std::thread());
			std::vector<T> results(X, T());
			std::vector<bool> threadfinished(X, false);
		
			for (size_t i = 0; i < X; i++) {
				threads[i] = std::thread([&results, &threadfinished, &mat](size_t threadIndex) {
						results[threadIndex] = det(removeCross(mat, threadIndex, 0));
						threadfinished[threadIndex] = true;
					}, i);
		
			}
			while (sum(threadfinished) > 0);
			mat.determinant = sum(results);
			return mat.determinant;
		}
		case false:
		{
			std::vector<T> results(X, T());
			for (size_t i = 0; i < X; i++) {
				results[i] = det(removeCross(mat, i, 0));

			}
			mat.determinant = sum(results);
			return mat.determinant;
		}
		}
	}

#pragma endregion

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

template<size_t X, typename T,typename = std::enable_if_t<X == 64 / sizeof(T)>, typename = std::enable_if_t<true>>
math::BasicMatrix<X, X, T, true>& operator*= (math::BasicMatrix<X, X, T, true>& mat, math::BasicMatrix<X, X, T, true>& mat2) {
	if ((GetIntrinsics() & INTRIN_AVX_512F)) {
		auto row = m512gather(mat.GetRawData(), X);
		std::vector rows(X, row);
		auto col = m512load(mat2.GetRawData());
		std::vector cols(X, col);
		for (size_t i = 1; i < X; i++) {
			rows[i] = m512gather(mat[0] + i, X);
			cols[i] = m512load(mat2[i]);
		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} else if(GetIntrinsics() & INTRIN_AVX2) {
		auto row = mgather(mat.GetRawData(), X);
		std::vector rows(X, row);
		row = mgather(mat.GetRawData() + X * (X / 2), X);
		std::vector rows2(X, row);

		auto col = mload(mat2.GetRawData());
		std::vector cols(X, col);
		col = mload(mat2.GetRawData() + (X / 2));
		std::vector cols2(X, col);

		for (size_t i = 1; i < X; i++) {
			rows[i] = mgather(mat[0] + i, X);
			rows2[i] = mgather(mat[0] + i + X * (X / 2), X);

			cols[i] = mload(mat2[i]);
			cols2[i] = mload(mat2[i] + (X / 2));

		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave((rows[i] * cols[j]) + (rows2[i] * cols2[j]));
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} 
	else if (GetIntrinsics() & INTRIN_SSE4_2) {
		auto row = m128gather(mat.GetRawData(), X);
		std::vector rows(X, row);
		row = m128gather(mat.GetRawData() + X * (X / 4), X);
		std::vector rows2(X, row);
		row = m128gather(mat.GetRawData() + X * (X / 2), X);
		std::vector rows3(X, row);
		row = m128gather(mat.GetRawData() + X * (3 * X / 4), X);
		std::vector rows4(X, row);

		auto col = m128load(mat2.GetRawData());
		std::vector cols(X, col);
		col = m128load(mat2.GetRawData() + (X / 4));
		std::vector cols2(X, col);
		col = m128load(mat2.GetRawData() + (X / 2));
		std::vector cols3(X, col);
		col = m128load(mat2.GetRawData() + (3*X / 4));
		std::vector cols4(X, col);

		for (size_t i = 1; i < X; i++) {
			rows[i] =  m128gather(mat[0] + i, X);
			rows2[i] = m128gather(mat[0] + i + X * (X / 4), X);
			rows3[i] = m128gather(mat[0] + i + X * (X / 2), X);
			rows4[i] = m128gather(mat[0] + i + X * (3*X / 4), X);

			cols[i] =  m128load(mat2[i]);
			cols2[i] = m128load(mat2[i] + (X / 4));
			cols3[i] = m128load(mat2[i] + (X/2));
			cols4[i] = m128load(mat2[i] + (3*X / 4));

		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave((rows[i] * cols[j]) + (rows2[i] * cols2[j]) + (rows3[i] * cols3[j]) + (rows4[i] * cols4[j]));
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}
	} else {
		math::BasicMatrix<X, X, T, true> temp = mulNoOptim<X, X, X, T, true>(mat, mat2);
		std::copy(temp.GetRawData(), temp.GetRawData() + (X) * (X), mat.GetRawData());
	}
	return mat;
}

template<size_t X, typename T, typename = std::enable_if_t<X == 32 / sizeof(T)>>
math::BasicMatrix<X, X, T, true>& operator*= (math::BasicMatrix<X, X, T, true>& mat, math::BasicMatrix<X, X, T, true>& mat2) {
	if ((GetIntrinsics() & INTRIN_AVX2)) {
		auto row = mgather(mat.GetRawData(), X);
		std::vector rows(X, row);
		auto col = mload(mat2.GetRawData());
		std::vector cols(X, col);
		for (size_t i = 1; i < X; i++) {
			rows[i] = mgather(mat[0] + i, X);
			cols[i] = mload(mat2[i]);
		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} else if (GetIntrinsics() & INTRIN_SSE4_2) {
		auto row = m128gather(mat.GetRawData(), X);
		std::vector rows(X, row);
		row = m128gather(mat.GetRawData() + X*(X/2), X);
		std::vector rows2(X, row);

		auto col = m128load(mat2.GetRawData());
		std::vector cols(X, col);
		col = m128load(mat2.GetRawData()+(X/2));
		std::vector cols2(X, col);

		for (size_t i = 1; i < X; i++) {
			rows[i] = m128gather(mat[0] + i, X);
			rows2[i] = m128gather(mat[0] + i + X*(X/2), X);

			cols[i] = m128load(mat2[i]);
			cols2[i] = m128load(mat2[i]+ (X/2));

		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]) + msumsave(rows2[i] * cols2[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} else {
		math::BasicMatrix<X, X, T, true> temp = mulNoOptim<X, X, X, T, true>(mat, mat2);
		std::copy(temp.GetRawData(), temp.GetRawData() + (X) * (X), mat.GetRawData());
	}
	return mat;
}

template<size_t X, typename T, typename = std::enable_if_t<X == 16 / sizeof(T)>, typename = std::enable_if_t<true>, typename = std::enable_if_t<true>>
math::BasicMatrix<X, X, T, true>& operator*= (math::BasicMatrix<X, X, T, true>& mat, const math::BasicMatrix<X, X, T, true>& mat2) {
	if ((GetIntrinsics() & INTRIN_AVX2)) {
		auto row = m128gather(mat.GetRawData(), X);
		std::vector rows(X, row);
		auto col = m128load(mat2.GetRawData());
		std::vector cols(X, col);
		for (size_t i = 1; i < X; i++) {
			rows[i] = m128gather(mat[0] + i, X);
			cols[i] = m128load(mat2[i]);
		}

		//T matri[32 / sizeof(T)][32 / sizeof(T)];
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < X; j++) {
				mat[j][i] = msumsave(rows[i] * cols[j]);
				//T[j][i] = msumsave(rows[i] * cols[j]);
			}
		}

	} 
	else {
		math::BasicMatrix<X, X, T, true> temp = mulNoOptim<X, X, X, T, true>(mat, mat2);
		std::copy(temp.GetRawData(), temp.GetRawData() + (X) * (X), mat.GetRawData());
	}
	return mat;
}


//NOT OPTIMIZED, NEEDS FINISHING
template<size_t X, typename T, typename = std::enable_if_t<(X != 16 / sizeof(T)) && (X != 32 / sizeof(T)) && (X != 64 / sizeof(T)) >, typename = std::enable_if_t<true>, typename = std::enable_if_t<true>, typename = std::enable_if_t<true>>
math::BasicMatrix<X, X, T, true>& operator*= (math::BasicMatrix<X, X, T, true>& mat, const math::BasicMatrix<X, X, T, true>& mat2) {
	//if (((GetIntrinsics() & INTRIN_AVX_512F)) && (X > 16 / sizeof(T))) {
	//	
	//} else if ((GetIntrinsics() & INTRIN_AVX2) && (X > 8 / sizeof(T))) {
	//
	//} else if((GetIntrinsics() & INTRIN_SSE4_2)){
	//
	//} else {
	//	mat = mulNoOptim(mat, mat2);
	//
	//}
	mat = mulNoOptim(mat, mat2);
	return mat;

}

template<size_t X, typename T>
math::BasicMatrix<X, X, T, false>& operator*= (math::BasicMatrix<X, X, T, false>& mat, const math::BasicMatrix<X, X, T, false>& mat2) {
	mat = mulNoOptim(mat, mat2);
	return mat;
}

#pragma endregion

#pragma region matrix*matrix
template<size_t X, size_t Y, size_t X2, typename T>
math::BasicMatrix<X2, Y, T, false> operator* (math::BasicMatrix<X, Y, T, false>& mat, math::BasicMatrix<X2, X, T, false>& mat2) {
	return mulNoOptim<X, Y, X2, T, false>(mat, mat2);
}
#pragma endregion

